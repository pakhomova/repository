#include "button.h"
//#include <QPixmap>

Button::Button(int xPos, int yPos, QString simple_Key, QString hover_Key){
    this->simpleKey = simple_Key;
    this->hoverKey = hover_Key;
    setPixmap(QPixmap(simpleKey));
    setPos(xPos, yPos);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(hoverKey));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPixmap(QPixmap(simpleKey));
}


