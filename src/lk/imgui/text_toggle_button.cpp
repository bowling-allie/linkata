#include "text_toggle_button.hpp"

#include <imgui.h>

lk::text_toggle_button::text_toggle_button(
    bool init_state_,
    std::string on_display_,
    std::string off_display_
) : m_state{init_state_},
    m_onDisplay{std::move(on_display_)},
    m_offDisplay{std::move(off_display_)} {
  refresh();
}

lk::text_toggle_button &lk::text_toggle_button::operator=(bool state_) {
  m_state = state_;
  refresh();
  return *this;
}

bool lk::text_toggle_button::getState() const noexcept {
  return m_state;
}

const char *lk::text_toggle_button::getDisplay() const noexcept {
  return m_display;
}

void lk::text_toggle_button::draw(float width_, float height_) {
  if (ImGui::Button(
      m_display,
      {width_, height_}
  )) {
    toggle();
  }
}

void lk::text_toggle_button::toggle() noexcept {
  m_state = !m_state;
  refresh();
}

void lk::text_toggle_button::refresh() {
  if (m_state) {
    m_display = m_onDisplay.c_str();
  } else {
    m_display = m_offDisplay.c_str();
  }
}
