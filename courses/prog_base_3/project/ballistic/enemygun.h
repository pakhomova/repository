#ifndef ENEMYGUN_H
#define ENEMYGUN_H

#include "gun.h"
#include "palm.h"

class Enemygun: public Gun{
Q_OBJECT
    public:
        Enemygun(Gun* enemy, Palm*);
    public slots:
        void Shoot();
    public:
        Gun* player;
        Palm* palm;
};

#endif // ENEMYGUN_H

