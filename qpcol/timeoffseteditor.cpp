/**************************************************************************
 **
 ** This free software may be freelty distributed in accordance with The BSD
 ** License.
 **
 ** Copyright (c) 2016 merlin
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 ** Redistributions of source code must retain the above copyright notice,
 ** this list of conditions and the following disclaimer.
 ** Redistributions in binary form must reproduce the above copyright notice,
 ** this list of conditions and the following disclaimer in the documentation
 ** and/or other materials provided with the distribution.
 ** Neither the name of the author nor the names of its contributors may be used
 ** to endorse or promote products derived from this software without specific
 ** prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 ** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 ** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND **  FITNESS FOR A PARTICULAR
 ** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 ** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 ** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 ** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 ** OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 ** OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 ** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **
 **************************************************************************/
#include "timeoffseteditor.h"
#include "ui_timeoffseteditor.h"

TimeOffsetEditor::TimeOffsetEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeOffsetEditor)
{
    ui->setupUi(this);
}

TimeOffsetEditor::~TimeOffsetEditor()
{
    delete ui;
}

void TimeOffsetEditor::setStartTime(QString start)
{
    startTime = QTime::fromString(start, "hh:mm:ss");
    ui->startTime->setTime(startTime);
}

void TimeOffsetEditor::setEndpos(QString end)
{
    endpos = QTime::fromString(end, "hh:mm:ss");

    QTime endTime(0, 0, 0);
    int interval = QTime(0, 0, 0).secsTo(startTime) + QTime(0, 0, 0).secsTo(endpos);
    endTime = endTime.addSecs(interval);

    ui->endTime->setTime(endTime);
}

void TimeOffsetEditor::on_buttonBox_rejected()
{
    close();
}

void TimeOffsetEditor::on_buttonBox_accepted()
{
    startTime = ui->startTime->time();
    QTime endTime = ui->endTime->time();

    int interval = startTime.secsTo(endTime) - QTime(0, 0, 0).secsTo(startTime);
    endpos = startTime.addSecs(interval);

    if (endpos.toString("hh:mm:ss") == "00:00:00") {
        endpos.setHMS(23, 59, 59);
    }

    qDebug() << "Endpos set to" << endpos;
    emit timeOffsets(startTime.toString("hh:mm:ss"), endpos.toString("hh:mm:ss"));
}

void TimeOffsetEditor::on_buttonBox_clicked(QAbstractButton *button)
{
    if (ui->buttonBox->standardButton(button) == QDialogButtonBox::RestoreDefaults) {
        setStartTime("00:00:00");
        setEndpos("23:59:59");
    }
}
