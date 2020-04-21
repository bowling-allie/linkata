#include "style.hpp"

void lk::imgui::style::cherry()  {
#define LK_IMGUI_STYLE_CHERRY_HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
#define LK_IMGUI_STYLE_CHERRY_MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
#define LK_IMGUI_STYLE_CHERRY_LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
#define LK_IMGUI_STYLE_CHERRY_BG(v)   ImVec4(0.200f, 0.220f, 0.270f, v)
#define LK_IMGUI_STYLE_CHERRY_TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

  auto &style = ImGui::GetStyle();
  style.Colors[ImGuiCol_Text]                  = LK_IMGUI_STYLE_CHERRY_TEXT(0.78f);
  style.Colors[ImGuiCol_TextDisabled]          = LK_IMGUI_STYLE_CHERRY_TEXT(0.28f);
  style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
  style.Colors[ImGuiCol_ChildBg]               = LK_IMGUI_STYLE_CHERRY_BG( 0.58f);
  style.Colors[ImGuiCol_PopupBg]               = LK_IMGUI_STYLE_CHERRY_BG( 0.9f);
  //style.Colors[ImGuiCol_Border]                = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
  //style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_FrameBg]               = LK_IMGUI_STYLE_CHERRY_BG( 1.00f);
  style.Colors[ImGuiCol_FrameBgHovered]        = LK_IMGUI_STYLE_CHERRY_MED( 0.78f);
  style.Colors[ImGuiCol_FrameBgActive]         = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_TitleBg]               = LK_IMGUI_STYLE_CHERRY_LOW( 1.00f);
  style.Colors[ImGuiCol_TitleBgActive]         = LK_IMGUI_STYLE_CHERRY_HI( 1.00f);
  style.Colors[ImGuiCol_TitleBgCollapsed]      = LK_IMGUI_STYLE_CHERRY_BG( 0.75f);
  style.Colors[ImGuiCol_MenuBarBg]             = LK_IMGUI_STYLE_CHERRY_BG( 0.47f);
  style.Colors[ImGuiCol_ScrollbarBg]           = LK_IMGUI_STYLE_CHERRY_BG( 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered]  = LK_IMGUI_STYLE_CHERRY_MED( 0.78f);
  style.Colors[ImGuiCol_ScrollbarGrabActive]   = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
  style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
  style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
  style.Colors[ImGuiCol_Button]                = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
  style.Colors[ImGuiCol_ButtonHovered]         = LK_IMGUI_STYLE_CHERRY_MED( 0.86f);
  style.Colors[ImGuiCol_ButtonActive]          = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_Header]                = LK_IMGUI_STYLE_CHERRY_MED( 0.76f);
  style.Colors[ImGuiCol_HeaderHovered]         = LK_IMGUI_STYLE_CHERRY_MED( 0.86f);
  style.Colors[ImGuiCol_HeaderActive]          = LK_IMGUI_STYLE_CHERRY_HI( 1.00f);
  style.Colors[ImGuiCol_Separator]             = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
  style.Colors[ImGuiCol_SeparatorHovered]      = LK_IMGUI_STYLE_CHERRY_MED( 0.78f);
  style.Colors[ImGuiCol_SeparatorActive]       = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
  style.Colors[ImGuiCol_ResizeGripHovered]     = LK_IMGUI_STYLE_CHERRY_MED( 0.78f);
  style.Colors[ImGuiCol_ResizeGripActive]      = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  // [...]
  style.Colors[ImGuiCol_PlotLines]             = LK_IMGUI_STYLE_CHERRY_TEXT(0.63f);
  style.Colors[ImGuiCol_PlotLinesHovered]      = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_PlotHistogram]         = LK_IMGUI_STYLE_CHERRY_TEXT(0.63f);
  style.Colors[ImGuiCol_PlotHistogramHovered]  = LK_IMGUI_STYLE_CHERRY_MED( 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg]        = LK_IMGUI_STYLE_CHERRY_MED( 0.43f);
  // [...]
  style.Colors[ImGuiCol_ModalWindowDimBg]  = LK_IMGUI_STYLE_CHERRY_BG( 0.73f);

#undef LK_IMGUI_STYLE_CHERRY_HI
#undef LK_IMGUI_STYLE_CHERRY_MED
#undef LK_IMGUI_STYLE_CHERRY_LOW
#undef LK_IMGUI_STYLE_CHERRY_BG
#undef LK_IMGUI_STYLE_CHERRY_TEXT

  style.WindowPadding            = ImVec2(6, 4);
  style.WindowRounding           = 0.0f;
  style.FramePadding             = ImVec2(5, 2);
  style.FrameRounding            = 3.0f;
  style.ItemSpacing              = ImVec2(7, 1);
  style.ItemInnerSpacing         = ImVec2(1, 1);
  style.TouchExtraPadding        = ImVec2(0, 0);
  style.IndentSpacing            = 6.0f;
  style.ScrollbarSize            = 12.0f;
  style.ScrollbarRounding        = 16.0f;
  style.GrabMinSize              = 20.0f;
  style.GrabRounding             = 2.0f;

  style.WindowTitleAlign.x = 0.50f;

  style.Colors[ImGuiCol_Border] = ImVec4(0.539f, 0.479f, 0.255f, 0.162f);
  style.FrameBorderSize = 0.0f;
  style.WindowBorderSize = 1.0f;
}