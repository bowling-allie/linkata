#include "ui.hpp"

#include <lk/app.hpp>
#include <lk/emoji.hpp>
#include <lk/util.hpp>
#include <lk/imgui/util.hpp>

#include <lk/imgui/texture_viewer.hpp>
#include <lk/imgui/style.hpp>

#include <Corrade/Utility/DebugStl.h>

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Mesh.h>

#if defined(LINKATA_HAX)
#include <lk/hax.hpp>
#endif

lk::imgui::ui::ui(
    app *application_
) : m_application{application_},
    m_imgui{
        Magnum::Vector2{m_application->windowSize()} / m_application->dpiScaling(),
        m_application->windowSize(),
        m_application->framebufferSize()
} {
/*
  ImGui::GetStyle().WindowBorderSize = 1.0f;
  ImGui::GetStyle().ChildBorderSize = 1.0f;
  ImGui::GetStyle().PopupBorderSize = 1.0f;
  ImGui::GetStyle().FrameBorderSize = 1.0f;
  ImGui::GetStyle().TabBorderSize = 1.0f;
  ImGui::GetStyle().Colors[ImGuiCol_Border] = {1.0f, 1.0f, 1.0f, 1.0f};
*/
  //imgui::style::cherry();

  relayoutFont();
}

void lk::imgui::ui::relayoutFont() {
  auto resource_font_roboto_ptr_ = std::make_shared<resource>(id::fonts::roboto);
  //auto resource_font_fa_regular_ptr_ = std::make_shared<resource>(id::fonts::fa_regular);
/*
  Corrade::Utility::Debug{} << "literal :" << std::array<const char, 4>{"\uF06E"};
  Corrade::Utility::Debug{} << "     u8 :" << std::array<const char, 4>{u8"\uF06E"};
  Corrade::Utility::Debug{} << "    raw :" << std::array<const char, 4>{R"()"};
  Corrade::Utility::Debug{} << "    raw :" << std::array<const char, 32>{R"( £ 👐 👩 💻 👩‍💻 )"};
*/
  m_application->getTaskQueue().pushTask(
      "lk::ui::ui() - initialize_font",
      ready_task_queue::task_type{[this, resource_font_roboto_ptr_]() -> std::any {
        if (!resource_font_roboto_ptr_)
          Corrade::Utility::Fatal{} << "lk::ui::ui()::<task_lambda> - resource_font_roboto_ptr_ is null!";

        {
          ///glBlendEquation(GL_FUNC_ADD);
          Magnum::GL::Renderer::setBlendEquation(
              Magnum::GL::Renderer::BlendEquation::Add
          );

          ///glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          Magnum::GL::Renderer::setBlendFunction(
              Magnum::GL::Renderer::BlendFunction::SourceAlpha,
              Magnum::GL::Renderer::BlendFunction::OneMinusSourceAlpha
          );
        }

        auto &imgui_io_ = ImGui::GetIO();
        imgui_io_.Fonts->Clear();

        ImFont *font_roboto_;
        if constexpr (resource_handle::can_release_data) {
          font_roboto_ = util::addFont(
              resource_font_roboto_ptr_->releaseData(),
              static_cast<float>(m_currentFontSize)
          );
        } else {
          font_roboto_ = util::addFont(
              resource_font_roboto_ptr_->getData(),
              static_cast<float>(m_currentFontSize)
          );
        }

#if defined(LINKATA_WITH_EMOJIS)
        std::vector<int> custom_rect_indices_;
        custom_rect_indices_.reserve(std::size(emoji::codepoints_list));
        {
          imgui_io_.Fonts->AddCustomRectFontGlyph(font_roboto_, 0x200D, 0, 0, 0);

          static const constexpr float emoji_scale = 1.2f;
          int emoji_size = std::max(18, static_cast<int>(m_currentFontSize * emoji_scale));
          // todo: do not hardcode num
          int i = 0;
          for (auto &codepoint : emoji::codepoints_list) {
            ++i;
            if (i > 200) break;
            if (codepoint.size() > 1) continue;
            custom_rect_indices_.push_back(
                imgui_io_.Fonts->AddCustomRectFontGlyph(
                    font_roboto_,
                    std::data(codepoint)[0],
                    emoji_size,
                    emoji_size,
                    static_cast<float>(emoji_size)
                )
            );
          }
        }
        custom_rect_indices_.shrink_to_fit();
#endif

        relayout(
            Magnum::Vector2{m_application->windowSize()} / m_application->dpiScaling(),
            m_application->windowSize(),
            m_application->framebufferSize()
        );

#if defined(LINKATA_WITH_EMOJIS)
/*
        emoji_svg_cache::custom_rects_type custom_rects_{};
        custom_rects_.reserve(custom_rect_indices_.size());
        for (auto custom_rect_index_ : custom_rect_indices_) {
          auto &imgui_custom_rect_ = imgui_io_.Fonts->CustomRects[custom_rect_index_];
          codepoint_array_type codepoints_array_{Corrade::Containers::NoInit, 1};
          codepoints_array_[0] = imgui_custom_rect_.ID;
          custom_rects_[std::move(codepoints_array_)] = Magnum::Range2Di{
              {
                  imgui_custom_rect_.X,
                  imgui_custom_rect_.Y
              },
              {
                  imgui_custom_rect_.X + imgui_custom_rect_.Width,
                  imgui_custom_rect_.Y + imgui_custom_rect_.Height
              }
          };
        }
*/

        Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::ScissorTest);

        Magnum::GL::Framebuffer atlas_framebuffer_{{}};
        atlas_framebuffer_.bind();
        atlas_framebuffer_
            .attachTexture(Magnum::GL::Framebuffer::ColorAttachment{0}, util::getAtlasTexture(m_imgui), 0)
            .mapForDraw(Magnum::GL::Framebuffer::ColorAttachment{0});

        if (atlas_framebuffer_.checkStatus(Magnum::GL::FramebufferTarget::Draw)
            != Magnum::GL::Framebuffer::Status::Complete) {
          Corrade::Utility::Debug{}
              << "atlas_framebuffer_.checkStatus() ="
              << atlas_framebuffer_.checkStatus(Magnum::GL::FramebufferTarget::Draw);
        }
/*
        nvgBeginFrame(
            svg::detail::getNvgContext(),
            static_cast<float>(Magnum::GL::defaultFramebuffer.viewport().size().x()),
            static_cast<float>(Magnum::GL::defaultFramebuffer.viewport().size().y()),
            1.0f
        );

        m_emojiRenderer.draw(
            util::imgui::getAtlasTexture(m_imgui),
            custom_rects_
        );*/

        for (auto custom_rect_index_ : custom_rect_indices_) {
          auto &imgui_custom_rect_ = imgui_io_.Fonts->CustomRects[custom_rect_index_];
          emoji::codepoint_array_type codepoint_array_{Corrade::Containers::NoInit, 1};
          codepoint_array_[0] = imgui_custom_rect_.ID;

          Magnum::Range2Di custom_rect_;
/*
    m_atlasFramebuffer.setViewport(
        {
            {0, 0},
            {512, 512}
        }
    );
*/
          atlas_framebuffer_.setViewport(
              {
                  {
                      imgui_custom_rect_.X,
                      imgui_custom_rect_.Y
                  },
                  {
                      imgui_custom_rect_.X + imgui_custom_rect_.Width,
                      imgui_custom_rect_.Y + imgui_custom_rect_.Height
                  }
              }
          );
          Corrade::Containers::ArrayView<const unsigned int> tmp{codepoint_array_};
          auto handle_it_ = m_emojiRenderer.m_svgHandles.find({codepoint_array_});
          if (handle_it_ == m_emojiRenderer.m_svgHandles.end()) {
            Corrade::Utility::Fatal{} << "lk::emoji_svg_cache::draw() - no emoji at codepoint:" << id::getCodepointArrayName(
                tmp);
            continue;
          }

          //svg::draw(handle_it_->second, {{{}, {512, 512}}});

          svg::draw(
              handle_it_->second,
              {{{}, static_cast<Magnum::Vector2>(custom_rect_.size())}}
          );

        }

        nvgEndFrame(svg::detail::getNvgContext());

        Magnum::GL::defaultFramebuffer.bind();

        while (true) {
          auto error_ = Magnum::GL::Renderer::error();
          if (error_ == Magnum::GL::Renderer::Error::NoError) break;
          Corrade::Utility::Error{} << "lk::emoji_svg_cache::draw() - " << error_;
        }
#endif
        return {};
      }},
      [resource_font_roboto_ptr_]() -> bool {
        if (!resource_font_roboto_ptr_)
          Corrade::Utility::Fatal{} << "lk::ui::ui()::<ready_lambda> - resource_font_roboto_ptr_ is null!";
        return resource_font_roboto_ptr_->isReady();
      }
  );
}

