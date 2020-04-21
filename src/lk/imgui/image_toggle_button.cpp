#include "image_toggle_button.hpp"

#include <lk/util.hpp>

#include <imgui.h>
#include <imgui_internal.h>

lk::image_toggle_button::image_toggle_button(
    bool init_state_,
    const std::string &on_resource_id_,
    const std::string &off_resource_id_,
    bool async_
) : m_state{init_state_},
    m_onResource{on_resource_id_, true, async_},
    m_offResource{off_resource_id_, true, async_} {
  refresh();
}

lk::image_toggle_button &lk::image_toggle_button::operator=(bool state_) {
  m_state = state_;
  refresh();
  return *this;
}

bool lk::image_toggle_button::getState() const noexcept {
  return m_state;
}

Magnum::GL::Texture2D *lk::image_toggle_button::getTexture() const noexcept {
  return m_texture;
}

void lk::image_toggle_button::draw(float width_, float height_) {
  if (ImGui::ImageButton(
      reinterpret_cast<ImTextureID>(m_texture),
      {width_, height_}
  )) {
    toggle();
  }

  ImGuiWindow* window = ImGui::GetCurrentWindow();
  window->DrawList->_TextureIdStack.back() = reinterpret_cast<ImTextureID>(m_texture);
}

void lk::image_toggle_button::toggle() noexcept {
  m_state = !m_state;
  refresh();
}

bool lk::image_toggle_button::isReady() const {
  if (m_state) {
    return m_onResource.isReady();
  } else {
    return m_offResource.isReady();
  }
}

void lk::image_toggle_button::refresh() {
  if (m_state) {
    if (m_onTexture) {
      m_texture = &(*m_onTexture);
    } else {
      if (m_onResource.isReady()) {
        m_onTexture = *util::createTexture2DFromImageData2D(
            *util::importImageData2D(m_onResource.getData())
        );
        m_texture = &(*m_onTexture);
      }
    }
  } else {
    if (m_offTexture) {
      m_texture = &(*m_offTexture);
    } else {
      if (m_offResource.isReady()) {
        m_offTexture = *util::createTexture2DFromImageData2D(
            *util::importImageData2D(m_offResource.getData())
        );
        m_texture = &(*m_offTexture);
      }
    }
  }
}
