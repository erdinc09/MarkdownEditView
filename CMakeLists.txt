cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
huntergate(URL "https://github.com/cpp-pm/hunter/archive/v0.23.279.tar.gz" SHA1 "0a8ede485c3e9c1ceed8ccb989ab6c0aba1f4db7")

project(MarkdownEditView)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS WebEngineWidgets WebChannel REQUIRED)
find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})

#find submodules and initiate them
unset(ADIF_INCLUDE CACHE)
find_path(ADIF_INCLUDE NAMES "CMakeLists.txt" PATHS ./external/adif)
if((NOT ADIF_INCLUDE) OR (NOT EXISTS ${ADIF_INCLUDE}))
    message("Unable to find adif")
    execute_process(COMMAND git submodule update --init -- external/adif
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

unset(AEB_INCLUDE CACHE)
find_path(AEB_INCLUDE NAMES "CMakeLists.txt" PATHS ./external/aeb)
if((NOT AEB_INCLUDE) OR (NOT EXISTS ${AEB_INCLUDE}))
    message("Unable to find aeb")
    execute_process(COMMAND git submodule update --init -- external/aeb
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_subdirectory(external/adif)
add_subdirectory(external/aeb)

include_directories("./external/aeb" "./external/adif")

file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_qtc_plugin(MarkdownEditView

    PLUGIN_DEPENDS
    QtCreator::Core

    DEPENDS
    adif
    aeb
    ${QtX}::Widgets
    ${QtX}::WebEngineWidgets
    ${QtX}::WebChannel
    QtCreator::ExtensionSystem
    QtCreator::Utils
    QtCreator::TextEditor

    SOURCES
    .github/workflows/build_cmake.yml
    .github/workflows/README.md
    README.md
    resources/resource.qrc
    ${SRC_FILES}
    )
