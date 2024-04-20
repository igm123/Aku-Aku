#include <QtWidgets>
#include "MyView.h"
//#include "readmap.h"
//#include "simpleitem.h"
#include "myscene.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale::C); // точка (а не запятая) в качестве дроби: 1.234

    MyScene* pScene = new MyScene(&app);

    QWidget        wgt;

    QPushButton* pcmdZoomIn      = new QPushButton("&Zoom +");
    QPushButton* pcmdZoomOut     = new QPushButton("Z&oom -");
    QCheckBox* pcmdMove          = new QCheckBox("Двигать станцию");

    MyView* pView = pScene->getView();

    QObject::connect(pcmdZoomIn, SIGNAL(clicked()), 
                     pView,      SLOT(slotZoomIn())
                    );
    QObject::connect(pcmdZoomIn, SIGNAL(clicked()),
                     pScene,      SLOT(slotScalePlus())
                    );

    QObject::connect(pcmdZoomOut, SIGNAL(clicked()), 
                     pView,       SLOT(slotZoomOut())
                    );
    QObject::connect(pcmdZoomOut, SIGNAL(clicked()),
                     pScene,       SLOT(slotScaleMinus())
                    );
    QObject::connect(pcmdMove, SIGNAL(toggled(bool)),
                     pScene,       SLOT(slotMoveStation(bool))
                    );

//    QObject::connect(pcmdRotateLeft, SIGNAL(clicked()),
//                     pView,          SLOT(slotRotateLeft())
//                    );
//    QObject::connect(pcmdRotateRight, SIGNAL(clicked()),
//                     pView,           SLOT(slotRotateRight())
//                    );

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pView);
    pvbxLayout->addWidget(pcmdZoomIn);
    pvbxLayout->addWidget(pcmdZoomOut);
    pvbxLayout->addWidget(pcmdMove);
//    pvbxLayout->addWidget(pcmdRotateLeft);
//    pvbxLayout->addWidget(pcmdRotateRight);
    wgt.setLayout(pvbxLayout);

    wgt.show();
  
    return app.exec();
} 
