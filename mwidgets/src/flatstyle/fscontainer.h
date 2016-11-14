#ifndef FSCONTAINER_H
#define FSCONTAINER_H

#include <QtGui>
#include <QtCore>
//#include <QWidget>
#include <QFrame>

class fsContainer : public QFrame
{
    Q_OBJECT
public:
    explicit fsContainer(QWidget *parent = 0);
    ~fsContainer();
    fsContainer(QSizePolicy, QWidget *parent = 0);

private:
    void init();
};

#endif // FSCONTAINER_H
