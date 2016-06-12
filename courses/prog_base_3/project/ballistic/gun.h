#ifndef GUN_H
#define GUN_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QObject>

class Gun: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

    public:
        Gun();
        QPointF getLocation();
        void decreas();
        void increas();
        void increasScores();
        void setDefault();
        int getScores();
        void setScores(int score);
        void refresh();
        QGraphicsTextItem* getScoresText();
        QGraphicsTextItem* HealthText;
    protected:
        int health;
        int alpha;
        int power;
        double speed_x;
        double speed_y;
    public slots:
        void move();
    private:
        QGraphicsTextItem* ScoresText;
        int scores;
        void keyPressEvent(QKeyEvent *event);
};

#endif
