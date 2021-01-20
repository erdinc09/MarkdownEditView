#pragma once
#include <typeinfo>

#include "eventbus_impl.h"

namespace aeb {

template <typename Event>
class EventListener {
 public:
  EventListener() {
    internal::EventBus_Impl::addEventListener(typeid(Event).hash_code(), this);
  }
  ~EventListener() {
    internal::EventBus_Impl::removeEventListener(typeid(Event).hash_code(),
                                                 this);
  }

 private:
  virtual void handleEvent(const Event& event) = 0;

  /*friends*/
  template <typename T>
  friend class EventBus;

  template <typename Event_>
  friend void postEvent(const Event_& event);
};
}  // namespace aeb
