#ifndef LINKATA_SRC_LK_IMGUI_UTIL_HPP_
#define LINKATA_SRC_LK_IMGUI_UTIL_HPP_
#pragma once

#include <lk/lk.hpp>

#include <Corrade/Containers/Containers.h>

#include <Magnum/Magnum.h>
#include <Magnum/GL/GL.h>
#include <Magnum/ImGuiIntegration/Context.h>

#include <imgui.h>

namespace lk::imgui::util {
  /**
   * adds font to ImFontAtlas atlas using ImFontAtlas::AddFontFromMemoryTTF()
   * @param font_res_
   * @param glyph_ranges_
   */
  ImFont *addFont(
      Corrade::Containers::ArrayView<const char> font_,
      float size_pixels,
      const ImFontConfig *font_cfg_template_ = nullptr,
      const ImWchar *glyph_ranges_ = nullptr
  );

  /**
   * adds font to ImFontAtlas atlas using ImFontAtlas::AddFontFromMemoryTTF()
   * @param font_
   * @param font_cfg_template_
   * @param glyph_ranges_
   */
  ImFont *addFont(
      Corrade::Containers::Array<char> font_,
      float size_pixels,
      const ImFontConfig *font_cfg_template_ = nullptr,
      const ImWchar *glyph_ranges_ = nullptr
  );

  Magnum::GL::Texture2D &getAtlasTexture(Magnum::ImGuiIntegration::Context &imgui_);

  Magnum::Vector2i getAtlasTextureSize(Magnum::ImGuiIntegration::Context &imgui_);
};

#endif //LINKATA_SRC_LK_IMGUI_UTIL_HPP_
