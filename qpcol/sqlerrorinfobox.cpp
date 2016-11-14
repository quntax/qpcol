#include "sqlerrorinfobox.h"
#include "ui_sqlerrorinfobox.h"

SqlErrorInfoBox::SqlErrorInfoBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlErrorInfoBox)
{
    ui->setupUi(this);
}

SqlErrorInfoBox::~SqlErrorInfoBox()
{
    delete ui;
}

void SqlErrorInfoBox::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}
