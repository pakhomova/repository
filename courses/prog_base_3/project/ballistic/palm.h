#ifndef PALM_H
#define PALM_H

#include<QObject>
#include <QGraphicsPixmapItem>

class Palm: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

    public:
        Palm();
        QPointF getLocation();
        void setDefault();
    public slots:
        void move();
    private:
        double speed_y;

};

#endif // PALM_H

