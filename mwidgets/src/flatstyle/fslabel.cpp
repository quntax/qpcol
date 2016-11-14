#include "fslabel.h"

fsLabel::fsLabel(QWidget *parent) :
    QLabel(parent)
{
}

fsLabel::fsLabel(QSizePolicy policy, QWidget *parent) :
    QLabel(parent)
{
    setSizePolicy(policy);
}

void fsLabel::alignText(const QString &label)
{
    alignText(label, width());
}

void fsLabel::alignText(const QString &label, int width)
{
    text = label;
    elidedText = fontMetrics().elidedText(text,
                                          Qt::ElideRight,
                                          width,
                                          Qt::TextWrapAnywhere);
    setText(elidedText);
    setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
}

void fsLabel::resizeEvent(QResizeEvent *event)
{
    alignText(text, event->size().width() - 20);
    QLabel::resizeEvent(event);
}

void fsLabel::mouseDoubleClickEvent(QMouseEvent * event)
{
    QObject::startTimer(2000);
    oldText = QLabel::text();

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text, QClipboard::Clipboard);

    alignText(tr("Skopiowano do schowka"));
    event->accept();
}

void fsLabel::timerEvent(QTimerEvent * event)
{
    QObject::killTimer(event->timerId());
    alignText(oldText);
    QLabel::timerEvent(event);
}


fsLabel::~fsLabel()
{

}
