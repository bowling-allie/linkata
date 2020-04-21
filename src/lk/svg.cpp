#include <cstdio>

#define NANOSVG_IMPLEMENTATION
#include "svg.hpp"

#include <cassert>

#include <Corrade/Containers/Optional.h>
#include <Corrade/Containers/Pointer.h>
#include <Corrade/Utility/DebugStl.h>

#include <fmt/core.h>

#if !defined(MAGNUM_TARGET_GL)
#error "nanovg requires targeting opengl"
#endif

#if defined(MAGNUM_TARGET_GLES)
#if defined(MAGNUM_TARGET_GLES3)
#define NANOVG_GLES3_IMPLEMENTATION
#elif defined(MAGNUM_TARGET_GLES2)
#define NANOVG_GLES2_IMPLEMENTATION
#endif
#else
#define NANOVG_GL3_IMPLEMENTATION
#endif

#include <Magnum/Magnum.h>
#include <Magnum/GL/OpenGL.h>

#include <nanovg_gl.h>

#include <utility>

lk::svg::handle::handle(lk::svg::handle::type *init_) noexcept : m_handle{init_} {}

lk::svg::handle::~handle() {
  nsvgDelete(m_handle.release());
}

NVGcontext *lk::svg::detail::getNvgContext() {
  static thread_local NVGcontext *nvgContext_ =
#if defined(MAGNUM_TARGET_GLES)
#if defined(MAGNUM_TARGET_GLES3)
      nvgCreateGLES3(NVG_STENCIL_STROKES);
#elif defined(MAGNUM_TARGET_GLES2)
      nvgCreateGLES2(0);
#endif
#else
      nvgCreateGL3(NVG_STENCIL_STROKES)
#endif
  ;

  return nvgContext_;
}

lk::svg::handle lk::svg::parse(char *svg_data) {
  return {nsvgParse(svg_data, "px", 1.0f)};
}

namespace {
  NVGcolor getNVGColor(uint32_t color) {
    return nvgRGBA(
        (color >> 0) & 0xff,
        (color >> 8) & 0xff,
        (color >> 16) & 0xff,
        (color >> 24) & 0xff
        );
  }

  static NVGpaint getPaint(NVGcontext* vg, NSVGpaint* p) {
    assert(p->type == NSVG_PAINT_LINEAR_GRADIENT || p->type == NSVG_PAINT_RADIAL_GRADIENT);
    NSVGgradient* g = p->gradient;
    assert(g->nstops >= 1);
    NVGcolor icol = getNVGColor(g->stops[0].color);
    NVGcolor ocol = getNVGColor(g->stops[g->nstops - 1].color);

    float inverse[6];
    nvgTransformInverse(inverse, g->xform);
    Corrade::Utility::Debug{} << fmt::format("\t\t\tinverse: {} {} {} {} {} {}\n", inverse[0], inverse[1], inverse[2], inverse[3], inverse[4], inverse[5]);
    std::pair<float, float> s{};
    std::pair<float, float> e{};
    Corrade::Utility::Debug{} << fmt::format("\t\t\tsx: {} sy: {} ex: {} ey: {}\n", s.first, s.second, e.first, e.second);
    // Is it always the case that the gradient should be transformed from (0, 0) to (0, 1)?
    nvgTransformPoint(&s.first, &s.second, inverse, 0, 0);
    nvgTransformPoint(&e.first, &e.second, inverse, 0, 1);
    Corrade::Utility::Debug{} << fmt::format("\t\t\tsx: {} sy: {} ex: {} ey: {}\n", s.first, s.second, e.first, e.second);

    NVGpaint paint;
    if (p->type == NSVG_PAINT_LINEAR_GRADIENT)
      paint = nvgLinearGradient(vg, s.first, s.second, e.first, e.second, icol, ocol);
    else
      paint = nvgRadialGradient(vg, s.first, s.second, 0.0, 160, icol, ocol);
    return paint;
  }

