#pragma once

#include <unordered_map>
#include <vector>

using EventListenerList = std::vector<void*>;

namespace aeb {

/*forward decalerations for friends*/
template <class T>
class EventListener;

template <class T>
class EventBus;

template <typename Event>
void postEvent(const Event& event);

namespace internal {
class EventBus_Impl {
 private:
  EventBus_Impl() = default;
  std::unordered_map<int, std::shared_ptr<EventListenerList>> instances;
  static EventBus_Impl globalEventBus;
  static void addEventListener(int id, void* listener);
  static void removeEventListener(int id, void* listener);

  /*friends*/

  template <class T>
  friend class ::aeb::EventListener;

  template <class T>
  friend class ::aeb::EventBus;

  template <typename Event>
  friend void ::aeb::postEvent(const Event& event);
};
}  // namespace internal
}  // namespace aeb
