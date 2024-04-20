#include "stationitem.h"

StationItem::StationItem(qreal scale): QGraphicsItem()
{
    m_razm = scale;
}
//--------------------------
// Изменение размера изображения при масштабировании
void StationItem::setScale(qreal scale)
{
    if (m_razm != scale) {
        prepareGeometryChange();
        m_razm = scale;
    }
}
/*virtual*/
QRectF StationItem::boundingRect() const
{
    QPointF ptPosition(-nPenWidth-m_razm*0.5, -nPenWidth-m_razm*0.5);
//    QPointF ptPosition(-nPenWidth, -nPenWidth);
//    QPointF ptPosition(-10 - nPenWidth, -10 - nPenWidth);
//    QPointF ptPosition(-nPenWidth/2, -nPenWidth/2);
    QSizeF  size(m_razm + nPenWidth * 2, m_razm + nPenWidth * 2);
//    QSizeF  size(20 + nPenWidth * 2, 20 + nPenWidth * 2);
//    QSizeF  size(m_razm + nPenWidth, m_razm + nPenWidth);
    return QRectF(ptPosition, size);
}
/*virtual*/
void StationItem::paint(QPainter* ppainter,
    const QStyleOptionGraphicsItem*,
    QWidget* )
{
    ppainter->save();
    ppainter->setPen(QPen(Qt::blue, nPenWidth));
    ppainter->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    ppainter->drawEllipse(-m_razm*0.5, -m_razm*0.5, m_razm, m_razm);
//    ppainter->drawEllipse(0, 0, m_razm, m_razm);
//    ppainter->drawEllipse(-10, -10, 20, 20);
//    ppainter->drawEllipse(0, 0, 20, 20);

    ppainter->restore();
}
/*virtual*/
void StationItem::mousePressEvent(QGraphicsSceneMouseEvent* pe)
{

    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    QGraphicsItem::mousePressEvent(pe);
}
/*virtual*/
void StationItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* pe)
{
    QApplication::restoreOverrideCursor();
    QGraphicsItem::mouseReleaseEvent(pe);
}
