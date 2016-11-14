# MWidgets

Small set of custom Qt widgets, build over QWidget and Phonon, intended
to use in Qt apps (also from Qt Designer).
Currently it's being in  maintenance mode only, no further development.
Havoc toolkit is my other project that's going to replace (and improve) mwidgets.
Last thing to do here is to refactor it and allow modular/static (generally - customized) 
build configuration.

## Contents

* FlatStyle
Labels, with pre-defined styling.

* QHttpRequest(*)
Set of classes for downloading files over HTTP protocol

* MediaWidget (*)
Multimedia widget with controls, build over Phonon::MediaPlayer

* MplayerWidget
Widget with embedded mplayer, using slave mode to dispatch commands to
backend

* PTable
QTableWidget and QTableView that preserve constant columns width ratio when
resizing.

Some other widgets are unfinished

*) Names marked with astersk are eithger buggy/misbehavuing, discouraged to use
or deprecated. They are disableby default build (not included in m,widgets
libnrary).

## Designer plugin

Designer plugin is also available, adds section "Multimedia Widgets". Currently - disabled
due to library refactoring.

## Installation

Execute following commands to install in the same prefix dir as Qt libraries:

<pre>
$ qmake \
    DESIGNER_PLUGIN_INSTALL_DIR=$(qmake -query QT_INSTALL_PLUGINS) \
    BUILD_MODE=release \
    MWIDGETS_RELEASE=1 \
    PREFIX=$(qmake -query QT_INSTALL_PREFIX) \
    <root_mwidgets_directory>

$ make -j$(nproc)
# make install
</pre>

Last command executed as root. In project root _build.sh_ script is located, wihch does the same job, except install.

For archlinux users, build directory contains also PKGBUILD file.

## TODO

See TODO.md file

## Bugs

See ISSUES.md file
