#ifndef LINKATA_SRC_LK_HAX_HPP_
#define LINKATA_SRC_LK_HAX_HPP_

#include <lk/lk.hpp>

#include <Magnum/GL/GL.h>
#include <Magnum/ImGuiIntegration/Context.hpp>

namespace lk::hax {
  Magnum::GL::Texture2D *getAtlasTexture(Magnum::ImGuiIntegration::Context &imgui_);
  Magnum::ImGuiIntegration::Implementation::ImGuiShader *getImGuiShader(Magnum::ImGuiIntegration::Context &imgui_);
}

#endif //LINKATA_SRC_LK_HAX_HPP_