void lk::imgui::ui::relayout(const Magnum::Vector2 &size, const Magnum::Vector2i &windowSize, const Magnum::Vector2i &framebufferSize) {
  m_imgui.relayout(size, windowSize, framebufferSize);
}

void lk::imgui::ui::relayout(const Magnum::Vector2i &size) {
  m_imgui.relayout(size);
}
int i = 0;
void lk::imgui::ui::draw() {
  //svg::draw(m_emojiRenderer.m_svgHandles.begin()->second);
/*
  for (auto &svg : m_emojiRenderer.m_svgHandles) {
    if (!svg.second.m_handle) {
      Corrade::Utility::Debug{} << i << "NULL AHHHHH! meow 2efffdgsv";
    }
    //svg::draw(svg.second);
  }
*/
  {
    ///glBlendEquation(GL_FUNC_ADD);
    Magnum::GL::Renderer::setBlendEquation(
        Magnum::GL::Renderer::BlendEquation::Add
    );

    ///glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Magnum::GL::Renderer::setBlendFunction(
        Magnum::GL::Renderer::BlendFunction::SourceAlpha,
        Magnum::GL::Renderer::BlendFunction::OneMinusSourceAlpha
    );
  }

  m_imgui.newFrame();

  // Enable text input, if needed
  if (ImGui::GetIO().WantTextInput && !m_application->isTextInputActive()) {
    m_application->startTextInput();
  } else if (!ImGui::GetIO().WantTextInput && m_application->isTextInputActive()) {
    m_application->stopTextInput();
  }

  // ui visibility button
  {
    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowPos(
        {io.DisplaySize.x, io.DisplaySize.y},
        ImGuiCond_Always,
        {1.0f, 1.0f}
    );


    if (ImGui::Begin(
        "ui_visibility",
        nullptr,
        ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoDecoration |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav
    )) {
      m_uiVisibilityButton.draw(20, 16);
    }
    ImGui::End();
  }

  if (m_uiVisibilityButton.getState()) {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("example")) {
          // todo: make menu items
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Edit")) {
        if (ImGui::MenuItem("example")) {
          // todo: make menu items
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("View")) {
        /*{
          static const std::vector<std::pair<std::string, std::function<void()>>> font_selection_values_ = {
              {"Default", [this]() {
                m_taskQueue.pushTask("set_font_to_default", ready_task_queue::task_type{[this]() {
                  ImGui::GetIO().Fonts->Clear();
                  ImGui::GetIO().Fonts->AddFontDefault();
                  util::relayoutImGui(m_application, m_imgui);
                }});
              }},
              {"Roboto", [this]() {
                m_taskQueue.pushTask("set_font_to_roboto", ready_task_queue::task_type{[this]() {
                  {
                    auto fa_data_ = lk::res::getResources().getRaw("fonts/fa-regular-400.ttf");
                    ImWchar fa_glyph_ranges_[]{
                        0xf004, 0xf5c8,
                        0
                    };
                  }

                  ImGui::GetIO().Fonts->Clear();
                  lk::util::addImGuiFont(m_robotoFontResource.getData());
                  util::ImGui_relayout(m_application, m_imgui);
                }});
              }}
          };
          static std::size_t font_selection_selected_index_{0};
          static const char
              *font_selection_display_{font_selection_values_.at(font_selection_selected_index_).first.c_str()};
          ImGui::Text("Font");
          ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
          if (ImGui::BeginCombo("##linkata|main_menu|view|font_selection", font_selection_display_)) {
            for (int i = 0; i < font_selection_values_.size(); ++i) {
              const bool is_selected_{i == font_selection_selected_index_};
              if (ImGui::Selectable(font_selection_values_[i].first.c_str(), is_selected_)) {
                font_selection_selected_index_ = i;
                auto &selected_font_ = font_selection_values_.at(i);
                font_selection_display_ = selected_font_.first.c_str();
                selected_font_.second();
              }

              if (is_selected_) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
          }
        }*/
        drawFontSizeSlider();

        if (ImGui::MenuItem("example")) {
          // todo: make menu items
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("example")) {
          // todo: make menu items
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    if (m_showMainWindow) {
      if (ImGui::Begin("main", &m_showMainWindow)) {
        ImGui::Text("Hello, world!");

#if defined(LINKATA_WITH_EMOJIS)
        ImGui::Text("fa_eye: \uF06E");
        ImGui::Text("u8 meh: \U0001f612");
        ImGui::Text("u8 woman: \U0001F469");
        ImGui::Text("u8 zwj: \u200D");
        ImGui::Text("u8 pc: \U0001F4BB");
        ImGui::Text(R"(raw: £ 😒 👐 👩 💻 👩‍💻)");
#endif

        ImGui::SliderFloat("Clear color", &m_floatValue, 0.0f, 360.0f);
        Magnum::GL::Renderer::setClearColor(Magnum::Math::Color3<float>::fromHsv(
            {Magnum::Math::Deg<float>{m_floatValue}, 1.0f, 1.0f}
        ));
        /*if (m_emojiRenderer.m_textures.begin() != m_emojiRenderer.m_textures.end())
          texture_viewer::draw<>(m_emojiRenderer.m_textures.begin()->second, {m_currentFontSize, m_currentFontSize});*/

        texture_viewer::draw<>(util::getAtlasTexture(m_imgui), {ImGui::GetIO().Fonts->TexWidth, ImGui::GetIO().Fonts->TexHeight});

        if (ImGui::Button("Demo Window")) m_showDemoWindow ^= true;

        {
          float framerate_ = ImGui::GetIO().Framerate;
          ImGui::Text(
              "average delta %.3f ms/frame",
              1000.0f / framerate_
          );
          ImGui::Text(
              "average fps %.1f",
              framerate_
          );
        }

        {
          float delta_ = ImGui::GetIO().DeltaTime;
          static const constexpr auto sec_num = 1;
          static float worst_delta_ = delta_;
          static auto last_wd_ = std::chrono::system_clock::now();
          if (delta_ > worst_delta_
              || std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - last_wd_).count()
                  >= sec_num) {
            worst_delta_ = delta_;
            last_wd_ = std::chrono::system_clock::now();
          }

          ImGui::Text(
              "worst (last %d second(s)) delta %.3f ms/frame",
              sec_num,
              worst_delta_ * 1000.0f
          );
          ImGui::Text(
              "worst (last %d second(s)) fps %.3f ms/frame",
              sec_num,
              1.0f / worst_delta_
          );
        }
      }
      ImGui::End();
    }

    if (m_showDemoWindow) {
      ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
      ImGui::ShowDemoWindow();
    }
  }

  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::Blending);
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::ScissorTest);
  Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::FaceCulling);
  Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::DepthTest);

  m_imgui.drawFrame();

  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::DepthTest);
  Magnum::GL::Renderer::enable(Magnum::GL::Renderer::Feature::FaceCulling);
  Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::ScissorTest);
  Magnum::GL::Renderer::disable(Magnum::GL::Renderer::Feature::Blending);

  {
    while (true) {
      auto error_ = Magnum::GL::Renderer::error();
      if (error_ == Magnum::GL::Renderer::Error::NoError) break;
      Corrade::Utility::Error{} << "lk::ui::draw() - " << error_;
    }
  }
}

void lk::imgui::ui::drawFontSizeSlider() {
  static auto font_size_ = m_currentFontSize;
  ImGui::SliderInt("Font size", &font_size_, 0, 36);
  if (font_size_ != m_currentFontSize) {
    ImGui::SameLine();
    if (ImGui::Button("Apply")) {
      m_currentFontSize = font_size_;
      relayoutFont();
    }
  }
}

void lk::imgui::ui::buildFontAtlas() {

}
