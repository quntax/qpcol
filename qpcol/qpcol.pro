#-------------------------------------------------
#
# Project created by QtCreator 2010-10-17T18:46:49
#
#-------------------------------------------------

QT  += \
    core \
    gui \
    sql \
    widgets

TARGET      = qpcol
TEMPLATE    = app
CONFIG      += link_pkgconfig autogen_precompile_source
PKGCONFIG   += mwidgets
QMAKE_CXXFLAGS_RELEASE *= -O2 -march=native -pipe -fomit-frame-pointer
QPCOL_SRC = $$_PRO_FILE_PWD_

TRANSLATIONS += $$QPCOL_SRC/lang/qpcol_pl.ts

! isEmpty(QPCOL_PRECOMPILED_HEADERS) {
    DEFINES += USING_PCH
    CONFIG  += precompile_header
    PRECOMPILED_HEADER = $${QPCOL_SRC}/precompiled.h
    HEADERS += $$QPCOL_SRC/precompiled.h
}

QPCOL_VERSION  = $$cat($$QPCOL_SRC/VERSION)
DEFINES         += QPCOL_VERSION="\\\"$$QPCOL_VERSION\\\"" VERSION="\\\"$$QPCOL_VERSION\\\""

isEmpty(QPCOL_RELEASE) {
    message(Using SYSTEM mwidgets)
    CONFIG  += release
    DEFINES += QPCOL_RELEASE
    LIBS    += -lmwidgets
} else {
    message(Using DEBUG mwidgets)
    CONFIG += debug
    PROJECTS_ROOT="/home/merlin/Projekty"
    INCLUDEPATH += \
        $${PROJECTS_ROOT}/mwidgets/src \
        $${PROJECTS_ROOT}/mwidgets/src/flatstyle \
        $${PROJECTS_ROOT}/mwidgets/src/ptable \
        $${PROJECTS_ROOT}/mwidgets/src/mplayerwidget \
        $${PROJECTS_ROOT}/mwidgets/src/htmlextract
##    LIBS    += -L$${QPCOL_SRC}/../build/mwidgets-mplayer-parameters/library -lmwidgets
#    LIBS    += -L$${PROJECTS_ROOT}/build/mwidgets-mplayer-parameters/library -lmwidgets
}

INCLUDEPATH += \
    $$QPCOL_SRC \
    $$QPCOL_SRC/database \
    $$QPCOL_SRC/dirscanner \
    $$QPCOL_SRC/handlers \
    $$QPCOL_SRC/models \
    $$QPCOL_SRC/resources \
    $$QPCOL_SRC/types

SOURCES += \
    $$QPCOL_SRC/main.cpp \
    $$QPCOL_SRC/qpcolapplication.cpp \
    $$QPCOL_SRC/filmtagslistview.cpp \
    $$QPCOL_SRC/filmnotestextedit.cpp \
    $$QPCOL_SRC/mainwindow.cpp \
    $$QPCOL_SRC/database/query.cpp \
    $$QPCOL_SRC/database/database.cpp \
    $$QPCOL_SRC/database/connection.cpp \
    $$QPCOL_SRC/types/tag.cpp \
    $$QPCOL_SRC/types/film.cpp \
    $$QPCOL_SRC/types/options.cpp \
    $$QPCOL_SRC/types/searchresultitem.cpp \
    $$QPCOL_SRC/types/setting.cpp \
    $$QPCOL_SRC/handlers/taghandler.cpp \
    $$QPCOL_SRC/handlers/filehandler.cpp \
    $$QPCOL_SRC/handlers/filmhandler.cpp \
    $$QPCOL_SRC/handlers/videomodelhandler.cpp \
    $$QPCOL_SRC/handlers/tagmodelhandler.cpp \
    $$QPCOL_SRC/handlers/confighandler.cpp \
    $$QPCOL_SRC/handlers/clipboardgrabber.cpp \
    $$QPCOL_SRC/handlers/hashhandler.cpp \
    $$QPCOL_SRC/models/videomodel.cpp \
    $$QPCOL_SRC/models/tagmodel.cpp \
    $$QPCOL_SRC/models/videofilterproxymodel.cpp \
    $$QPCOL_SRC/models/videotagsmodel.cpp \
    $$QPCOL_SRC/dirscanner/dirscanner.cpp \
    $$QPCOL_SRC/videotableview.cpp \
    $$QPCOL_SRC/audioextractor.cpp \
    $$QPCOL_SRC/videotableitemdelegate.cpp \
    $$QPCOL_SRC/tageditor.cpp \
    $$QPCOL_SRC/tagdialog.cpp \
    $$QPCOL_SRC/filmurldialog.cpp \
    $$QPCOL_SRC/settingseditor.cpp \
    $$QPCOL_SRC/timeoffseteditor.cpp

