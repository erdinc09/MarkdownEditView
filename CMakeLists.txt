cmake_minimum_required(VERSION 3.10)

# Remove when sharing with others.
list(APPEND CMAKE_PREFIX_PATH "/Users/erdincyilmaz/Projects/qt-creator-4.14/qtcreator_build")

project(MarkdownEditView)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
set(QtX Qt${QT_VERSION_MAJOR})


# "another di framework" checks dependencies are wired.
add_definitions(-DDEPENDECY_CHECK)

add_library(di
    STATIC
    di/idiclient.h
    di/idiclient.cpp
    di/dependencyprovider_impl.cpp
    di/dependencyprovider_impl.h
    di/dependencyprovider.h
    )

add_library(eb
    STATIC
    eb/eventbus_impl.h
    eb/eventbus_impl.cpp
    eb/eventlistener.h
    eb/eventbus.h
    )

add_qtc_plugin(MarkdownEditView

    PLUGIN_DEPENDS
    QtCreator::Core

    DEPENDS
    di
    eb
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
