#include "fsbutton.h"

fsButton::fsButton(fsContainer *parent) :
    QPushButton(parent)
{
    initLayout();
}

fsButton::~fsButton()
{

}

fsButton::fsButton(const QString & themeIcon, fsContainer *parent) :
    QPushButton(parent)
{
    setIcon(QIcon::fromTheme(themeIcon));
    initLayout();
}

fsButton::fsButton(const QString & themeIcon, bool startDisabled, fsContainer *parent) :
    QPushButton(parent)
{
    setIcon(QIcon::fromTheme(themeIcon));
    initLayout(startDisabled);
}

void fsButton::initLayout(bool disabled)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    sizePolicy().setHorizontalStretch(0);
    sizePolicy().setVerticalStretch(0);

    setMaximumSize(QSize(35, 28));
    setIconSize(QSize(22, 22));
//    setFlat(true);
    setDisabled(disabled);
}

void fsButton::setThemeIcon(const QString &themeIcon)
{
    setIcon(QIcon::fromTheme(themeIcon));
}
