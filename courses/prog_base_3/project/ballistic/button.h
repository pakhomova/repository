#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Button: public QObject, public QGraphicsPixmapItem{
Q_OBJECT

    public:
        Button(int xPos, int yPos, QString simple_Key, QString hover_Key);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    signals:
        void clicked();

    private:
        QString simpleKey;
        QString hoverKey;
};

#endif // BUTTON_H

