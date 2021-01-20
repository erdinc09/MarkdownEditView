#include <algorithm>

#include "dependencyprovider_impl.h"
#include "idiclient.h"

namespace adif {
namespace internal {
std::vector<IDIClient*> DependencyProvider::clientList;

DependencyProvider DependencyProvider::dependencyProvider;

void DependencyProvider::clear() { instances.clear(); }

void DependencyProvider::addClient(IDIClient* const client) {
  clientList.push_back(client);
}

void DependencyProvider::initilizeAndShutDown() {
  std::for_each(clientList.rbegin(), clientList.rend(), [](auto client) {
    client->provideDependencies(dependencyProvider);
  });

  std::for_each(clientList.rbegin(), clientList.rend(), [](auto client) {
    client->getDependencies(dependencyProvider);
  });

#ifdef DEPENDECY_CHECK
  std::for_each(clientList.rbegin(), clientList.rend(),
                [](auto client) { client->checkDependenciesInitilized(); });
#endif
  dependencyProvider.clear();
  clientList.clear();
}
}  // namespace internal
}  // namespace adif
