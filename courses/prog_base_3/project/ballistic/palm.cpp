#include <QImage>
#include <QGraphicsScene>
#include <QTimer>
#include "palm.h"

const double delta = 0.05;
const double g = 9.81;
const int acceleration = 4; //ускорение

void Palm::move(){ //падение пальмы в начале игры, пока не встретит землю
    if(collidingItems().size() == 0){
        setPos(x(), y() + speed_y*delta*acceleration + g*delta*delta*acceleration/2);
    }
    else{
        speed_y = 0;
    }
    speed_y += g*delta*acceleration;
}

QPointF Palm::getLocation(){
    return this->pos();
}

void Palm::setDefault()
{
    speed_y = 0;
    setPos(400-pixmap().width()/2, 0);
}

Palm::Palm(){
    speed_y = 0;
    setPixmap(QPixmap(":/images/palm2_300x300.png"));
    setPos(400-pixmap().width()/2, 0);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}
