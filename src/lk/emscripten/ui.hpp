#ifndef LINKATA_SRC_LK_UI_EMSCRIPTEN_UI_HPP_
#define LINKATA_SRC_LK_UI_EMSCRIPTEN_UI_HPP_
#pragma once

#include <lk/config.hpp>
#include LINKATA_PLATFORM_HEADER"Magnum/Platform/GlfwApplication.h"

#include <lk/ready_task_queue.hpp>

namespace lk {
  namespace emscripten {
    class ui {
     public:
      explicit ui(
          Magnum::Platform::Application &application_,
          ready_task_queue &task_queue_
      );

     private:
      Magnum::Platform::Application &m_application;
      ready_task_queue &m_taskQueue;
    };
  }

#if !defined(LINKATA_UI_GUARD)
#define LINKATA_UI_GUARD
  using ui = emscripten::ui;
#else
#error "only one ui type may be used"
#endif
}

#include <ui.tpp>

#endif //LINKATA_SRC_LK_UI_EMSCRIPTEN_UI_HPP_
