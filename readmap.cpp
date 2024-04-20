#include <QDir>
#include <QDebug>
#include <QLocale>

#include <iostream>
#include <cstdio>

#include "readmap.h"

ReadMap::ReadMap(const QApplication *qa)
{

    QString dirApp = qa->applicationDirPath();
    // поиск bmp-файла в папке приложения
     QDir dir(dirApp);
     dir.setFilter(QDir::Files);
     QStringList filters;
     filters << "*.bmp";
     dir.setNameFilters(filters);
     bool res = true; // успех
     QFileInfoList list = dir.entryInfoList();
     std::cout << "     Bytes Filename" << std::endl;
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
         .arg(fileInfo.fileName()));
         std::cout << std::endl;
//         res = fillMyMap(fileInfo.fileName());
         res = readBmpName(fileInfo.fileName());
         if(res){
             myPixmap = QPixmap(fileInfo.fileName());
         }
         break;
     }

}
//----------------------------------------------
// Функция работает неустойчиво относительно десятичного разделителя
// числа: точка или запятая
// Заполнение структуры данных карты
// Вход:
//  fileName - имя файла изображения
// Возврат:
//  успех
bool ReadMap::fillMyMap(const QString& fileName){
    myMap.width = -1;// недействительные значения
    myMap.height = -1;
    //
    // Из названия файла считываем масшаб, положение и т.д.
    //
    char fname[50];
//    for(int i=0; i<50; i++){
//        fname[i] = 0;
//    }
    strncpy(fname, fileName.toLatin1().constData(), 50);
    if (10 != sscanf(fname, "%up_%um_%ux%upx=%c%u_%f_%c%u_%f",
       &myParam.Sp, &myParam.Sm, &myParam.Pxp, &myParam.Pyp, &myParam.Fis,
       &myParam.Figr, &myParam.Fimin, &myParam.Ls, &myParam.Lgr, &myParam.Lmin)) {
        qDebug() << "Sp = " << myParam.Sp <<"\n" <<
                    "Sm = " << myParam.Sm << "\n" <<
                    "Pxp = " << myParam.Pxp << "\n" <<
                    "Pyp = " << myParam.Pyp << "\n" <<
                    "Fis = " << myParam.Fis << "\n" <<
                    "Figr = " << myParam.Figr << "\n" <<
                    "Fimin = " << myParam.Fimin << "\n" <<
                    "Ls = " << myParam.Ls << "\n" <<
                    "Lgr = " << myParam.Lgr << "\n" <<
                    "Lmin = " << myParam.Lmin << "\n" ;
        qDebug() << "Не могу найти информацию из имени карты дна" << "\n";
        return false;
    }
     qDebug() << "Sp = " << myParam.Sp <<"\n" <<
                 "Sm = " << myParam.Sm << "\n" <<
                 "Pxp = " << myParam.Pxp << "\n" <<
                 "Pyp = " << myParam.Pyp << "\n" <<
                 "Fis = " << myParam.Fis << "\n" <<
                 "Figr = " << myParam.Figr << "\n" <<
                 "Fimin = " << myParam.Fimin << "\n" <<
                 "Ls = " << myParam.Ls << "\n" <<
                 "Lgr = " << myParam.Lgr << "\n" <<
                 "Lmin = " << myParam.Lmin << "\n" ;
     double cmPerPix = myParam.Sm * 100. / myParam.Sp;
     myMap.width = myParam.Pxp * cmPerPix;
     myMap.height = myParam.Pyp * cmPerPix;
    return true;
}
//------------------------------------
bool ReadMap::readBmpName(const QString &fileName){
//    QLocale::setNumberOptions(QLocale::DefaultNumberOptions);
//    QLocale::setDefault(QLocale::C);
    bool res = false;
    char fname[50];
    char tmp[10];
    strncpy(fname, fileName.toLatin1().constData(), 50);
    int i;
    for(i=0; i<50; i++){
        char ch = fname[i] ;
        if(ch == 'p'){
           res = true;
           break;
        }
    }
    if(!res) return false;
    res = false;
    int num = i;
    strncpy(tmp, fname, num);
    tmp[num] = 0;
    myParam.Sp = std::atoi(tmp);
    qDebug() << "Sp = " << myParam.Sp <<"\n";
    for(i=num+2; i<50; i++){
        char ch = fname[i] ;
        if(ch == 'm'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num+2, i-(num+2));
    tmp[i-(num+2)] = 0;
    myParam.Sm = std::atoi(tmp);
    qDebug() << "Sm = " << myParam.Sm <<"\n";

    res = false;
    num = i+2;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == 'x'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    myParam.Pxp = std::atoi(tmp);
    qDebug() << "Pxp = " << myParam.Pxp <<"\n";

    res = false;
    num = i+1;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == 'p'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    myParam.Pyp = std::atoi(tmp);
    qDebug() << "Pyp = " << myParam.Pyp <<"\n";

    num = i+3;
    myParam.Fis = fname[num];
    qDebug() << "Fis = " << myParam.Fis <<"\n";

    res = false;
    num++;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == '_'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    myParam.Figr = std::atoi(tmp);
    qDebug() << "Figr = " << myParam.Figr <<"\n";

    res = false;
    num = i+1;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == '_'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    bool ok;
    myParam.Fimin = QString(tmp).toFloat(&ok);

    qDebug() << "Fimin = " << myParam.Fimin <<"\n";

    num = i+1;
    myParam.Ls = fname[num];
    qDebug() << "Ls = " << myParam.Ls <<"\n";

    res = false;
    num++;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == '_'){
            res = true;
           break;
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    myParam.Lgr = std::atoi(tmp);
    qDebug() << "Lgr = " << myParam.Lgr <<"\n";

    res = false;
    num = i+1;
    int i2 = 0;
    for(i=num; i<50; i++){
        char ch = fname[i] ;
        if(ch == '.'){
            if(i2 == 0){// пропуск десятичной точки
                i2++;
            }else{
                res = true;
                break;
            }
        }
    }
    if(!res) return false;
    strncpy(tmp, fname+num, i-num);
    tmp[i-num] = 0;
    myParam.Lmin = QString(tmp).toFloat(&ok);

    qDebug() << "Lmin = " << myParam.Lmin <<"\n";
    qDebug() << "Sp = " << myParam.Sp <<"\n" <<
                "Sm = " << myParam.Sm << "\n" <<
                "Pxp = " << myParam.Pxp << "\n" <<
                "Pyp = " << myParam.Pyp << "\n" <<
                "Fis = " << myParam.Fis << "\n" <<
                "Figr = " << myParam.Figr << "\n" <<
                "Fimin = " << myParam.Fimin << "\n" <<
                "Ls = " << myParam.Ls << "\n" <<
                "Lgr = " << myParam.Lgr << "\n" <<
                "Lmin = " << myParam.Lmin << "\n" ;
    double cmPerPix = myParam.Sm * 100. / myParam.Sp;
    myMap.width = myParam.Pxp * cmPerPix;
    myMap.height = myParam.Pyp * cmPerPix;

    return true;;
}
