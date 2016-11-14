DEFINES     += MWIDGETS_PLUGIN

include($${PWD}/../mwidgets.pri)

QT          += core gui widgets uiplugin designer phonon4qt5
TARGET      = $$qtLibraryTarget(mwidgetsplugin)
TEMPLATE    = lib
CONFIG      += plugin
LIBS        += -L$${PWD}/../library -lmwidgets

target.path         = $${DESIGNER_PLUGIN_INSTALL_DIR}/designer

INSTALLS            += target
