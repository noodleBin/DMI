#ifndef SIGNAL_H
#define SIGNAL_H

#include <QWidget>
#include <QPainter>

class MySignal : public QWidget
{
    Q_OBJECT
public:
    explicit MySignal(quint8 size,QWidget *parent = 0);
    void setValue(quint8 type,quint8 status,QRect& r,bool isreverse=0);
private:
    quint8  m_status;
    QRect m_rect;
    quint8 m_type;
    quint8 m_size;
    bool m_isreverse;

    void drawCBISignal(QPainter &painter);
    void drawOLCSignal(QPainter &painter);
signals:

protected:
    void paintEvent(QPaintEvent *e);
    QSize sizeHint() const;
public slots:
};

#endif // SIGNAL_H
