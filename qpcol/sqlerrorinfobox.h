#ifndef SQLERRORINFOBOX_H
#define SQLERRORINFOBOX_H

#include <QtGui/QWidget>

namespace Ui {
    class SqlErrorInfoBox;
}

class SqlErrorInfoBox : public QWidget
{
        Q_OBJECT

    public:
        explicit SqlErrorInfoBox(QWidget *parent = 0);
        ~SqlErrorInfoBox();

    protected:
        void changeEvent(QEvent *e);

    private:
        Ui::SqlErrorInfoBox *ui;
};

#endif // SQLERRORINFOBOX_H
