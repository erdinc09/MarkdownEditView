cmake_minimum_required(VERSION 3.10)


#You need this only if you change the build type in QtCreator while building in it.
#list(APPEND CMAKE_PREFIX_PATH "/Users/erdinc09/Projects/qt-creator-4.14.2/qtcreator_build")
#list(APPEND CMAKE_PREFIX_PATH "/Users/erdinc09/Qt/5.15.2/clang_64")

include("external/cmake/HunterGate.cmake")
huntergate(URL "https://github.com/cpp-pm/hunter/archive/v0.23.279.tar.gz" SHA1 "0a8ede485c3e9c1ceed8ccb989ab6c0aba1f4db7")

project(MarkdownEditView)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions("-DQT_NO_DEBUG_OUTPUT")
endif()


find_package(Qt5 COMPONENTS WebEngineWidgets WebChannel REQUIRED)
find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})

add_subdirectory(external/adif)
add_subdirectory(external/aeb)


file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    MarkdownEditView.json.in)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/external/aeb"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/adif")

add_qtc_plugin(MarkdownEditView

    PLUGIN_DEPENDS
    QtCreator::Core

    DEPENDS
    ${QtX}::Widgets
    ${QtX}::WebEngineWidgets
    ${QtX}::WebChannel
    QtCreator::ExtensionSystem
    QtCreator::Utils
    QtCreator::TextEditor
    adif
    aeb

    SOURCES
    .github/workflows/build_cmake.yml
    .github/workflows/README.md
    README.md
    resources/resource.qrc
    ${SRC_FILES}
    ${SYNTAX_HIGHLIGHTER_FILES}
    )

set(INDEX_TEMPLATE_HTML "${CMAKE_CURRENT_SOURCE_DIR}/resources/index_template.html")
set(INDEX_DARK_HTML "${CMAKE_CURRENT_SOURCE_DIR}/resources/index_dark.html")
set(INDEX_LIGHT_HTML "${CMAKE_CURRENT_SOURCE_DIR}/resources/index_light.html")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlgenerator.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlgenerator.h
  @ONLY
  )

# html file generator. This generated files enables the plugin adapt to qtcreator theme (dark & classic)
add_executable(htmlgenerator
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlgenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlgenerator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/htmlgenerator.h.in)

target_link_libraries(htmlgenerator Qt${QT_VERSION_MAJOR}::Core)
