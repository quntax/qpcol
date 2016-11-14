# FlatStyle
FLATSTYLE_HEADERS = \
    $${PWD}/src/flatstyle/fsbutton.h \
    $${PWD}/src/flatstyle/fscontainer.h \
    $${PWD}/src/flatstyle/fsseparator.h \
    $${PWD}/src/flatstyle/fslabel.h \
    $${PWD}/src/flatstyle/FlatStyle

FLATSTYLE_SOURCES += \
    $${PWD}/src/flatstyle/fsbutton.cpp \
    $${PWD}/src/flatstyle/fscontainer.cpp \
    $${PWD}/src/flatstyle/fsseparator.cpp \
    $${PWD}/src/flatstyle/fslabel.cpp

# QHttpRequest
QHTTPREQUEST_HEADERS = \
    $${PWD}/src/qhttprequest/qhttprequest.h \
    $${PWD}/src/qhttprequest/qhttprequestabstract.h \
    $${PWD}/src/qhttprequest/qhttprequestproxy.h \
    $${PWD}/src/qhttprequest/qhttpdownload.h \
    $${PWD}/src/qhttprequest/qhttphash.h \
    $${PWD}/src/qhttprequest/QHttpRequest

QHTTPREQUEST_SOURCES = \
    $${PWD}/src/qhttprequest/qhttprequest.cpp \
    $${PWD}/src/qhttprequest/qhttprequestabstract.cpp \
    $${PWD}/src/qhttprequest/qhttprequestproxy.cpp \
    $${PWD}/src/qhttprequest/qhttpdownload.cpp \
    $${PWD}/src/qhttprequest/qhttphash.cpp \

# MediaWidget
MEDIAWIDGET_HEADERS = \
    $${PWD}/src/mediawidget/downloaddialog.h \
    $${PWD}/src/mediawidget/mediaplayer.h \
    $${PWD}/src/mediawidget/mediawidget.h \
    $${PWD}/src/mediawidget/MediaWidget

MEDIAWIDGET_SOURCES = \
    $${PWD}/src/mediawidget/downloaddialog.cpp \
    $${PWD}/src/mediawidget/mediaplayer.cpp \
    $${PWD}/src/mediawidget/mediawidget.cpp

# MplayerWidget
MPLAYERWIDGET_HEADERS = \
    $${PWD}/src/mplayerwidget/mplayerdispatcher.h \
    $${PWD}/src/mplayerwidget/mplayerparams.h \
    $${PWD}/src/mplayerwidget/mplayerprocess.h \
    $${PWD}/src/mplayerwidget/mplayerslave.h \
    $${PWD}/src/mplayerwidget/mplayerwidget.h \
    $${PWD}/src/mplayerwidget/MplayerWidget

MPLAYERWIDGET_SOURCES = \
    $${PWD}/src/mplayerwidget/mplayerdispatcher.cpp \
    $${PWD}/src/mplayerwidget/mplayerprocess.cpp \
    $${PWD}/src/mplayerwidget/mplayerwidget.cpp

# PTable
PTABLE_HEADERS = \
    $${PWD}/src/ptable/ptable.h \
    $${PWD}/src/ptable/ptablewidget.h \
    $${PWD}/src/ptable/ptableview.h \
    $${PWD}/src/ptable/PTable

PTABLE_SOURCES = \
    $${PWD}/src/ptable/ptablewidget.cpp \
    $${PWD}/src/ptable/ptableview.cpp

# HtmlExtract & FileContents classes
HTMLEXTRACT_HEADERS = \
    $${PWD}/src/htmlextract/filecontents.h \
    $${PWD}/src/htmlextract/html.h \
    $${PWD}/src/htmlextract/htmlextract.h \
    $${PWD}/src/htmlextract/HtmlExtract

HTMLEXTRACT_SOURCES = \
    $${PWD}/src/htmlextract/filecontents.cpp \
    $${PWD}/src/htmlextract/htmlextract.cpp

# MWidgets library includes
MWIDGETS_LIBRARY_HEADERS = \
    $${PWD}/src/mwidgets_global.h \
    $${PWD}/src/mwidgets.h \
    $${PWD}/src/MWidgets

