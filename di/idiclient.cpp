#include "idiclient.h"
namespace adif {
namespace internal {
IDIClient::IDIClient() { DependencyProvider::addClient(this); }
}  // namespace internal
}  // namespace adif
