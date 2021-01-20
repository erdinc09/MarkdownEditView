#pragma once

#include "eventbus_impl.h"
#include "eventlistener.h"

namespace aeb {

template <typename Event>
void postEvent(const Event& event) {
  auto hash = typeid(Event).hash_code();
  auto listenersit =
      internal::EventBus_Impl::globalEventBus.instances.find(hash);
  if (listenersit != internal::EventBus_Impl::globalEventBus.instances.end()) {
    std::for_each(
        listenersit->second->begin(), listenersit->second->end(),
        [&event](void* listener) {
          static_cast<EventListener<Event>*>(listener)->handleEvent(event);
        });
  }
}

}  // namespace aeb
