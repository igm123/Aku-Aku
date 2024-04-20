#include <QGraphicsScene>
#include <QGraphicsItem>

#include "myscene.h"
#include "simpleitem.h"


MyScene::MyScene(const QApplication *qa) : QObject()
{
    m_scale = 20; // размер станции в пикселах
    ReadMap rm(qa);// чтение файла карты
    double dx = rm.myParam.Pxp;
    double dy = rm.myParam.Pyp;

    m_pScene = new QGraphicsScene();
//    m_pScene = new QGraphicsScene(QRectF(-dx/2, -dy/2, dx, dy));
    m_pView = new MyView(m_pScene);
    m_pView->setRenderHint(QPainter::Antialiasing, true);
    // загрузка карты
    m_pPixmapItem = m_pScene->addPixmap(rm.myPixmap);
//    m_pPixmapItem->setFlags(QGraphicsItem::ItemIsMovable);

    m_pStationItem = new StationItem(m_scale);
    m_pScene->addItem(m_pStationItem);

    // дальность локации станции: L=100 м. В пикселах = L*Sp/Sm
    double lpix = 100.*rm.myParam.Sp/rm.myParam.Sm;

//    m_pStationItem->setPos(lpix, lpix);
    m_pStationItem->setPos(150, 150);
//    m_pStationItem->setPos(0, 0);
    m_pStationItem->setParentItem(m_pPixmapItem);
    //    SimpleItem*  pSimpleItem = new SimpleItem;
    //    m_pScene->addItem(pSimpleItem);
    //    pSimpleItem->setPos(0, 0);
    //    pSimpleItem->setFlags(QGraphicsItem::ItemIsMovable);


    CirculItem* pCirculItem = new CirculItem(lpix);
    pCirculItem->setParentItem(m_pStationItem);
    auto rect = m_pScene->sceneRect();
    qDebug()<<"sceneRect(x) = "<< rect.width()<< " sceneRect(y) = "<< rect.height()<<"\n";
}
//--------------------------
MyView* MyScene::getView(){
    return m_pView;
}
//--------------------------
void MyScene::slotScalePlus()
{
    m_scale /= 1.1;
    m_pStationItem->setScale(m_scale);
}
//--------------------------
void MyScene::slotScaleMinus()
{
    m_scale *= 1.1;
    m_pStationItem->setScale(m_scale);
}
//--------------------------
void MyScene::slotMoveStation(bool ok)
{
    if(ok){
        m_pStationItem->setFlags(QGraphicsItem::ItemIsMovable);
    }else{
        auto flags = m_pStationItem->flags();
        m_pStationItem->setFlags(flags & (~QGraphicsItem::ItemIsMovable));
    }
}

