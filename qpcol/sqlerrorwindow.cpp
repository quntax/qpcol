#include "sqlerrorwindow.h"

SqlErrorWindow::SqlErrorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlErrorWindow)
{
    ui->setupUi(this);
}

SqlErrorWindow::~SqlErrorWindow()
{
    delete ui;
}

void SqlErrorWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}
