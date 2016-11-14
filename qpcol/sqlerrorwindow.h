#ifndef SQLERRORWINDOW_H
#define SQLERRORWINDOW_H

#include <QtGui/QDialog>

namespace Ui {
    class SqlErrorWindow;
}

class SqlErrorWindow : public QDialog
{
        Q_OBJECT

    public:
        explicit SqlErrorWindow(QWidget *parent = 0);
        ~SqlErrorWindow();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::SqlErrorWindow *ui;
};

#endif // SQLERRORWINDOW_H
