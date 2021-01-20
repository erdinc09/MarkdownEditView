cmake_minimum_required(VERSION 3.10)

# Remove when sharing with others.
list(APPEND CMAKE_PREFIX_PATH "/Users/erdincyilmaz/Projects/qt-creator-4.14/qtcreator_build")

include("cmake/HunterGate.cmake")
huntergate(URL "https://github.com/cpp-pm/hunter/archive/v0.23.279.tar.gz" SHA1 "0a8ede485c3e9c1ceed8ccb989ab6c0aba1f4db7")

project(MarkdownEditView)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})

add_subdirectory(external/adif)
add_subdirectory(external/aeb)

include_directories("./external/aeb""./external/adif")

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
    markdowneditview.cpp
    markdowneditview.h
    markdowneditview_global.h
    markdowneditviewconstants.h
    markdowneditviewplugininternal.cpp
    markdowneditviewplugininternal.h
    markdowntexteditorwidget.cpp
    markdowntexteditorwidget.h
    markdowntexteditorfactory.cpp
    markdowntexteditorfactory.h
    previewpage.cpp
    previewpage.h
    htmlview.cpp
    htmlview.h
    htmlviewwidgetfactory.cpp
    htmlviewwidgetfactory.h
    ihtmlview.h
    imarkdowneditview.h
    textchangedevent.h
    )