# Components setup
# Required components:
! defined(FLATSTYLE, var) || \
! defined(MPLAYERWIDGET, var) || \
! defined(PTABLE, var) || \
! defined(HTMLEXTRACT, var) {
    message(Standard components: FLATSTYLE MPLAYERWIDGET PTABLE HTMLEXTRACT)

    DEFINES *= FLATSTYLE MPLAYERWIDGET PTABLE HTMLEXTRACT
    INCLUDEPATH += \
        $${PWD}/src/flatstyle \
        $${PWD}/src/mplayerwidget \
        $${PWD}/src/ptable \
        $${PWD}/src/htmlextract

    MWIDGETS_PLUGIN_HEADERS += $${PWD}/src/mplayerwidget/mplayerwidgetplugin.h
    MWIDGETS_PLUGIN_SOURCES += $${PWD}/src/mplayerwidget/mplayerwidgetplugin.cpp

    MWIDGETS_PLUGIN_HEADERS += \
        $${PWD}/src/ptable/ptablewidgetplugin.h \
        $${PWD}/src/ptable/ptableviewplugin.h
    MWIDGETS_PLUGIN_SOURCES += \
        $${PWD}/src/ptable/ptablewidgetplugin.cpp \
        $${PWD}/src/ptable/ptableviewplugin.cpp

    HEADERS += \
        $$FLATSTYLE_HEADERS \
        $$MPLAYERWIDGET_HEADERS \
        $$PTABLE_HEADERS \
        $$HTMLEXTRACT_HEADERS

    SOURCES += \
        $$FLATSTYLE_SOURCES \
        $$MPLAYERWIDGET_SOURCES \
        $$PTABLE_SOURCES \
        $$HTMLEXTRACT_SOURCES
}

# Optional components:
defined(MEDIAWIDGET, var) {
    message(Using MEDIAWIDGET)

    DEFINES *= QHTTPREQUEST MEDIAWIDGET
    INCLUDEPATH += \
        $${PWD}/src/qhttprequest \
        $${PWD}/src/mediawidget

    HEADERS += $$QHTTPREQUEST_HEADERS $$MEDIAWIDGET_HEADERS
    SOURCES += $$QHTTPREQUEST_SOURCES $$MEDIAWIDGET_SOURCES

    MWIDGETS_PLUGIN_HEADERS += $${PWD}/src/mediawidget/mediawidgetplugin.h
    MWIDGETS_PLUGIN_SOURCES += $${PWD}/src/mediawidget/mediawidgetplugin.cpp

    QT += network phonon4qt5
}

defined(QHTTPREQUEST, var) {
    message(Using QHTTPREQUEST)

    DEFINES *= QHTTPREQUEST
    INCLUDEPATH += $${PWD}/src/qhttprequest

    HEADERS += $$QHTTPREQUEST_HEADERS
    SOURCES += $$QHTTPREQUEST_SOURCES

    QT += network
}

MWIDGETS_PLUGIN_HEADERS += $${PWD}/src/plugin/mwidgetsplugin.h
MWIDGETS_PLUGIN_SOURCES += $${PWD}/src/plugin/mwidgetsplugin.cpp

!isEmpty(BUILD_MODE) {
    CONFIG += $$BUILD_MODE
}

!isEmpty(MWIDGETS_RELEASE) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

CONFIG(release, debug|release):
    QMAKE_STRIP             =  strip
    QMAKE_STRIPFLAGS_LIB    += --strip-unneeded

defined(MWIDGETS_LIBRARY, var) {
    message(Building library)

    HEADERS *= $$MWIDGETS_LIBRARY_HEADERS
    SOURCES *= $$MWIDGETS_LIBRARY_SOURCES
}

defined(MWIDGETS_PLUGIN, var) {
    message(Building designer plugin)

    HEADERS *= $$MWIDGETS_LIBRARY_HEADERS $$MWIDGETS_PLUGIN_HEADERS
    SOURCES *= $$MWIDGETS_PLUGIN_SOURCES
}

isEmpty(PREFIX) {
    PREFIX=/usr/local
}

VERSION     = $$cat($${PWD}/VERSION)
DEFINES     += MWIDGETS_VERSION=\\\"$${VERSION}\\\" VERSION=\\\"$${VERSION}\\\"
