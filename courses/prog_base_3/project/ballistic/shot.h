#ifndef SHOT_H
#define SHOT_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Shot: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

   public:
        Shot(double set_alpha, double set_speed);
   public slots:
        void move();
   private:
        int radius_power;
        double speed_x;
        double speed_y;
};

#endif

