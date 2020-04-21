#ifndef LINKATA_SRC_LK_IMGUI_UI_HPP_
#define LINKATA_SRC_LK_IMGUI_UI_HPP_
#pragma once

#include <lk/lk.hpp>

#include <lk/id.hpp>
#include <lk/ready_task_queue.hpp>
#include <lk/resource.hpp>
#include <lk/util.hpp>

#include "image_toggle_button.hpp"
#include "text_toggle_button.hpp"
#include "lk/emoji_svg_cache.hpp"

#include <imgui.h>

#if IMGUI_VERSION_NUM < 17500
#error "imgui version >= 1.75 required (unicode support)"
#endif

#include <Magnum/ImGuiIntegration/Context.hpp>

namespace lk {
  namespace imgui {
    class ui {
     public:
      explicit ui(app *application_);

      void relayoutFont();

      void relayout(
          const Magnum::Vector2 &size,
          const Magnum::Vector2i &windowSize,
          const Magnum::Vector2i &framebufferSize
      );
      void relayout(const Magnum::Vector2i &size);
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

     private:
      void drawFontSizeSlider();
      void buildFontAtlas();

     private:
     public:
      app *m_application;
      Magnum::ImGuiIntegration::Context m_imgui;
      image_toggle_button m_uiVisibilityButton{true, id::drawable::eye, id::drawable::eye_slash};
#if defined(LINKATA_WITH_EMOJIS)
      emoji_svg_cache m_emojiRenderer{};
#endif
      int m_currentFontSize{16};

      float m_floatValue{0.0f};
      bool m_showMainWindow{true};
      bool m_showDemoWindow{true};
    };
  }

#if !defined(LINKATA_UI_GUARD)
#define LINKATA_UI_GUARD
  using ui = imgui::ui;
#else
#error "only one ui type may be included"
#endif
}

#include "ui.tpp"

#endif //LINKATA_SRC_LK_IMGUI_UI_HPP_
