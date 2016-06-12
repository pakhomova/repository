#include "button.h"
//#include <QPixmap>

Button::Button(int xPos, int yPos, QString simple_Key, QString hover_Key){ //simple - обычный вид кнопки, hover - вид кнопки, когда на нее наведен курсор
    this->simpleKey = simple_Key;
    this->hoverKey = hover_Key;
    setPixmap(QPixmap(simpleKey));
    setPos(xPos, yPos);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){ //когда на кнопку наводится курсор
    setPixmap(QPixmap(hoverKey));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){ //когда курсор убирается с кнопки
    setPixmap(QPixmap(simpleKey));
}


