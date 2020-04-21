//
// Created by but on 1/6/2020.
//

#include "ui.hpp"

lk::ui::emscripten::ui::ui(
    Magnum::Platform::Application &application_,
    ready_task_queue &task_queue_
) : m_application{application_},
    m_taskQueue{task_queue_} {

}
