#ifndef LINKATA_SRC_LK_READY_TASK_QUEUE_HPP_
#define LINKATA_SRC_LK_READY_TASK_QUEUE_HPP_
#pragma once

#include <lk/lk.hpp>

#include <any>
#include <functional>
#include <future>
#include <map>
#include <optional>
#include <tuple>
#include <vector>

namespace lk {
  class ready_task_queue {
   public:
    using task_type = std::packaged_task<std::any()>;
    using ready_type = std::function<bool()>;

    void pushTask(
        std::string id_,
        task_type &&task_,
        ready_type &&ready_ = []() -> bool { return true; },
        std::optional<std::thread::id> thread_id_ = {}
    );
    std::optional<std::pair<std::string, task_type>> popReadyTask();
    [[nodiscard]] std::size_t size() const noexcept;

   private:
    using entry = std::tuple<std::string, task_type, ready_type, std::optional<std::thread::id>>;
    std::vector<entry> m_tasks{};
    std::mutex m_tasks_mutex{};
  };
}

#endif //LINKATA_SRC_LK_READY_TASK_QUEUE_HPP_
