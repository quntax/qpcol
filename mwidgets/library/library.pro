DEFINES     += MWIDGETS_LIBRARY

include($${PWD}/../mwidgets.pri)

QT          += core gui widgets
TARGET      = mwidgets
TEMPLATE    = lib
CONFIG      += create_prl no_install_prl create_pc

OTHER_FILES += \
    $${PWD}/../mwidgets.pri \
    $${PWD}/../README.md \
    $${PWD}/../ISSUES.md \
    $${PWD}/../TODO.md \
    $${PWD}/../VERSION

QMAKE_CXXFLAGS_RELEASE = -O2 -march=native -pipe -fomit-frame-pointer
QMAKE_LFLAGS_RPATH=

target.path         = $${PREFIX}/lib

includes.target     = library_headers
includes.files      = $${HEADERS} $${PWD}/src/MWidgets
includes.path       = $${PREFIX}/include/mwidgets

INSTALLS = target includes

PCFILES              = \
    $${PWD}/pkgconfig/$${TARGET}.pc \
    $${PWD}/lib$${TARGET}.prl

QMAKE_PKGCONFIG_NAME        = $${TARGET}
QMAKE_PKGCONFIG_DESCRIPTION = Set of multimedia widgets for Qt
QMAKE_PKGCONFIG_PREFIX      = $${PREFIX}
QMAKE_PKGCONFIG_LIBDIR      = $$target.path
QMAKE_PKGCONFIG_INCDIR      = $$includes.path
QMAKE_PKGCONFIG_DESTDIR     = pkgconfig
QMAKE_PKGCONFIG_VERSION     = $${VERSION}
QMAKE_PKGCONFIG_VARIABLES   = \
    $$FLATSTYLE \
    $$QHTTPREQUEST \
    $$MEDIAWIDGET \
    $$MPLAYERWIDGET \
    $$PTABLE \
    $$HTMLEXTRACT