  /** Returns the parameterized value of the line p2--p3 where it intersects with p0--p1 */
  static float getLineCrossing(std::pair<float, float> &p0, std::pair<float, float> &p1, std::pair<float, float> &p2, std::pair<float, float> &p3) {
    std::pair<float, float> d{p1.first - p0.first, p1.second - p0.second};
    std::pair<float, float> e{p3.first - p2.first, p3.second - p2.second};
    float m = (d.first * e.second) - (d.second * e.first);
    // Check if lines are parallel, or if either pair of points are equal
    if (std::abs(m) < 1e-6)
      return std::numeric_limits<float>::quiet_NaN();

    std::pair<float, float> b{p2.first - p0.first, p2.second - p0.second};
    return -((d.first * b.second) - (d.second * b.first)) / m;
  }
}

void lk::svg::draw(lk::svg::handle &svg_handle, Corrade::Containers::Optional<Magnum::Range2D> rect) {
  /*
  Corrade::Utility::Debug{} << fmt::format(
      "new image | input size: {}x{} | output size: {}x{} | scale: {}x{}",
      svg_handle.m_handle->width,
      svg_handle.m_handle->height,
      size->x(),
      size->y(),
      scale.x(),
      scale.y()
  );
  */

  auto vg = detail::getNvgContext();
  auto svg = svg_handle.m_handle.get();

  nvgResetTransform(vg);

  if (rect) {
    Magnum::Vector2 scale{rect->size() / Magnum::Vector2{svg_handle.m_handle->width, svg_handle.m_handle->height}};
    nvgTranslate(vg, rect->min().x(), rect->min().y());
    nvgScale(vg, scale.x(), scale.y());
  }

  int shapeIndex = 0;
  // Iterate shape linked list
  for (NSVGshape* shape = svg->shapes; shape; shape = shape->next, shapeIndex++) {
    //Corrade::Utility::Debug{} << fmt::format("\tnew shape: {:d} id \"{}\", fillrule {:d}, from ({}, {}) to ({}, {})", shapeIndex, shape->id, shape->fillRule, shape->bounds[0], shape->bounds[1], shape->bounds[2], shape->bounds[3]);

    // Visibility
    if (!(shape->flags & NSVG_FLAGS_VISIBLE))
      continue;

    nvgSave(vg);

    // Opacity
    if (shape->opacity < 1.0)
      nvgGlobalAlpha(vg, shape->opacity);

    // Build path
    nvgBeginPath(vg);

    int pathIndex = 0;
    // Iterate path linked list
    for (NSVGpath* path = shape->paths; path; path = path->next, pathIndex++) {
      //Corrade::Utility::Debug{} << fmt::format("\t\tnew path: index: {:d} npts: {:d}, {}, from ({}, {}) to ({}, {})", pathIndex, path->npts, path->closed ? "closed" : "open", path->bounds[0], path->bounds[1], path->bounds[2], path->bounds[3]);

      nvgMoveTo(vg, path->pts[0], path->pts[1]);
      for (int i = 1; i < path->npts; i += 3) {
        float* p = &path->pts[2 * i];
        nvgBezierTo(vg, p[0], p[1], p[2], p[3], p[4], p[5]);
        //nvgLineTo(vg, p[4], p[5]);
        //Corrade::Utility::Debug{} << fmt::format("\t\t\tbezier ({}, {}) to ({}, {})", p[-2], p[-1], p[4], p[5]);
        //Corrade::Utility::Debug{} << fmt::format("\t\t\tbezier ({}, {}), ({}, {}), ({}, {}), ({}, {})", p[-2], p[-1], p[0], p[1], p[2], p[3], p[4], p[5]);
      }

      // Close path
      if (path->closed)
        nvgClosePath(vg);

      // Compute whether this is a hole or a solid.
      // Assume that no paths are crossing (usually true for normal SVG graphics).
      // Also assume that the topology is the same if we use straight lines rather than Beziers (not always the case but usually true).
      // Using the even-odd fill rule, if we draw a line from a point on the path to a point outside the boundary (e.g. top left) and count the number of times it crosses another path, the parity of this count determines whether the path is a hole (odd) or solid (even).
      int crossings = 0;
      std::pair<float, float> p0{path->pts[0], path->pts[1]};
      std::pair<float, float> p1{path->bounds[0] - 1.0f, path->bounds[1] - 1.0f};
      // Iterate all other paths
      for (NSVGpath* path2 = shape->paths; path2; path2 = path2->next) {
        if (path2 == path)
          continue;

        // Iterate all lines on the path
        if (path2->npts < 4)
          continue;
        for (int i = 1; i < path2->npts + 3; i += 3) {
          float* p = &path2->pts[2 * i];
          // The previous point
          std::pair<float, float> p2{p[-2], p[-1]};
          // The current point
          std::pair<float, float> p3 = (i < path2->npts) ? std::pair<float, float>{p[4], p[5]} : std::pair<float, float>{path2->pts[0], path2->pts[1]};
          float crossing = getLineCrossing(p0, p1, p2, p3);
          float crossing2 = getLineCrossing(p2, p3, p0, p1);
          if (0.0 <= crossing && crossing < 1.0 && 0.0 <= crossing2) {
            crossings++;
          }
        }
      }

      if (crossings % 2 == 0)
        nvgPathWinding(vg, NVG_SOLID);
      else
        nvgPathWinding(vg, NVG_HOLE);

    }

    // Fill shape
    if (shape->fill.type) {
      switch (shape->fill.type) {
        case NSVG_PAINT_COLOR: {
          NVGcolor color = getNVGColor(shape->fill.color);
          nvgFillColor(vg, color);
          /*
          Corrade::Utility::Debug{} << fmt::format(
              "\t\tfill color #{:02x}{:02x}{:02x}{:02x}",
              (shape->fill.color >>  0) & 0xff,
              (shape->fill.color >>  8) & 0xff,
              (shape->fill.color >> 16) & 0xff,
              (shape->fill.color >> 24) & 0xff
          );
          */
        } break;
        case NSVG_PAINT_LINEAR_GRADIENT:
        case NSVG_PAINT_RADIAL_GRADIENT: {
          NSVGgradient* g = shape->fill.gradient;
          (void)g;
          //Corrade::Utility::Debug{} << fmt::format("\t\tgradient: type: {} xform: {} {} {} {} {} {} spread: {:d} fx: {} fy: {} nstops: {:d}", (shape->fill.type == NSVG_PAINT_LINEAR_GRADIENT ? "linear" : "radial"), g->xform[0], g->xform[1], g->xform[2], g->xform[3], g->xform[4], g->xform[5], g->spread, g->fx, g->fy, g->nstops);
          for (int i = 0; i < g->nstops; i++) {
            //Corrade::Utility::Debug{} << fmt::format("\t\t\tstop: #{:08x}\t{}", g->stops[i].color, g->stops[i].offset);
          }
          nvgFillPaint(vg, getPaint(vg, &shape->fill));
        } break;
      }
      nvgFill(vg);
    }

    // Stroke shape
    if (shape->stroke.type) {
      nvgStrokeWidth(vg, shape->strokeWidth);
      // strokeDashOffset, strokeDashArray, strokeDashCount not yet supported
      nvgLineCap(vg, (NVGlineCap) shape->strokeLineCap);
      nvgLineJoin(vg, (int) shape->strokeLineJoin);

      switch (shape->stroke.type) {
        case NSVG_PAINT_COLOR: {
          NVGcolor color = getNVGColor(shape->stroke.color);
          nvgStrokeColor(vg, color);
          //Corrade::Utility::Debug{} << fmt::format("\t\tstroke color ({}, {}, {}, {})", color.r, color.g, color.b, color.a);
        } break;
        case NSVG_PAINT_LINEAR_GRADIENT: {
          Corrade::Utility::Fatal{} << "stroke type of NSVG_PAINT_LINEAR_GRADIENT is unsupported!";
          // NSVGgradient *g = shape->stroke.gradient;
          // printf("		lin grad: %f\t%f\n", g->fx, g->fy);
        } break;
        case NSVG_PAINT_RADIAL_GRADIENT: {
          Corrade::Utility::Fatal{} << "stroke type of NSVG_PAINT_LINEAR_GRADIENT is unsupported!";
          // NSVGgradient *g = shape->stroke.gradient;
          // printf("		lin grad: %f\t%f\n", g->fx, g->fy);
        } break;
      }
      nvgStroke(vg);
    }

    nvgRestore(vg);
  }

  //Corrade::Utility::Debug{} << "\n";
}