HEADERS += \
    $$QPCOL_SRC/messenger.h \
    $$QPCOL_SRC/qpcolapplication.h \
    $$QPCOL_SRC/filmtagslistview.h \
    $$QPCOL_SRC/filmnotestextedit.h \
    $$QPCOL_SRC/mainwindow.h \
    $$QPCOL_SRC/database/query.h \
    $$QPCOL_SRC/database/database.h \
    $$QPCOL_SRC/database/connection.h \
    $$QPCOL_SRC/types/tag.h \
    $$QPCOL_SRC/types/film.h \
    $$QPCOL_SRC/types/filmtag.h \
    $$QPCOL_SRC/types/options.h \
    $$QPCOL_SRC/types/setting.h \
    $$QPCOL_SRC/handlers/taghandler.h \
    $$QPCOL_SRC/handlers/filehandler.h \
    $$QPCOL_SRC/handlers/filmhandler.h \
    $$QPCOL_SRC/handlers/videomodelhandler.h \
    $$QPCOL_SRC/handlers/tagmodelhandler.h \
    $$QPCOL_SRC/handlers/clipboardgrabber.h \
    $$QPCOL_SRC/handlers/confighandler.h \
    $$QPCOL_SRC/handlers/hashhandler.h \
    $$QPCOL_SRC/models/videomodel.h \
    $$QPCOL_SRC/models/tagmodel.h \
    $$QPCOL_SRC/models/videofilterproxymodel.h \
    $$QPCOL_SRC/models/videotagsmodel.h \
    $$QPCOL_SRC/dirscanner/dirscanner.h \
    $$QPCOL_SRC/videotableitemdelegate.h \
    $$QPCOL_SRC/videotableview.h \
    $$QPCOL_SRC/audioextractor.h \
    $$QPCOL_SRC/tageditor.h \
    $$QPCOL_SRC/tagdialog.h \
    $$QPCOL_SRC/filmurldialog.h \
    $$QPCOL_SRC/settingseditor.h \
    $$QPCOL_SRC/timeoffseteditor.h

FORMS    += \
    $$QPCOL_SRC/forms/mainwindow.ui \
    $$QPCOL_SRC/forms/tageditor.ui \
    $$QPCOL_SRC/forms/tagdialog.ui \
    $$QPCOL_SRC/forms/filmurldialog.ui \
    $$QPCOL_SRC/forms/settingseditor.ui \
    $$QPCOL_SRC/forms/timeoffseteditor.ui

RESOURCES += \
    $$QPCOL_SRC/resources/icons.qrc

isEmpty(PREFIX) {
    PREFIX = /usr/local
}

DEFINES += QPCOL_PREFIX="\\\"$${PREFIX}"\\\"

CONFIG(release, debug|release)
CONFIG(shared, static|shared)
    QMAKE_STRIP             =   strip
    QMAKE_STRIPFLAGS_LIB    +=  --strip-unneeded

target.path = $$PREFIX/bin

LANGFILES   = lang/qpcol_pl.qm
lang.files  = $$LANGFILES
lang.path   = $$PREFIX/share/qpcol

icons.files = icons/qpcol.xpm
icons.path  = $$PREFIX/share/icons

menu.files  = menu/org.eu.merlin.qpcol.desktop
menu.path   = $$PREFIX/share/applications

protocol.files = menu/org.eu.merlin.qpcol.protocol
protocol.path = $$PREFIX/share/kde4/services

database.files = scripts/qpcol.sql
database.path  = $$PREFIX/share/qpcol

database_tools.files = scripts/qpcol_init_db scripts/qpcol_backup_db
database_tools.path  = $$PREFIX/bin

readme.files = README.md ISSUES.md VERSION
readme.path  = $$PREFIX/share/qpcol

INSTALLS    += target lang icons menu protocol database database_tools readme
