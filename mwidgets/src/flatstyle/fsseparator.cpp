#include "fsseparator.h"

fsSeparator::fsSeparator(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::VLine);
    setFrameShadow(QFrame::Sunken);
    setContentsMargins(6, 3, 6, 3);
}


fsSeparator::~fsSeparator()
{

}
