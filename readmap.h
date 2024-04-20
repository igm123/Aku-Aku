#ifndef READMAP_H
#define READMAP_H

#include <QApplication>
#include <QPixmap>

// Размеры карты в см
struct mapSizes{
    double width; // ширина (см)
    double height;// высота (см)
} ;
// параметры карты из названия файла
struct mapParam{
    unsigned int
       Sp,  // Шкала карты в пикселях
       Sm,  // Шкала карты в метрах
       Pxp, // Размер в пикселях по Х
       Pyp; // Размер в пикселях по Y
    char
       Fis, // Знак широты
       Ls;  // Знак долготы
    unsigned int
       Figr,// Широта в градусах
       Lgr; // долгота в градусах
    float
       Fimin,// Широта в минутах
       Lmin; // долгота в минутах
};

//------------------------------
// Чтение файла изображения карты
class ReadMap
{
public:
    ReadMap(const QApplication* qa);
    // переменные - - - - - - -
    mapSizes myMap;     // характеристики карты
    mapParam myParam;
    QPixmap myPixmap; // карта
private:
    bool fillMyMap(const QString& fileName);
    bool readBmpName(const QString& fileName);

};

#endif // READMAP_H
