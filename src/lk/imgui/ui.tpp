template<class KeyEvent>
bool lk::imgui::ui::handleKeyPressEvent(KeyEvent &event) {
  return m_imgui.handleKeyPressEvent(event);
}

template<class KeyEvent>
bool lk::imgui::ui::handleKeyReleaseEvent(KeyEvent &event) {
  return m_imgui.handleKeyReleaseEvent(event);
}

template<class MouseEvent>
bool lk::imgui::ui::handleMousePressEvent(MouseEvent &event) {
  return m_imgui.handleMousePressEvent(event);
}

template<class MouseEvent>
bool lk::imgui::ui::handleMouseReleaseEvent(MouseEvent &event) {
  return m_imgui.handleMouseReleaseEvent(event);
}

template<class MouseMoveEvent>
bool lk::imgui::ui::handleMouseMoveEvent(MouseMoveEvent &event) {
  return m_imgui.handleMouseMoveEvent(event);
}

template<class MouseScrollEvent>
bool lk::imgui::ui::handleMouseScrollEvent(MouseScrollEvent &event) {
  return m_imgui.handleMouseScrollEvent(event);
}

template<class TextInputEvent>
bool lk::imgui::ui::handleTextInputEvent(TextInputEvent &event)  {
  return m_imgui.handleTextInputEvent(event);
}
