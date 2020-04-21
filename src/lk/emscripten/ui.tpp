template<class KeyEvent>
bool lk::ui::ui::handleKeyPressEvent(KeyEvent &event) {
  return m_imgui.handleKeyPressEvent(event);
}

template<class KeyEvent>
bool lk::ui::ui::handleKeyReleaseEvent(KeyEvent &event) {
  return m_imgui.handleKeyReleaseEvent(event);
}

template<class MouseEvent>
bool lk::ui::ui::handleMousePressEvent(MouseEvent &event) {
  return m_imgui.handleMousePressEvent(event);
}

template<class MouseEvent>
bool lk::ui::ui::handleMouseReleaseEvent(MouseEvent &event) {
  return m_imgui.handleMouseReleaseEvent(event);
}

template<class MouseMoveEvent>
bool lk::ui::ui::handleMouseMoveEvent(MouseMoveEvent &event) {
  return m_imgui.handleMouseMoveEvent(event);
}

template<class MouseScrollEvent>
bool lk::ui::ui::handleMouseScrollEvent(MouseScrollEvent &event) {
  return m_imgui.handleMouseScrollEvent(event);
}

template<class TextInputEvent>
bool lk::ui::ui::handleTextInputEvent(TextInputEvent &event)  {
  return m_imgui.handleTextInputEvent(event);
}
