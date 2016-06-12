#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QList>
#include "enemygun.h"
#include "palm.h"
#include "battlefield.h"

class Game: public QGraphicsView{
Q_OBJECT
    public:
        Game();
        void displayMainMenu();
        void GameOver(int scores);
        Enemygun* enemy_player;
    public slots:
            void start();
            void restart();

    private:
        QList<QGraphicsItem*> GameOverListMenu;
        QGraphicsScene* scene;
        Gun* player;
        Battlefield* battlefield;
        Palm* palm;
};

#endif // GAME_H

