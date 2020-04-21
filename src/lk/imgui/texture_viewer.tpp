#include "texture_viewer.hpp"

template<int RegionSize, int Zoom>
void lk::texture_viewer::draw(Magnum::GL::Texture2D &texture_, Magnum::Vector2i texture_size_) {
  auto texture_id_ = reinterpret_cast<ImTextureID>(&texture_);
  ImGuiIO &imgui_io_ = ImGui::GetIO();

  ImGui::Text("%dx%d", texture_size_.x(), texture_size_.y());
  ImVec2 pos = ImGui::GetCursorScreenPos();
  ImGui::Image(
      texture_id_,
      ImVec2(texture_size_.x(), texture_size_.y()),
      ImVec2(0, 0),
      ImVec2(1, 1),
      ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
      ImVec4(1.0f, 1.0f, 1.0f, 0.5f)
  );
  if (ImGui::IsItemHovered()) {
    ImGui::BeginTooltip();

    float region_x = imgui_io_.MousePos.x - pos.x - RegionSize * 0.5f;
    if (region_x < 0.0f) {
      region_x = 0.0f;
    } else if (region_x > texture_size_.x() - RegionSize) {
      region_x = texture_size_.y() - RegionSize;
    }

    float region_y = imgui_io_.MousePos.y - pos.y - RegionSize * 0.5f;
    if (region_y < 0.0f) {
      region_y = 0.0f;
    } else if (region_y > texture_size_.y() - RegionSize) {
      region_y = texture_size_.y() - RegionSize;
    }

    ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
    ImGui::Text("Max: (%.2f, %.2f)", region_x + RegionSize, region_y + RegionSize);

    ImVec2 uv0 = ImVec2((region_x) / texture_size_.x(), (region_y) / texture_size_.y());
    ImVec2 uv1 = ImVec2((region_x + RegionSize) / texture_size_.x(), (region_y + RegionSize) / texture_size_.y());
    ImGui::Image(
        texture_id_,
        ImVec2(RegionSize * Zoom, RegionSize * Zoom),
        uv0,
        uv1,
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        ImVec4(1.0f, 1.0f, 1.0f, 0.5f)
    );

    ImGui::EndTooltip();
  }
}
