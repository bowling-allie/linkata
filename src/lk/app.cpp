#include "app.hpp"

#include <fmt/ostream.h>

#include <lk/emoji.hpp>
#include <lk/id.hpp>
#include <lk/svg.hpp>
#include <lk/resource.hpp>
#include <lk/log.hpp>

#include <Corrade/Utility/Arguments.h>
#include <Corrade/Utility/System.h>

#include <Magnum/GL/Context.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Renderer.h>

namespace {
  lk::svg::handle hello_kitty_svg{nullptr};
}

#include <Magnum/Math/BoolVector.h>
#include <Magnum/Math/Range.h>

lk::app::app(
    const Arguments &arguments
) : Magnum::Platform::Application{
    arguments,
    Configuration{}
        .setTitle(lk::config::app_name)
        .setSize({1280, 720})
        .setWindowFlags(Configuration::WindowFlag::Resizable),
    GLConfiguration{}
        .setColorBufferSize({8, 8, 8, 8})
        .setStencilBufferSize(8)
        .setSampleCount(8)
} {
#if defined(LINKATA_PLATFORM_GlfwApplication) && GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
  glfwSetWindowContentScaleCallback(window(), [](GLFWwindow *window, float x_scale, float y_scale) -> void {
    auto &app = *static_cast<lk::app *>(glfwGetWindowUserPointer(window));
    app.relayout(
        Magnum::Vector2{app.windowSize()} / app.dpiScaling(),
        app.windowSize(),
        app.framebufferSize()
    );
  });
#endif

  log::v(TAG, "arguments:");
  for (std::size_t i = 0; i < arguments.argc; ++i) {
    log::v(TAG, "  {}", arguments.argv[i]);
  }

  //using Debug = Corrade::Utility::Debug;
  //Debug debug{};
/*
  switch(Configuration{}.dpiScalingPolicy()) {
    case Configuration::DpiScalingPolicy::Physical:
      log::d(TAG, "default Configuration{}.dpiScalingPolicy(): Physical");
      break;
    case Configuration::DpiScalingPolicy::Virtual:
      log::d(TAG, "default Configuration{}.dpiScalingPolicy(): Virtual");
      break;
    default:
      break;
  }
*/

  /*{
    //Magnum::Math::BoolVector<83> val{0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b10101010, 0b010};
    Magnum::Math::BoolVector<8> val{0b10101010};
    //Magnum::Math::BoolVector<7> val{0b0101010};

    {
      boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
      for (std::size_t i = 0; i < 1000; ++i) {
        Corrade::Utility::Debug{} << val;
        //Corrade::Utility::Debug{} << "wow";
      }
      boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
      log::v(TAG, "time0: {}", end - start);
    }
    {
      boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
      for (std::size_t i = 0; i < 1000; ++i) {
        log::v(TAG, "{}", val);
        //log::v(TAG, "wow");
      }
      boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
      log::v(TAG, "time1: {}", end - start);
    }
    {
      boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();
      for (std::size_t i = 0; i < 1000; ++i) {
        LK_LOG_V(TAG, "{}", val);
        //LK_LOG_V(TAG, "wow");
      }
      boost::posix_time::ptime end = boost::posix_time::microsec_clock::local_time();
      log::v(TAG, "time2: {}", end - start);
    }
  }*/
/*
  Corrade::Containers::Array<int> array1{Corrade::Containers::InPlaceInit, {1, 2, 3}};
  Corrade::Containers::Array<Corrade::Containers::ArrayView<int>> array2{Corrade::Containers::InPlaceInit, {array1, array1, array1}};
  Corrade::Utility::Debug{} << "array1:" << array1;
  Corrade::Utility::Debug{} << "array2:" << array2;
  LK_LOG_V(TAG, "array1: {}", array1);
  LK_LOG_V(TAG, "array2: {}", array2);

  LK_LOG_D(TAG, "wow");
*/
  LK_LOG_D(TAG, "windowSize(): {}", windowSize());
  LK_LOG_D(TAG, "framebufferSize(): {}", framebufferSize());
  LK_LOG_D(TAG, "dpiScaling(): {}", dpiScaling());

#ifndef CORRADE_TARGET_EMSCRIPTEN
  LK_LOG_D(TAG, "GLConfiguration::flags(): {:#x}", static_cast<GLConfiguration::Flags::UnderlyingType>(GLConfiguration{}.flags()));
#endif

  LK_LOG_D(TAG, "GLConfiguration::colorBufferSize(): {}", GLConfiguration{}.colorBufferSize());
  LK_LOG_D(TAG, "GLConfiguration::depthBufferSize(): {}", GLConfiguration{}.depthBufferSize());
  LK_LOG_D(TAG, "GLConfiguration::stencilBufferSize(): {}", GLConfiguration{}.stencilBufferSize());
  LK_LOG_D(TAG, "GLConfiguration::sampleCount(): {}", GLConfiguration{}.sampleCount());

  /*{
    switch (Configuration{}.setSize({800, 600}, Configuration::DpiScalingPolicy::Physical).dpiScalingPolicy()) {
      case Configuration::DpiScalingPolicy::Physical:
        debug << "1 dpiScalingPolicy():" << "Physical" << Debug::newline;
        break;
      case Configuration::DpiScalingPolicy::Virtual:
        debug << "1 dpiScalingPolicy():" << "Virtual" << Debug::newline;
        break;
      default:break;
    }
    debug << "1 dpiScaling():" << Configuration{}.setSize({800, 600}, Configuration::DpiScalingPolicy::Physical).dpiScaling() << Debug::newline;
    debug << "2 dpiScaling():" << Configuration{}.setSize({800, 600}, {1.0f, 1.0f}).dpiScaling() << Debug::newline;
    debug << "3 dpiScaling():" << dpiScaling(Configuration{}.setSize({800, 600}, Configuration::DpiScalingPolicy::Physical)) << Debug::newline;
    debug << "4 dpiScaling():" << dpiScaling(Configuration{}.setSize({800, 600}, {1.0f, 1.0f})) << Debug::newline;

    debug << "4 dpiScaling():" << dpiScaling(Configuration{}.setSize({800, 600}, {1.0f, 1.0f})) << Debug::newline;
  }*/



  /*{
    GLFWmonitor* const monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* const mode = glfwGetVideoMode(monitor);
    debug << "mode" << Magnum::Vector2i{mode->width, mode->height} << Debug::newline;
    Magnum::Vector2i monitorSize;
    glfwGetMonitorPhysicalSize(monitor, &monitorSize.x(), &monitorSize.y());
    debug << "monitorSize" << monitorSize << Debug::newline;
    auto dpi = Magnum::Vector2{Magnum::Vector2i{mode->width, mode->height}*25.4f/Magnum::Vector2{monitorSize}};
    debug << "dpi" << dpi << Debug::newline;
    const Magnum::Vector2 dpiScaling{dpi/96.0f};
    debug << "dpiScaling:" << dpiScaling << Debug::newline;
    Magnum::Vector2 windowContentScale;
    glfwGetWindowContentScale(window(), &windowContentScale.x(), &windowContentScale.y());
    debug << "windowContentScale:" << windowContentScale << Debug::newline;
    //HWND handle = glfwGetWin32Window(window());
//    GetWindowDpiAwarenessContext (handle)
  }*/

  {
    std::vector<char> svg_vector{};
    {
      resource svg_resource{id::drawable::hello_kitty_svg, true, false};
      auto svg_data = svg_resource.getData();
      svg_vector.resize(svg_data.size() + 1);
      std::copy(svg_data.cbegin(), svg_data.cend(), svg_vector.begin());
    }
    hello_kitty_svg = svg::parse(svg_vector.data());
  }
/*
  Corrade::Utility::Debug{} << "Corrade::Utility::Resource::hasGroup(\"res\") - " << Corrade::Utility::Resource::hasGroup("res");
  auto res = Corrade::Utility::Resource{"res"};
  Corrade::Utility::Debug{} << "Resources:";
  for (auto &n : res.list()) {
    Corrade::Utility::Debug{} << "    " << Corrade::Utility::Debug::nospace << n.c_str();
  }
*/
  m_state = std::make_unique<state>();
  m_ui = std::make_unique<ui>(this);
}

