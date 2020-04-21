#ifndef LINKATA_SRC_LK_IMGUI_IMAGE_TOGGLE_BUTTON_HPP_
#define LINKATA_SRC_LK_IMGUI_IMAGE_TOGGLE_BUTTON_HPP_
#pragma once

#include <lk/lk.hpp>
#include <lk/resource.hpp>
#include <lk/id.hpp>

#include <Corrade/Containers/Optional.h>

#include <Magnum/GL/Texture.h>
#include <Magnum/Trade/ImageData.h>

namespace lk {
  class image_toggle_button {
   public:
    image_toggle_button(const image_toggle_button &) = delete;
    image_toggle_button(image_toggle_button &&other) noexcept = default;

    image_toggle_button &operator=(const image_toggle_button &other) = delete;
    image_toggle_button &operator=(image_toggle_button &&other) noexcept = default;

    explicit image_toggle_button(
        bool init_state_,
        const std::string &on_resource_id_,
        const std::string &off_resource_id_,
        bool async_ = false
    );

    image_toggle_button &operator=(bool state_);

    [[nodiscard]] bool getState() const noexcept;
    [[nodiscard]] Magnum::GL::Texture2D *getTexture() const noexcept;

    void draw(float width_, float height_);

    void toggle() noexcept;
    [[nodiscard]] bool isReady() const;

    void refresh();

   private:
    bool m_state;
    lk::resource m_onResource;
    lk::resource m_offResource;
    Corrade::Containers::Optional<Magnum::GL::Texture2D> m_onTexture{};
    Corrade::Containers::Optional<Magnum::GL::Texture2D> m_offTexture{};
    Magnum::GL::Texture2D *m_texture{nullptr};
  };
}

#endif //LINKATA_SRC_LK_IMGUI_IMAGE_TOGGLE_BUTTON_HPP_
