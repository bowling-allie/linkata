#include "ready_task_queue.hpp"

void lk::ready_task_queue::pushTask(
    std::string id_,
    task_type &&task_,
    ready_type &&ready_,
    std::optional<std::thread::id> thread_id_) {
  std::lock_guard<std::mutex> lock_{m_tasks_mutex};
  m_tasks.emplace_back(
      std::move(id_),
      std::move(task_),
      std::move(ready_),
      std::move(thread_id_)
  );
}

std::optional<std::pair<std::string, lk::ready_task_queue::task_type>> lk::ready_task_queue::popReadyTask() {
  std::lock_guard<std::mutex> lock_{m_tasks_mutex};
  for (auto it_ = m_tasks.rbegin(); it_ != m_tasks.rend(); ++it_) {
    auto &[id_, task_, ready_, thread_id_] = *it_;
    if (!thread_id_.has_value() || (std::this_thread::get_id() == thread_id_)) {
      if (ready_()) {
        std::string id_out_{std::move(id_)};
        auto task_out_{std::move(task_)};
        m_tasks.erase(it_.base() - 1);
        return {{std::move(id_out_), std::move(task_out_)}};
      }
    }
  }
  return {};
}

std::size_t lk::ready_task_queue::size() const noexcept {
  return m_tasks.size();
}
