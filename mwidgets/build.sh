#!/bin/bash

#
# Decide how to pass static configuration flag, here or directly to qmake
# Decide how to strip ELFs
#

PROJECT_ROOT=$(readlink -e $(dirname ${BASH_SOURCE[0]}))
COMPILATION_ROOT=$(pwd -P)
MWIDGETS_VERSION=$(cat ${PROJECT_ROOT}/VERSION)

# Not yet
#OBJ_LIBRARY=${COMPILATION_ROOT}/library/libmwidgets.so.${VERSION}
#OBJ_PLUGIN=${COMPILATION_ROOT}/designerplugin/libmwidgetsplugin.so

sed -i -r "s/^pkgver=(.+)$/pkgver=${MWIDGETS_VERSION}/" ${PROJECT_ROOT}/build/PKGBUILD
sed -i -r 's/md5sums=\([^\)]+\)//' ${PROJECT_ROOT}/build/PKGBUILD

if test -n $DESIGNER_PLUGINS_PKG_DIR; then
    DESIGNER_PLUGINS_PKG_DIR=$(qmake -query QT_INSTALL_PLUGINS)
fi

qmake \
    DESIGNER_PLUGIN_INSTALL_DIR=$DESIGNER_PLUGINS_PKG_DIR \
    BUILD_MODE=release \
    MWIDGETS_LIBRARY=1 MWIDGETS_PLUGIN=1 MWIDGETS_RELEASE=1 MEDIAWIDGET=1 \
    PREFIX=$(qmake -query QT_INSTALL_PREFIX) \
    ${PROJECT_ROOT}

make -j$(nproc)

exit 0

# Not yet
[[ -f "${OBJ_LIBRARY}" ]] && {
    echo "Moving library debug symbols to separate file"
    objcopy --only-keep-debug "${OBJ_LIBRARY}" "${OBJ_LIBRARY}.debug"
    strip "${OBJ_LIBRARY}"
    objcopy --add-gnu-debuglink "${OBJ_LIBRARY}.debug" "${OBJ_LIBRARY}"
}

[[ -f "${OBJ_PLUGIN}" ]] && {
    echo "Moving plugin debug symbols to separate file"
    objcopy --only-keep-debug "${OBJ_PLUGIN}" "${OBJ_PLUGIN}.debug"
    strip "${OBJ_PLUGIN}"
    objcopy --add-gnu-debuglink "${OBJ_PLUGIN}.debug" "${OBJ_PLUGIN}"
}
