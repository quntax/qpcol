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

#ifndef HTML_H
#define HTML_H

#define DDEBUG qDebug() <<\
        QString("[%1:%2]:").\
                arg(QString(__FILE__).split("/").last()).\
                arg(__LINE__) <<

#include <QtCore>

namespace Html {
    enum Element {
        A,
        ABBR,
        ACRONYM,
        ADDRESS,
        APPLET,
        AREA,
        B,
        BASE,
        BASEFONT,
        BDO,
        BIG,
        BLOCKQUOTE,
        BODY,
        BR,
        BUTTON,
        CAPTION,
        CENTER,
        CITE,
        CODE,
        COL,
        COLGROUP,
        DD,
        DEL,
        DFN,
        DIR,
        DIV,
        DL,
        DT,
        EM,
        FIELDSET,
        FONT,
        FORM,
        FRAME,
        FRAMESET,
        HEAD,
        HR,
        HTML,
        I,
        IFRAME,
        IMG,
        INPUT,
        INS,
        ISINDEX,
        KBD,
        LABEL,
        LEGEND,
        LI,
        LINK,
        MAP,
        MENU,
        META,
        NOFRAMES,
        NOSCRIPT,
        OBJECT,
        OL,
        OPTGROUP,
        OPTION,
        P,
        PARAM,
        PRE,
        Q,
        S,
        SAMP,
        SCRIPT,
        SELECT,
        SMALL,
        SPAN,
        STRIKE,
        STRONG,
        STYLE,
        SUB,
        SUP,
        TABLE,
        TBODY,
        TD,
        TEXTAREA,
        TFOOT,
        TH,
        THEAD,
        TITLE,
        TR,
        TT,
        U,
        UL
    };

    const QString Tags[84] = {
        "a",
        "abbr",
        "acronym",
        "address",
        "applet",
        "area",
        "b",
        "base",
        "basefont",
        "bdo",
        "big",
        "blockquote",
        "body",
        "br",
        "button",
        "caption",
        "center",
        "cite",
        "code",
        "col",
        "colgroup",
        "dd",
        "del",
        "dfn",
        "dir",
        "div",
        "dl",
        "dt",
        "em",
        "fieldset",
        "font",
        "form",
        "frame",
        "frameset",
        "head",
        "hr",
        "html",
        "i",
        "iframe",
        "img",
        "input",
        "ins",
        "isindex",
        "kbd",
        "label",
        "legend",
        "li",
        "link",
        "map",
        "menu",
        "meta",
        "noframes",
        "noscript",
        "object",
        "ol",
        "optgroup",
        "option",
        "p",
        "param",
        "pre",
        "q",
        "s",
        "samp",
        "script",
        "select",
        "small",
        "span",
        "strike",
        "strong",
        "style",
        "sub",
        "sup",
        "table",
        "tbody",
        "td",
        "textarea",
        "tfoot",
        "th",
        "thead",
        "title",
        "tr",
        "tt",
        "u",
        "ul"
    };

    const QString PatternElement = "<%1([^>]*)*>([\\w\\W]*)</%1>";
    const QString PatternAttribute = "(([a-zA-Z]+)[\\s]*=[\\s]*\"([^\"]*)\")";

    typedef QHash<QString, QString> Attribute;
}

#endif // HTML_H
