#include "hax.hpp"

namespace {
#if defined(LINKATA_HAX_IMGUI_SHADER)
  struct linkata_hax_getImGuiShader_type {
    Magnum::ImGuiIntegration::Implementation::ImGuiShader *imgui_shader;
  };
#endif

#if defined(LINKATA_HAX_ATLAS_TEXTURE)
  struct linkata_hax_getAtlasTexture_type {
    Magnum::GL::Texture2D *atlas_texture;
  };
#endif
}

#if defined(LINKATA_HAX_IMGUI_SHADER)
template<>
bool Magnum::ImGuiIntegration::Context::handleTextInputEvent(linkata_hax_getImGuiShader_type &obj) {
  obj.imgui_shader = &_shader;
  return false;
}
#endif

#if defined(LINKATA_HAX_ATLAS_TEXTURE)
template<>
bool Magnum::ImGuiIntegration::Context::handleTextInputEvent(linkata_hax_getAtlasTexture_type &obj) {
  obj.atlas_texture = &_texture;
  return false;
}
#endif

Magnum::ImGuiIntegration::Implementation::ImGuiShader *lk::hax::getImGuiShader(Magnum::ImGuiIntegration::Context &imgui_)
#if defined(LINKATA_HAX_IMGUI_SHADER)
{
  linkata_hax_getImGuiShader_type event{};
  imgui_.handleTextInputEvent(event);
  return event.imgui_shader;
}
#else
{
  return nullptr;
}
#endif

Magnum::GL::Texture2D *lk::hax::getAtlasTexture(Magnum::ImGuiIntegration::Context &imgui_)
#if defined(LINKATA_HAX_ATLAS_TEXTURE)
{
  linkata_hax_getAtlasTexture_type event{};
  imgui_.handleTextInputEvent(event);
  return event.atlas_texture;
}
#else
{
  return nullptr;
}
#endif
