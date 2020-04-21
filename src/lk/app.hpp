#ifndef LINKATA_SRC_LK_APP_HPP_
#define LINKATA_SRC_LK_APP_HPP_
#pragma once

#include <lk/lk.hpp>
#include LINKATA_PLATFORM_HEADER
#include LINKATA_UI_HEADER

#include <lk/ready_task_queue.hpp>
#include <lk/state.hpp>

#include <atomic>
#include <condition_variable>
#include <thread>

namespace lk {
  class app : public Magnum::Platform::Application {
   public:
    static const constexpr auto TAG = "lk::app";

    explicit app(const Arguments &arguments);

    ready_task_queue &getTaskQueue();
    std::thread::id getThreadId();
    void processTasks();
    void draw();
    void relayout(
        const Magnum::Vector2 &size,
        const Magnum::Vector2i &windowSize,
        const Magnum::Vector2i &framebufferSize
    );

    Magnum::Vector2i windowSize() const;
    Magnum::Vector2i framebufferSize() const;
    Magnum::Vector2 dpiScaling();
    void drawEvent() override;
    void viewportEvent(ViewportEvent &event) override;
    void keyPressEvent(KeyEvent &event) override;
    void keyReleaseEvent(KeyEvent &event) override;
    void mousePressEvent(MouseEvent &event) override;
    void mouseReleaseEvent(MouseEvent &event) override;
    void mouseMoveEvent(MouseMoveEvent &event) override;
    void mouseScrollEvent(MouseScrollEvent &event) override;
    void textInputEvent(TextInputEvent &event) override;

   private:
    //std::mutex m_mutex{};
    //std::condition_variable m_condition{};
    //std::atomic_bool m_startRender{false};
    std::thread::id m_threadId{std::this_thread::get_id()};
    ready_task_queue m_taskQueue{};
    std::unique_ptr<state> m_state{nullptr};
    std::unique_ptr<ui> m_ui{nullptr};
    //std::thread m_renderThread;
  };
}

#endif //LINKATA_SRC_LK_APP_HPP_
