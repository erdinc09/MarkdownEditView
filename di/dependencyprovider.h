#ifndef DEPENDENCYPROVIDER2_H
#define DEPENDENCYPROVIDER2_H
#include <exception>
#include <iostream>
#include <string>

#include "dependencyprovider_impl.h"
#include "idiclient.h"

namespace adif {

inline void initilizeAndShutDown() {
  internal::DependencyProvider::initilizeAndShutDown();
}

template <typename...>
constexpr auto make_false() {
  return false;
}

template <typename... types>

class Provides {  // no final class and no private default constructor in order
                  // to show that  "more than 3 interface is not supported" in
                  // compile error, when not used appropriately
 public:
  Provides() {
    static_assert(make_false<types...>(),
                  "more than 3 interface is not supported");
  }
};

template <typename T>
class Provides<T> : public T, internal::IDIClient {
  void provideDependencies(
      internal::DependencyProvider& depencyProvider) final override {
    depencyProvider.provideDependency<T>(this);
  }

  void getDependencies(internal::DependencyProvider&) final override{};

  void checkDependenciesInitilized() override{};
};

template <typename T, typename U>
class Provides<T, U> : public T, U, internal::IDIClient {
  void provideDependencies(
      internal::DependencyProvider& depencyProvider) final override {
    depencyProvider.provideDependency<T>(this);
    depencyProvider.provideDependency<U>(this);
  }

  void getDependencies(internal::DependencyProvider&) final override{};

  void checkDependenciesInitilized() override{};
};

template <typename T, typename U, typename X>
class Provides<T, U, X> : public T, public U, public X, internal::IDIClient {
  void provideDependencies(
      internal::DependencyProvider& dependencyProvider) final override {
    dependencyProvider.provideDependency<T>(this);
    dependencyProvider.provideDependency<U>(this);
    dependencyProvider.provideDependency<X>(this);
  }

  void getDependencies(internal::DependencyProvider&) final override{};

  void checkDependenciesInitilized() override{};
};

template <typename T>
class Injects final : public internal::IDIClient {
 private:
  T* dependency{nullptr};

  void getDependencies(
      internal::DependencyProvider& dependencyProvider) override {
    dependency = dependencyProvider.getDependency<T>();
  }

  void provideDependencies(internal::DependencyProvider&) override {}

#ifdef DEPENDECY_CHECK
  void checkDependenciesInitilized() override {
    if (dependency == nullptr) {
      std::string msg("variable named");
      msg.append(" \"" + variableName + "\"")
          .append(" is not  injected")
          .append(", Here: ")
          .append(fileName)
          .append(":")
          .append(std::to_string(lineNumber));
      throw std::runtime_error(msg);
    }
  };

  std::string variableName;
  std::string fileName;
  int lineNumber;
#else
  void checkDependenciesInitilized() final override {}
#endif

  bool isDependencyInitilized() { return dependency != nullptr; }

 public:
#ifdef DEPENDECY_CHECK
  Injects(const std::string& variableName_, const std::string& fileName_,
          const int lineNumber_)
      : variableName{variableName_},
        lineNumber{lineNumber_},
        fileName{fileName_} {};
#endif
  T* operator->() const {
#ifdef DEPENDECY_CHECK
    if (dependency == nullptr) {
      std::string msg(
          "adif is not initilized, did you miss to call  "
          "\"adif::initilizeAndShutDown()\" ?");
      throw std::runtime_error(msg);
    }
#endif
    return dependency;
  }
  operator T*() const {
#ifdef DEPENDECY_CHECK
    if (dependency == nullptr) {
      std::string msg(
          "adif is not initilized, did you miss to call  "
          "\"adif::initilizeAndShutDown()\" ?");
      throw std::runtime_error(msg);
    }
#endif
    return dependency;
  }
};

/*
 * @... the interfaces that the class provides.
 */
#define Provides(...) \
 public               \
  adif::Provides<__VA_ARGS__>

#ifdef DEPENDECY_CHECK
/*
 *@type type of the variable
 *@name name of the variable
 */
#define Injects(type, name) \
  adif::Injects<type> name { #name, __FILE__, __LINE__ }
#else
/**
 *@type type of the variable
 *@name name of the variable
 */
#define Injects(type, name) \
  adif::Injects<type> name {}
#endif

/*<deprecated_macros>*/
#define dependencyCheck1(a)                                                  \
  void c##heckDependenciesInitilized() override {                            \
    if (!a.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#a).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
  }

#define dependencyCheck2(a, b)                                               \
  void c##heckDependenciesInitilized() override {                            \
    if (!a.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#a).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
    if (!b.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#b).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
  }

#define dependencyCheck3(a, b, c)                                            \
  void c##heckDependenciesInitilized() override {                            \
    if (!a.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#a).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
    if (!b.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#b).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
    if (!c.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#c).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
  }

#define dependencyCheck4(a, b, c, d)                                         \
  void c##heckDependenciesInitilized() override {                            \
    if (!a.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#a).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
    if (!b.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#b).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
                                                                             \
    if (!c.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#c).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
    if (!d.isDependencyInitilized()) {                                       \
      std::cerr << std::string(#d).append(" is not  injected") << std::endl; \
      assert(false);                                                         \
    }                                                                        \
  }

/*</deprecated_macros>*/

}  // namespace adif
#endif  // DEPENDENCYPROVIDER2_H
