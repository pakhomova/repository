#include <QGraphicsScene>
#include <math.h>
#include <ctime>
#include "orange.h"
#include "lemon.h"
#include "eat.h"
#include <QTimer>
#include "enemygun.h"

#include <QDebug>

const double g = 9.81;

Enemygun::Enemygun(Gun* enemy, Palm* palma):player(enemy),palm(palma){
    alpha = 120;
    power = 80;
    speed_y = 0;
    speed_x = 0;

    HealthText = new QGraphicsTextItem();
    HealthText->setPlainText(QString("Health: ") + QString::number(health));
    HealthText->setDefaultTextColor(Qt::black);
    HealthText->setFont(QFont("times", 20));
    HealthText->setPos(675, 0);

    QTimer* timer_enemy = new QTimer();
    QObject::connect(timer_enemy, SIGNAL(timeout()), this, SLOT(Shoot()));
    static int time = 3000;
    if(player->getScores() == 0)
        time = 3000;
    time = time * 0.9;
    timer_enemy->start(time);
}

void Enemygun::Shoot(){
    QPointF player_location = player->getLocation();
    QPointF palm_location = palm->getLocation();
    if((player_location.x() < palm_location.x()) || ((pos().x() - palm_location.x()) < palm->pixmap().width())){
        int min;
        int height;
        if((palm_location.x() - player_location.x() + player->pixmap().width()) > (pos().x() -  palm_location.x() + palm->pixmap().width())){
            min = (pos().x() -  palm_location.x() + palm->pixmap().width());
            height = pos().y() - palm_location.y() + fabs(pos().y() - player_location.y()) + player->pixmap().height();
        }
        else{
            min = (palm_location.x() - player_location.x() - player->pixmap().width());
            height = player_location.y() - palm_location.y() + fabs(pos().y() - player_location.y()) + player->pixmap().height();
        }
        alpha = 180 - atan(height*1.0/min)*180/M_PI - 1;
        power = sqrt(fabs(2*g*(this->x() - player_location.x() - player->pixmap().width())/sin(2*alpha*M_PI/180)))/1.42;

        qDebug() << "min  = "<< min<<", height = "<<height<<", alpha = "<<alpha<<", power = "<<power;
        Shot* shot;
        srand(time(NULL));
        int temp = rand()%20+1;
        if(temp%10 == 0){
            shot  = new Eat((double)alpha, (double)power);
        }
        else if(temp%19 == 0){
            shot = new Lemon((double)alpha, (double)power);
        }
        else{
            shot = new Orange((double)alpha, (double)power);
        }
        shot->setPos(x()-20, y()-25);
        scene()->addItem(shot);
    }
}
