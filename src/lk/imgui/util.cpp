#include "util.hpp"

#if defined(LINKATA_HAX)
#include <lk/hax.hpp>
#endif

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/ArrayView.h>

ImFont *lk::imgui::util::addFont(
    Corrade::Containers::ArrayView<const char> font_,
    float size_pixels,
    const ImFontConfig *font_cfg_template_,
    const ImWchar *glyph_ranges_
) {
  ImFontConfig font_config_{font_cfg_template_ ? *font_cfg_template_ : ImFontConfig{}};

  font_config_.PixelSnapH = true;
  font_config_.OversampleH = 1;
#if !defined(LINKATA_COPY_IMGUI_FONT_DATA)
  font_config_.FontDataOwnedByAtlas = false;
#endif

  auto font_data_size_ = font_.size();

#if defined(LINKATA_COPY_IMGUI_FONT_DATA)
  char *font_data_ = new char[font_data_size_];
  std::copy(font_res_.data(), font_res_.data() + font_data_size_, font_data_);
#else
  auto font_data_ = font_.data();
#endif

  return ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
#if defined(LINKATA_COPY_IMGUI_FONT_DATA)
      font_data_,
#else
      const_cast<char *>(font_data_),
#endif
      font_data_size_,
      size_pixels,
      &font_config_,
      glyph_ranges_
  );
}

ImFont *lk::imgui::util::addFont(
    Corrade::Containers::Array<char> font_,
    float size_pixels,
    const ImFontConfig *font_cfg_template_,
    const ImWchar *glyph_ranges_
) {
  ImFontConfig font_config_{font_cfg_template_ ? *font_cfg_template_ : ImFontConfig{}};

  font_config_.PixelSnapH = true;
  font_config_.OversampleH = 1;

  auto font_data_size_ = font_.size();
  auto font_data_ = font_.release();

  return ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
      font_data_,
      font_data_size_,
      size_pixels,
      &font_config_,
      glyph_ranges_
  );
}

Magnum::GL::Texture2D &lk::imgui::util::getAtlasTexture(Magnum::ImGuiIntegration::Context &imgui_) {
#if defined(LINKATA_HAX_ATLAS_TEXTURE)
  return *hax::getAtlasTexture(imgui_);
#else
  return imgui_.atlasTexture();
#endif
}

Magnum::Vector2i lk::imgui::util::getAtlasTextureSize(Magnum::ImGuiIntegration::Context &imgui_) {
  auto fonts = ImGui::GetIO().Fonts;
  return {fonts->TexWidth, fonts->TexHeight};
}
