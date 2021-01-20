#ifndef IDICLIENT_H
#define IDICLIENT_H
#include "dependencyprovider_impl.h"
namespace adif {

/*forward declerations for friends*/
template <typename T>
class Injects;

template <typename... types>
class Provides;

namespace internal {

class IDIClient {
 private:
  IDIClient();
  virtual void provideDependencies(DependencyProvider& depencyProvider) = 0;
  virtual void getDependencies(DependencyProvider& depencyProvider) = 0;
  virtual void checkDependenciesInitilized() = 0;

  /*friends*/
  friend class DependencyProvider;

  template <typename T>
  friend class ::adif::Injects;

  template <typename... types>
  friend class ::adif::Provides;
};
}  // namespace internal
}  // namespace adif

#endif  // IDICLIENT_H
