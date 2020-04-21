#ifndef LINKATA_SRC_LK_IMGUI_TEXT_TOGGLE_BUTTON_HPP_
#define LINKATA_SRC_LK_IMGUI_TEXT_TOGGLE_BUTTON_HPP_
#pragma once

#include <lk/lk.hpp>

#include <string>

namespace lk {
  class text_toggle_button {
   public:
    text_toggle_button(const text_toggle_button&) = delete;
    text_toggle_button(text_toggle_button&& other) noexcept = default;

    text_toggle_button& operator=(const text_toggle_button& other) = delete;
    text_toggle_button& operator=(text_toggle_button&& other) noexcept = default;

    explicit text_toggle_button(bool init_state_, std::string on_display_, std::string off_display_);

    text_toggle_button &operator=(bool state_);

    [[nodiscard]] bool getState() const noexcept;
    [[nodiscard]] const char *getDisplay() const noexcept;

    void draw(float width_, float height_);

    void toggle() noexcept;

    void refresh();

   private:
    bool m_state;
    std::string m_onDisplay;
    std::string m_offDisplay;
    const char *m_display{nullptr};
  };
}

#endif //LINKATA_SRC_LK_IMGUI_TEXT_TOGGLE_BUTTON_HPP_
