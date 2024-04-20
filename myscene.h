#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QApplication>

#include "MyView.h"
#include "readmap.h"
#include "stationitem.h"

class MyScene : public QObject
{
    Q_OBJECT
public:
    MyScene(const QApplication* qa);
    MyView* getView();
private:
    MyView* m_pView;
    QGraphicsScene* m_pScene;
    QGraphicsPixmapItem* m_pPixmapItem;
    StationItem*  m_pStationItem;
    ReadMap* m_rm;
    qreal m_scale;
public slots:
    void slotScalePlus();
    void slotScaleMinus();
    void slotMoveStation(bool ok);
};

#endif // MYSCENE_H
