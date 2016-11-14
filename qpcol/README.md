# Qt Porn Collection Manager

Keyboard-oriented, build towards ease of use, this tool helps to gather,
catalogue, browse and manage your videos collection.

Meta-information about videos is stored in database, allowing user to organize
his films collection as flexible as possible.

## Requirements

Project uses embedded mplayer to play local media and Phonon for streaming.
Version 1.3 was ported succesfully to Qt-5.4. 

## Installation:

Download, build and install mwidgets as described in its README.md.

__Note__: For Archlinux users, PKGBUILD file isp   rovided , so
PKGBUILD files, so you can create arch pakage non your own.

To compile and install qpcol it should be enough to run *build.sh* script in
most cases. After build, execute *make install* as root user.

Detailed build and install instructions:

CXXINCLUDEFLAGS=$(find /usr/include/qt -maxdepth 1 -type d -exec echo -e "-I{}\0" \; | xargs  --null --)

$ PROJECT_ROOT=$(readlink -e $(dirname path to to_qpcol_root_dir}))
$ VERSION=$(< ${PROJECT_ROOT}/VERSION)

sed -i -r "s/^pkgver=(.+)$/pkgver=${VERSION}/" ${PROJECT_ROOT}/build/PKGBUILD
sed -i -r 's/md5sums=\([^\)]+\)//' ${PROJECT_ROOT}/build/PKGBUILD

qmake PREFIX=/usr BUILD_MODE=release QPCOL_RELEASE=1 "${PROJECT_ROOT}"
make -j$(nproc) && echo "Execute make install as root"

## First run

Before first run, start qpcol_init_db script from /usr/bin.
It initializes database. One of development plans is to take care of it automatically.

## Backups

If you want to backup current database, run qpcol_backup_db from /usr/bin.
It creates file qpcol_current_date.sql.gz in current working directory.

Examine qpcol_init_db to find out how to restore db from backup (I'll write
tool for it some day

## Bugs and issuess

Sure. List in prepare. Some of them is already described in ISSUES.md file.
