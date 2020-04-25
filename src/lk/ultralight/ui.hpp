//
// Created by but on 1/6/2020.
//

#ifndef LINKATA_SRC_LK_UI_ULTRALIGHT_UI_HPP_
#define LINKATA_SRC_LK_UI_ULTRALIGHT_UI_HPP_
#pragma once
#include <lk/lk.hpp>
#include LINKATA_PLATFORM_HEADER

#include <lk/ready_task_queue.hpp>

namespace lk {
  namespace ultralight {
    class ui {
     public:
      explicit ui(
          Magnum::Platform::Application &application_,
          ready_task_queue &task_queue_
      );

      void relayout(const Magnum::Vector2& size, const Magnum::Vector2i& windowSize, const Magnum::Vector2i& framebufferSize);
      void relayout(const Magnum::Vector2i& size);
      void draw();

      template<class KeyEvent>
      bool handleKeyPressEvent(KeyEvent &event);

      template<class KeyEvent>
      bool handleKeyReleaseEvent(KeyEvent &event);

      template<class MouseEvent>
      bool handleMousePressEvent(MouseEvent &event);

      template<class MouseEvent>
      bool handleMouseReleaseEvent(MouseEvent &event);

      template<class MouseMoveEvent>
      bool handleMouseMoveEvent(MouseMoveEvent &event);

      template<class MouseScrollEvent>
      bool handleMouseScrollEvent(MouseScrollEvent &event);

      template<class TextInputEvent>
      bool handleTextInputEvent(TextInputEvent &event);
    };
  }

#if !defined(LINKATA_UI_GUARD)
#define LINKATA_UI_GUARD
  using ui = ultralight::ui;
#else
#error "only one ui type may be used"
#endif
}

#include "ui.tpp"

#endif //LINKATA_SRC_LK_UI_ULTRALIGHT_UI_HPP_
