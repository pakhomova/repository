#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QGraphicsScene> //класс предоставляет поверхность для управления большим числом графических 2D элементов

const int WidthScreen = 800;
const int HeightScreen = 600;

class Battlefield{
    public:
        Battlefield();
        void addBattlefieldItemToScene(QGraphicsScene*);

    private:
        bool Matrixfield[HeightScreen][WidthScreen];
};

#endif

