#include <QImage>
#include "mappixel.h"

MapPixel::MapPixel(int i, int j){  //устанавливает элемент текстуры(картинку) на заданую позицию
    setPixmap(QPixmap(":/images/texture3_8x8.png"));
    setPos(i,j);
}