lk::ready_task_queue &lk::app::getTaskQueue() {
  return m_taskQueue;
}

std::thread::id lk::app::getThreadId() {
  return m_threadId;
}

void lk::app::processTasks() {
  while (auto task_ = m_taskQueue.popReadyTask()) {
    log::v(TAG, "executing task: {}", task_->first);
    task_->second();
  }
}

Magnum::Vector2i lk::app::windowSize() const {
  return Magnum::Platform::Application::windowSize();
}

Magnum::Vector2i lk::app::framebufferSize() const {
  return Magnum::Platform::Application::framebufferSize();
}

Magnum::Vector2 lk::app::dpiScaling() {
#if defined(LINKATA_PLATFORM_GlfwApplication) && GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
  Magnum::Vector2 windowContentScale{};
  glfwGetWindowContentScale(window(), &windowContentScale.x(), &windowContentScale.y());
  return windowContentScale;
#else
  return Magnum::Platform::Application::dpiScaling();
#endif
}

void lk::app::draw() {
  //Corrade::Utility::System::sleep(500);
  processTasks();
  //Magnum::GL::Renderer::setScissor({{}, framebufferSize()});
  Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::ScissorTest);
  Magnum::GL::defaultFramebuffer.clear(
      Magnum::GL::FramebufferClear::Color
          | Magnum::GL::FramebufferClear::Depth
          | Magnum::GL::FramebufferClear::Stencil
  );

  {
    Magnum::GL::Context::current().resetState(Magnum::GL::Context::State::EnterExternal);

    nvgBeginFrame(
        svg::detail::getNvgContext(),
        windowSize().x(),
        windowSize().y(),
        dpiScaling().x()
    );

    svg::draw(hello_kitty_svg, {{{}, Magnum::Vector2{static_cast<float>(windowSize().min())}}});

    nvgEndFrame(svg::detail::getNvgContext());

    Magnum::GL::Context::current().resetState(Magnum::GL::Context::State::ExitExternal);

    /// todo: find out why we need this when calling Context::current().resetState(State::Framebuffers)
    //Magnum::GL::defaultFramebuffer.bind();
  }

  m_ui->draw();
  swapBuffers();
}

