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
  std::unique_lock<std::mutex> lock_(m_tasks_mutex);
  for (auto it_ = m_tasks.rbegin(); it_ != m_tasks.rend(); ++it_) {
    auto &[id_, task_, ready_, thread_id_] = *it_;
    if (!thread_id_.has_value() || (std::this_thread::get_id() == thread_id_)) {
      if (ready_()) {
        auto task_ret_{std::move(task_)};
        std::string ret_id_{std::move(id_)};
        m_tasks.erase(it_.base());
        return {{std::move(ret_id_), std::move(task_ret_)}};
      }
    }
  }
  return {};
}

std::size_t lk::ready_task_queue::size() const noexcept {
  return m_tasks.size();
}
