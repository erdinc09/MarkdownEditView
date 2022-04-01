# MarkdownEditView
Qt Creator IDE markdown plugin, for both editing and previewing the file in html.

__Features:__

* Syntax highlighting in editor
* Html preview
* Code highlighting in preview
* Theme aware preview and editor
* Bidirectional vertical sroll synchronization between editor and preview

__Dark Theme Screen Shot:__
![](./doc/dark.png)

__Classic Theme Screen Shot:__
![](./doc/light.png)


## How To Install

* For Linux, MacOs and Windows you can download the plugin from [releases](https://github.com/erdinc09/MarkdownEditView/releases).
* Since QtCreator is not packaged with Qt6WebEngine,Qt6WebChannel and Qt6Positioning, you need to install following dependencies from qt installation to qtcreator (qtcreator that MarkdownEditView will be installed!) directory. This process will be automatized later by the plugin.
  * Qt6.2.2 must be installed with Qt6WebEngine, Qt6WebChannel and Qt6Positioning dependency (we will copy the dependencies from here).
  * For __linux:__  
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/lib/libQt6WebChannel.so*       to `<Ct Creator Ins Path>`/lib/Qt/lib  
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/lib/libQt6WebEngineCore.so*    to `<Ct Creator Ins Path>`/lib/Qt/lib
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/lib/libQt6WebEngineWidgets.so* to `<Ct Creator Ins Path>`/lib/Qt/lib
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/lib/libQt6Positioning.so* to `<Ct Creator Ins Path>`/lib/Qt/lib
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/libexec        to `<Ct Creator Ins Path>`/lib/Qt/
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/resources      to `<Ct Creator Ins Path>`/lib/Qt/
    * copy  `<Qt Installation Path>`/6.2.3/gcc_64/translations   to `<Ct Creator Ins Path>`/lib/Qt/
  
Not: Actually for resource, libexec and translations folders only the related files should be copied. But just now, copy all files. I will update later.

  * For __macos:__
    * This is easier than linux. All resource and configuratin files are kept together.
    * copy  `<Qt Installation Path`>/6.2.2/macos/lib/QtWebChannel.framework           to  `<Qt Creator.app`>/Contents/Frameworks/
    * copy  `<Qt Installation Path`>/6.2.2/macos/lib/QtWebEngineCore.framework        to  `<Qt Creator.app`>/Contents/Frameworks/
    * copy  `<Qt Installation Path`>/6.2.2/macos/lib/QtWebEngineWidgets.framework     to  `<Qt Creator.app`>/Contents/Frameworks/
    * copy  `<Qt Installation Path`>/6.2.2/macos/lib/QtPositioning.framework          to  `<Qt Creator.app`>/Contents/Frameworks/
  * For __windows:__
    * Since I do not have Windows machine I cannot write the exact steps but the logic same.
    * By the help of [official qtwebengine6 deployment notes](https://doc-snapshots.qt.io/qt6-dev/qtwebengine-deploying.html) you can copy the related files.
    * As soon as I have a windows machine I will write down exact steps.


## How to Build


* Install Qt 6.2.3 with Qt6WebEngine and Qt6WebChannel (for to build qtcreator Qt6Positioning and Qt5 Compatibility also needed).
* Follow command below:

__For Linux:__

first, get qt-crator and build it:

* git clone https://github.com/qt-creator/qt-creator.git
* cd ./qt-creator
* git checkout v7.0.0
* mkdir qtcreator_build
* cd ./qtcreator_build
* cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja "-DCMAKE_PREFIX_PATH=/home/erdinc09/Qt/6.2.3/gcc_64" ..
* cmake --build .

then, get MarkdownEditView and build it:

* git clone --recursive -j8 https://github.com/erdinc09/MarkdownEditView.git
* cd ./MarkdownEditView
* mkdir build
* cd ./build
* cmake "-DCMAKE_PREFIX_PATH=/home/erdinc09/git/qt-creator/qtcreator_build;/home/erdinc09/Qt/6.2.3/gcc_64" -DCMAKE_BUILD_TYPE=RelWithDebInfo -GNinja ..
* cmake --build .

__For Mac:__

first, get qt-crator and build it:

* git clone https://github.com/qt-creator/qt-creator.git
* cd ./qt-creator
* git checkout v7.0.0
* mkdir qtcreator_build
* cd ./qtcreator_build
* cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja "-DCMAKE_PREFIX_PATH=/Users/erdinc09/Qt/6.2.3/macos;/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain" ..
* cmake --build .

then, get MarkdownEditView and build it:

* git clone --recursive -j8 https://github.com/erdinc09/MarkdownEditView.git
* cd ./MarkdownEditView
* mkdir build
* cd ./build
* cmake "-DCMAKE_PREFIX_PATH=/Users/erdinc09/git/qt-creator/qtcreator_build;/Users/erdinc09/Qt/6.2.3/macos" -DCMAKE_BUILD_TYPE=RelWithDebInfo -GNinja ..
* cmake --build .

__Note that directory delimeter is same for in all platforms! ";"__


## How to Run (For Development Of Plugin)

Run a compatible Qt Creator with the additional command line argument

    -pluginpath <path_to_plugin>

where `<path_to_plugin>` is the path to the resulting plugin library in the build directory
(`<plugin_build>/lib/qtcreator/plugins` on Windows and Linux,
`<plugin_build>/Qt Creator.app/Contents/PlugIns` on macOS).

You might want to add `-temporarycleansettings` (or `-tcs`) to ensure that the opened Qt Creator
instance cannot mess with your user-global Qt Creator settings.

When building and running the plugin from Qt Creator, you can use

    -pluginpath "%{buildDir}/lib/qtcreator/plugins" -tcs

on Windows and Linux, or

    -pluginpath "%{buildDir}/Qt Creator.app/Contents/PlugIns" -tcs

for the `Command line arguments` field in the run settings


## Credits

* For markdown to html conversion, [marked js library fork](https://github.com/erdinc09/marked) is used (adapted).
* For CSS in preview, [markdown-css](https://github.com/rhiokim/markdown-css) is used.
* For code highlighting in preview [highlightjs](https://highlightjs.org/) is used (10.5).
* For SyntaxHighligter in editor, [qmarkdowntextedit](https://github.com/pbek/qmarkdowntextedit) syntaxhighlighter is used (adapted).
