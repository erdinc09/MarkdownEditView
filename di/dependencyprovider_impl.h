#ifndef DEPENDENCYPROVIDER_H
#define DEPENDENCYPROVIDER_H
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <vector>

namespace adif {

/*forward declarations for friends*/
template <typename T>
class Injects;

template <typename...>
class Provides;

void initilizeAndShutDown();

namespace internal {
class IDIClient;

class DependencyProvider final {
 private:
  DependencyProvider() = default;
  ~DependencyProvider() = default;

  void clear();

  template <typename T>
  void provideDependency(T* const instance);

  template <typename T>
  T* getDependency();

  std::unordered_map<int, void*> instances;
  static std::vector<IDIClient*> clientList;
  static DependencyProvider dependencyProvider;

  static void initilizeAndShutDown();
  static void addClient(IDIClient* const client);

  /*friends*/
  friend class IDIClient;

  template <typename T>
  friend class ::adif::Injects;

  template <typename...>
  friend class ::adif::Provides;

  friend void ::adif::initilizeAndShutDown();
};

template <typename T>
void DependencyProvider::provideDependency(T* instance) {
  auto hash = typeid(T).hash_code();
  if (!dependencyProvider.instances.emplace(hash, instance).second) {
    throw std::invalid_argument(
        std::string(typeid(T).name())
            .append(" = (typeid(<interface type>).name()) is alredy registered "
                    "before"));
  }
}

template <typename T>
T* DependencyProvider::getDependency() {
  auto hash = typeid(T).hash_code();
  auto itr1 = dependencyProvider.instances.find(hash);
  if (itr1 != dependencyProvider.instances.end()) {
    return static_cast<T*>(itr1->second);
  } else {
    // I do not throw ex here because if I do, there would be no detailed
    // message. Later I throw std::runtime_error with detailed message with
    // file,line and varible name.
    return nullptr;
  }
}
}  // namespace internal
}  // namespace adif

#endif  // DEPENDENCYPROVIDER_H