void lk::app::relayout(
    const Magnum::Vector2 &size,
    const Magnum::Vector2i &windowSize,
    const Magnum::Vector2i &framebufferSize
) {
  Magnum::GL::defaultFramebuffer.bind();
  Magnum::GL::defaultFramebuffer.setViewport({{}, framebufferSize});
  m_ui->relayout(
      size,
      windowSize,
      framebufferSize
  );
}

void lk::app::drawEvent() {
  if (m_isDrawing) return;
  m_isDrawing = true;
  draw();
  redraw();
  m_isDrawing = false;
}

void lk::app::viewportEvent(ViewportEvent &event) {
  relayout(
      Magnum::Vector2{event.windowSize()} / dpiScaling(),
      event.windowSize(),
      event.framebufferSize()
  );
}

void lk::app::keyPressEvent(KeyEvent &event) {
  if (m_ui->handleKeyPressEvent(event)) return;
}

void lk::app::keyReleaseEvent(KeyEvent &event) {
  if (m_ui->handleKeyReleaseEvent(event)) return;
}

void lk::app::mousePressEvent(MouseEvent &event) {
  if (m_ui->handleMousePressEvent(event)) return;
}

void lk::app::mouseReleaseEvent(MouseEvent &event) {
  if (m_ui->handleMouseReleaseEvent(event)) return;
}

void lk::app::mouseMoveEvent(MouseMoveEvent &event) {
  if (m_ui->handleMouseMoveEvent(event)) return;
}

void lk::app::mouseScrollEvent(MouseScrollEvent &event) {
  if (m_ui->handleMouseScrollEvent(event)) {
    event.setAccepted(); // Prevent scrolling the page
    return;
  }
}

void lk::app::textInputEvent(TextInputEvent &event) {
  if (m_ui->handleTextInputEvent(event)) return;
}
