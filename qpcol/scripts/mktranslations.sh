#!/bin/bash

find "$(readlink -f ..)" -name '*.cpp' -or -name '*.h' -or -name '*.xml' -or -name '*.ui' > files.txt
touch qpcol_pl.po
xgettext -C -d qpcol_pl --from-code=utf-8 -a -ktr --qt -o qpcol_pl.po -f files.txt -j --package-name=qpcol --package-version="$(cat "$(dirname "${0}")"/../VERSION)" --msgid-bugs-address="<quntax1@gmail.com>"
rm -f files.txt
