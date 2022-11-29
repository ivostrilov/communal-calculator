#ifndef SOURCEFILES_MODEL_CORE_OBSERVER_H_
#define SOURCEFILES_MODEL_CORE_OBSERVER_H_

#include <functional>
#include <shared_mutex>
#include <utility>

namespace CommunalCalculator::Core {

template <typename T>
class Observer final {
 public:
  using Connection = std::function<void()>;

  Observer() = default;
  Observer(const Observer &) = delete;
  Observer(Observer &&) = delete;

  auto operator=(const Observer &) -> Observer & = delete;
  auto operator=(Observer &&) -> Observer & = delete;

  ~Observer() = default;

  void SetConnection(Connection &&connection) {
    connection_ = std::move(connection);
  }

  template <typename Data>
  void Push(Data &&data) {
    {
      std::unique_lock lock(access_);
      data_ = std::forward<Data>(data);
    }

    if (connection_) {
      connection_();
    }
  }

  auto PullCopy() -> T {
    std::shared_lock lock(access_);
    return data_;
  }

 private:
  std::shared_mutex access_;
  T data_;

  Connection connection_;
};

}  // namespace CommunalCalculator::Core

#endif  // SOURCEFILES_MODEL_CORE_OBSERVER_H_
