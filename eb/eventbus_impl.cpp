#include "eventbus_impl.h"

#include <algorithm>
#include <typeinfo>

#include "eventlistener.h"
namespace aeb {
namespace internal {
EventBus_Impl EventBus_Impl::globalEventBus;

void EventBus_Impl::addEventListener(int id, void* listener) {
  auto listeners = globalEventBus.instances.find(id);
  if (listeners == globalEventBus.instances.end()) {
    std::shared_ptr<EventListenerList> listenerList =
        std::make_shared<EventListenerList>();
    listenerList->push_back(listener);
    globalEventBus.instances.emplace(id, listenerList);
  } else {
    listeners->second->push_back(listener);
  }
}

void EventBus_Impl::removeEventListener(int id, void* listener) {
  auto listeners = globalEventBus.instances.find(id);
  if (listeners != globalEventBus.instances.end()) {
    auto listenerPos = std::find(listeners->second->begin(),
                                 listeners->second->end(), listener);
    if (listenerPos != listeners->second->end()) {
      listeners->second->erase(listenerPos);
    }

    if (listeners->second->size() == 0) {
      globalEventBus.instances.erase(id);
    }
  }
}
}  // namespace internal
}  // namespace aeb
