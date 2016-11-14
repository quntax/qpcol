/****************************************************************************
** $Id$
**
** Copyright (c) 2010, Daniel Jeznach <djeznach@gmail.com>
** All rights reserved.
**
** This file may be used under the terms of the BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in
**       the documentation
**       and/or other materials provided with the distribution.
**     * Neither the name of the author nor the names of its contributors
**       may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** HOLDER OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "htmlextract.h"

HtmlExtract::HtmlExtract(QObject *parent) :
    QObject(parent)
{
}

bool HtmlExtract::extract(Html::Element element, const QString &contents)
{
    QString elem = Html::Tags[element];
    QString patternElement = Html::PatternElement.arg(elem);
    QRegExp regexpElements(patternElement);

    regexpElements.setMinimal(true);
    clearStorage();
    int pos = 0;

    while ((pos = regexpElements.indexIn(contents, pos)) > -1) {
        QRegExp regexpAttributes(Html::PatternAttribute);
        int attrpos = 0;
        Html::Attribute attribute;

        while ((attrpos = regexpAttributes.indexIn(regexpElements.cap(0), attrpos)) > -1) {
            attribute.insert(regexpAttributes.cap(2), regexpAttributes.cap(3));
            attrpos += regexpAttributes.matchedLength();
        }

        listCaptures.append(regexpElements.cap(0));
        listValues.append(regexpElements.cap(2));
        listAttributes.append(attribute);

        countCaptures++;
        pos += regexpElements.matchedLength();
    }

    if (pos == 0) {
        return false;
    }

    return true;
}

void HtmlExtract::clearStorage()
{
    listCaptures.clear();
    listValues.clear();
    listAttributes.clear();

    countCaptures = 0;
}

QString HtmlExtract::capture(int index)
{
    return listCaptures.at(index);
}

QString HtmlExtract::value(int index)
{
    return listValues.at(index);
}

Html::Attribute HtmlExtract::attribute(int index)
{
    return listAttributes.at(index);
}

int HtmlExtract::count()
{
    return countCaptures;
}
