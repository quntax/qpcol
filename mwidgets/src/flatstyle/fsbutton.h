#ifndef FSBUTTON_H
#define FSBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "fscontainer.h"

class fsButton : public QPushButton
{
    Q_OBJECT

public:
    explicit fsButton(fsContainer *parent = 0);
    ~fsButton();

    fsButton(const QString & themeIcon, fsContainer *parent = 0);
    fsButton(const QString & themeIcon, bool startDisabled = false, fsContainer *parent = 0);

    void setThemeIcon(const QString & themeIcon);

private:
    void initLayout(bool disabled = false);
};

#endif // FSBUTTON_H
