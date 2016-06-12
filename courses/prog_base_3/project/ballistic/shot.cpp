#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QImage>
#include <typeinfo>
#include <math.h>
#include <ctime>
#include "enemygun.h"
#include "mappixel.h"
#include "eat.h"
#include "orange.h"
#include "lemon.h"
#include "palm.h"

#include <QDebug>

const double delta = 0.01;
const double g = 9.81;
const int acceleration = 4;

void Shot::move(){

    QList<QGraphicsItem*> colliding_items = collidingItems();

    for(int i = 0; i < colliding_items.size(); i++){
        if((typeid(*(colliding_items[i])) == typeid(QGraphicsTextItem)) || (typeid(*(colliding_items[i])) == typeid(QGraphicsRectItem)) || (typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)));
        else if((typeid(*colliding_items[i])) == typeid(Palm)){
            scene()->removeItem(this);
            delete this;
            return;
        }
        else if((typeid(*colliding_items[i])) == typeid(Lemon) || (typeid(*colliding_items[i])) == typeid(Orange) || (typeid(*colliding_items[i])) == typeid(Eat) ){
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];

            scene()->removeItem(this);
            delete this;
            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(MapPixel)){
            QGraphicsEllipseItem* destroy_elips = new QGraphicsEllipseItem(x(), y(), 40, 40);
            scene()->addItem(destroy_elips);
            QList<QGraphicsItem*> colliding_Pixel = destroy_elips->collidingItems();

            for(int j = 0; j < colliding_Pixel.size(); j++){
                if(typeid(*(colliding_Pixel[j])) == typeid(MapPixel)){
                    scene()->removeItem(colliding_Pixel[j]);
                    delete colliding_Pixel[j];
                }
            }

            scene()->removeItem(destroy_elips);
            delete destroy_elips;

            scene()->removeItem(this);
            delete this;
            return;
        }
        else if((typeid(*(colliding_items[i])) == typeid(Gun)) || (typeid(*(colliding_items[i])) == typeid(Enemygun)) ){
            if(typeid(*this) == typeid(Orange))
                ((Gun*)colliding_items[i])->decreas();
            else if(typeid(*this) == typeid(Eat))
                ((Gun*)colliding_items[i])->increas();
            else if(typeid(*this) == typeid(Lemon))
                ((Gun*)colliding_items[i])->refresh();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    setPos(x() + speed_x*delta*acceleration, y() - speed_y*delta*acceleration + g*delta*delta*acceleration);

    if((pos().y() + pixmap().height() < -3000) || ((pos().y() + pixmap().height() > 600))){
        scene()->removeItem(this);
        delete this;
        return;
    }

    speed_y -=g*delta*acceleration;
}

Shot::Shot(double set_alpha, double set_speed){
    radius_power = 3;
    speed_x = set_speed*cos(set_alpha*M_PI/180);
    speed_y = set_speed*sin(set_alpha*M_PI/180);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(1000*delta);

}
