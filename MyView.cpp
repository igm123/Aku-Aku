#include "MyView.h"

MyView::MyView(QGraphicsScene* pScene, QWidget* pwgt)
    : QGraphicsView(pScene, pwgt)
{
}
//========================
// Увеличение масштаба
void MyView::slotZoomIn()
{
    scale(1.1, 1.1);
}
//========================
// Уменьшение масштаба
void MyView::slotZoomOut()
{
    scale(1 / 1.1, 1 / 1.1);
}
