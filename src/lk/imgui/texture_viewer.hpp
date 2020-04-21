#ifndef LINKATA_SRC_LK_IMGUI_TEXTURE_VIEWER_HPP_
#define LINKATA_SRC_LK_IMGUI_TEXTURE_VIEWER_HPP_
#pragma once

#include <lk/lk.hpp>

#include <Magnum/GL/GL.h>

namespace lk::texture_viewer {
  template<int RegionSize = 32, int Zoom = 4>
  void draw(Magnum::GL::Texture2D &texture_, Magnum::Vector2i texture_size_);
}

#include "texture_viewer.tpp"

#endif //LINKATA_SRC_LK_IMGUI_TEXTURE_VIEWER_HPP_
