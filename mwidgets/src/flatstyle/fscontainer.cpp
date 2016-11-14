#include "fscontainer.h"

fsContainer::fsContainer(QWidget *parent) :
    QFrame(parent)
{
    init();
}

fsContainer::fsContainer(QSizePolicy policy, QWidget *parent) :
    QFrame(parent)
{
    init();
    setSizePolicy(policy);
}

void fsContainer::init()
{
    QSizePolicy p(QSizePolicy::Minimum, QSizePolicy::Minimum);

    p.setHorizontalStretch(0);
    p.setVerticalStretch(0);

    setSizePolicy(p);
    setSizeIncrement(QSize(0, 0));
    setFrameShape(QFrame::StyledPanel);
//    setFrameShadow(QFrame::Plain);
    setFrameShadow(QFrame::Sunken);
    setLineWidth(1);
    setMidLineWidth(0);
}


fsContainer::~fsContainer()
{

}
