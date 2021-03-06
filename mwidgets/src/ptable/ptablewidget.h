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

#ifndef PTABLEWIDGET_H
#define PTABLEWIDGET_H

#include "ptable.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QResizeEvent>
#include <QtUiPlugin/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT PTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit PTableWidget(QWidget *parent = 0);

    virtual void setColumnsWidth(const ColumnsWidth &);
    virtual void setColumnsWidth();

    virtual inline ColumnsWidth columnsWidth() { return widths; }

protected slots:
    void resizeEvent(QResizeEvent *);
    virtual void columnResized(int column, int oldWidth, int newWidth);

protected:
    ColumnsWidth widths;
};

#endif // PTABLEWIDGET_H
