#ifndef FSSEPARATOR_H
#define FSSEPARATOR_H

#include <QFrame>

class fsSeparator : public QFrame
{
    Q_OBJECT
public:
    explicit fsSeparator(QWidget *parent = 0);
    ~fsSeparator();
};

#endif // FSSEPARATOR_H
