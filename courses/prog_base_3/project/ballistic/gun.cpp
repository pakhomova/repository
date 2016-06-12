#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QFont>
#include <time.h>
#include <typeinfo>
#include "game.h"
#include "enemygun.h"
#include "eat.h"
#include "lemon.h"
#include "orange.h"

#include <QDebug>

const double delta = 0.05;
const double g = 9.81;
const int acceleration = 4;

extern Game* game;

Gun::Gun(){
    scores = 0;
    health = 3;
    alpha = 60;
    power = 80;
    speed_y = 0;
    speed_x = 0;
    setPos(40, 150);

    HealthText = new QGraphicsTextItem();
    HealthText->setPlainText(QString("Health: ") + QString::number(health));
    HealthText->setDefaultTextColor(Qt::yellow);
    HealthText->setFont(QFont("times", 20));

    ScoresText = new QGraphicsTextItem();
    ScoresText->setPlainText(QString("Scores: ") + QString::number(scores));
    ScoresText->setDefaultTextColor(Qt::yellow);
    ScoresText->setFont(QFont("times", 20));
    ScoresText->setPos(0, 25);

    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

QPointF Gun::getLocation(){
    return this->pos();
}

void Gun::decreas()
{
    --health;
    if(health < 0)
        HealthText->setPlainText(QString("Health: ") + QString::number(0));
    else
        HealthText->setPlainText(QString("Health: ") + QString::number(health));
    if(health == 0){
        HealthText->setPlainText(QString("Health: ") + QString::number(health));
        if(typeid(*this) == typeid(Enemygun)){
            Enemygun* newEnemy = new Enemygun(((Enemygun*)this)->player, ((Enemygun*)this)->palm);
            newEnemy->setPixmap(QPixmap(":/images/blackskingorilla_35x37.png"));
            newEnemy->setPos(800 - 40 - pixmap().width(), 150);
            (((Enemygun*)this)->player)->increasScores();
            scene()->addItem(newEnemy);
            scene()->addItem(newEnemy->HealthText);
            game->enemy_player = newEnemy;
            scene()->removeItem(HealthText);
            delete HealthText;
            scene()->removeItem(this);
            delete this;
            return;
        }
        else{
            if(health == 0)
                game->GameOver(scores);
            else
                health = 0;
        }
    }
    qDebug()<<health;
}

void Gun::increas()
{
    ++health;
    HealthText->setPlainText(QString("Health: ") + QString::number(health));
    qDebug()<<health;
}

void Gun::increasScores()
{
    scores++;
    ScoresText->setPlainText(QString("Scores: ") + QString::number(scores));
}

void Gun::setDefault()
{
    scores = 0;
    health = 3;
    alpha = 60;
    power = 80;
    speed_y = 0;
    speed_x = 0;
    setPos(40, 150);

    HealthText->setPlainText(QString("Health: ") + QString::number(health));
    ScoresText->setPlainText(QString("Scores: ") + QString::number(scores));
}

int Gun::getScores()
{
    return scores;
}

void Gun::setScores(int set_score)
{
    scores = set_score;
}

void Gun::refresh()
{
    health = 5;
    HealthText->setPlainText(QString("Health: ") + QString::number(health));
    qDebug()<<health;
}

QGraphicsTextItem *Gun::getScoresText()
{
    return ScoresText;
}

void Gun::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left){
        if(pos().x() > 0){
            QGraphicsRectItem* LeftRectAccess = new QGraphicsRectItem();
            LeftRectAccess->setRect(pos().x() - 15, pos().y() + pixmap().height() - 32, 10, 10);
            scene()->addItem(LeftRectAccess);
            QList<QGraphicsItem*> RectCollidingList = LeftRectAccess->collidingItems();
            if(RectCollidingList.size() > 0){
                scene()->removeItem(LeftRectAccess);
                delete LeftRectAccess;
                return;
            }
            scene()->removeItem(LeftRectAccess);
            delete LeftRectAccess;

            QGraphicsRectItem* LeftRect = new QGraphicsRectItem();
            LeftRect->setRect(pos().x() - 22, pos().y() + pixmap().height() - 11, 10, 10);
            scene()->addItem(LeftRect);
            RectCollidingList = LeftRect->collidingItems();
            for(int i = 0; i < RectCollidingList.size(); i++){
                if(typeid(*(RectCollidingList[i])) == typeid(Palm)){
                    scene()->removeItem(LeftRect);
                    delete LeftRect;
                    return;
                }
                else if(typeid(*(RectCollidingList[i])) == typeid(*this))
                    RectCollidingList.removeOne(RectCollidingList[i]);
            }
            if(RectCollidingList.size() > 1){
               setPos(x() - 5, y() - 5);
            }
            else
                setPos(x() - 5, y());

            scene()->removeItem(LeftRect);
            delete LeftRect;
        }
    }

    if(event->key() == Qt::Key_Right){
        if(pos().x() < (800 - pixmap().width())){
            QGraphicsRectItem* RightRectAccess = new QGraphicsRectItem();
            RightRectAccess->setRect(pos().x() + pixmap().width(), pos().y() + pixmap().height() - 32, 10, 10);
            scene()->addItem(RightRectAccess);
            QList<QGraphicsItem*> RectCollidingList = RightRectAccess->collidingItems();
            if(RectCollidingList.size() > 0){
                scene()->removeItem(RightRectAccess);
                delete RightRectAccess;
                return;
            }
            scene()->removeItem(RightRectAccess);
            delete RightRectAccess;


            QGraphicsRectItem* RightRect = new QGraphicsRectItem();
            RightRect->setRect(pos().x() + pixmap().width(), pos().y() + pixmap().height(), 10, 10);
            scene()->addItem(RightRect);
            RectCollidingList = RightRect->collidingItems();
            for(int i = 0; i < RectCollidingList.size(); i++){
                if(typeid(*(RectCollidingList[i])) == typeid(Palm)){
                    scene()->removeItem(RightRect);
                    delete RightRect;
                    return;
                }
                else if(typeid(*(RectCollidingList[i])) == typeid(*this))
                    RectCollidingList.removeOne(RectCollidingList[i]);
            }
            if(RectCollidingList.size() > 1){
               setPos(x() + 5, y() - 5);
            }
            else
                setPos(x() + 5, y());

            scene()->removeItem(RightRect);
            delete RightRect;
        }
    }

    if(event->key() == Qt::Key_Up){
        alpha++;
    }

    if(event->key() == Qt::Key_Down){
        alpha--;
    }
    if(event->key() == Qt::Key_Plus){
        power++;
    }
    if(event->key() == Qt::Key_Minus){
        power--;
    }
    else if(event->key() == Qt::Key_Space){
        Shot* shot;
        srand(time(NULL));
        int temp = rand()%20 + 1;
        if(temp%10 == 0){
            shot  = new Eat((double)alpha, (double)power);
        }
        else if(temp%19 == 0){
            shot = new Lemon((double)alpha, (double)power);
        }
        else{
            shot = new Orange((double)alpha, (double)power);
        }
        shot->setPos(x()+25, y()-25);
        scene()->addItem(shot);
    }

}

void Gun::move(){
    if(collidingItems().size() == 0){
        if((pos().y() + pixmap().height()) > 600)
            speed_y = 0;
        setPos(x() + delta*speed_x*acceleration, y() + speed_y*delta*acceleration + g*delta*delta*acceleration/2);
    }
    else{
        speed_x = 0;
        speed_y = 0;
    }
    speed_y += g*delta*acceleration;
}
