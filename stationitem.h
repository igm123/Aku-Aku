#ifndef STATIONITEM_H
#define STATIONITEM_H

#include <QObject>
#include <QtWidgets>

class StationItem : public QGraphicsItem
{
//    Q_OBJECT
private:
    enum {nPenWidth = 1};
    qreal m_razm; // сторона квадрата (пиксел)
public:
    StationItem(qreal scale);
    void setScale(qreal scale);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* ppainter,
       const QStyleOptionGraphicsItem*, QWidget*);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pe);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe);
};

#endif // STATIONITEM_H
