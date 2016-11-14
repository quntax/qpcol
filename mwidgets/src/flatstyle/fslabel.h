#ifndef FSLABEL_H
#define FSLABEL_H

#include <QApplication>
#include <QLabel>
#include <QResizeEvent>
#include <QClipboard>
#include <QTimerEvent>

class fsLabel : public QLabel
{
    Q_OBJECT
public:
    explicit fsLabel(QWidget *parent = 0);
    ~fsLabel();
    fsLabel(QSizePolicy, QWidget *parent = 0);

    void alignText(const QString &);
    void alignText(const QString &, int);

protected:
    void resizeEvent(QResizeEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void timerEvent(QTimerEvent *);

protected:
    QString text;
    QString elidedText;
    QString oldText;
};

#endif // FSLABEL_H
