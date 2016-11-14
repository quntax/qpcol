#!/bin/bash

CXXINCLUDEFLAGS=$(find /usr/include/qt -maxdepth 1 -type d -exec echo -e "-I{}\0" \; | xargs  --null --)
PROJECT_ROOT=$(readlink -e $(dirname ${BASH_SOURCE[0]}))
VERSION=$(< ${PROJECT_ROOT}/VERSION)

sed -i -r "s/^pkgver=(.+)$/pkgver=${VERSION}/" ${PROJECT_ROOT}/build/PKGBUILD
sed -i -r 's/md5sums=\([^\)]+\)//' ${PROJECT_ROOT}/build/PKGBUILD

qmake PREFIX=/usr BUILD_MODE=release QPCOL_RELEASE=1 "${PROJECT_ROOT}"
make -j$(nproc) && echo "Execute make install as root"
