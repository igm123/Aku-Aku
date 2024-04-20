#ifndef SIMPLEITEM_H
#define SIMPLEITEM_H

#include <QtWidgets>

//----------------------------------
// окружность вокруг станции
class CirculItem : public QGraphicsItem {
private:
    enum {nPenWidth = 1};
    double m_radius;// радиус окружности (пиксел)
public:
    CirculItem(double radius){
        m_radius = radius;
    }
    virtual QRectF boundingRect() const
    {
        QPointF ptPosition(-m_radius - nPenWidth, -m_radius - nPenWidth);
        QSizeF  size(2*m_radius + nPenWidth * 2, 2*m_radius + nPenWidth * 2);
        return QRectF(ptPosition, size);
    }

    virtual void paint(QPainter* ppainter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*
                      )
    {
        ppainter->save();
        ppainter->setPen(QPen(Qt::black, nPenWidth));
        ppainter->drawEllipse(-m_radius, -m_radius, 2*m_radius, 2*m_radius);
        ppainter->restore();
    }
};
//-------------------
class SimpleItem : public QGraphicsItem {
private:
    enum {nPenWidth = 3};

public:
    virtual QRectF boundingRect() const
    {
        QPointF ptPosition(-10 - nPenWidth, -10 - nPenWidth);
        QSizeF  size(20 + nPenWidth * 2, 20 + nPenWidth * 2);
        return QRectF(ptPosition, size);
    }

    virtual void paint(QPainter* ppainter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*
                      )
    {
        ppainter->save();
        ppainter->setPen(QPen(Qt::blue, nPenWidth));
        ppainter->drawEllipse(-10, -10, 20, 20);
        ppainter->restore();
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pe)
    {

        QApplication::setOverrideCursor(Qt::PointingHandCursor);
        QGraphicsItem::mousePressEvent(pe);
    }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* pe)
    {
        QApplication::restoreOverrideCursor();
        QGraphicsItem::mouseReleaseEvent(pe);
    }
};


#endif // SIMPLEITEM_H
