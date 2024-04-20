#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

// ==========================
// Отрисовка графической сцены
class MyView: public QGraphicsView {
    Q_OBJECT
public:
    MyView(QGraphicsScene* pScene, QWidget* pwgt = 0);

public slots:
    void slotZoomIn();
    void slotZoomOut();

//signals:
//    void signalScale();

//    void slotRotateLeft()
//    {
//        rotate(-5);
//    }

//    void slotRotateRight()
//    {
//        rotate(5);
//    }

};

#endif // MYVIEW_H
