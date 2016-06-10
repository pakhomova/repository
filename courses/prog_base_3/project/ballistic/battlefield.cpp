#include <ctime>
#include "battlefield.h"
#include "mappixel.h"

Battlefield::Battlefield(){
    srand(time(NULL));

    int height = HeightScreen/7 + HeightScreen/2 + rand() % (HeightScreen/4);

    for(int i = 0; i < WidthScreen; i+=8){
            for(int j = height; j < HeightScreen; j+=8){
                Matrixfield[j][i] = 1;
            }
            if(!((i < (WidthScreen/2 - 20)) && (i > (WidthScreen/2 - 75)))){
                height += -10 + rand()%21;
                if((height < HeightScreen/2) && (height > (7*HeightScreen/8)))
                height = HeightScreen/8 + HeightScreen/2 + rand() % (HeightScreen/4);

            }
    }
}

void Battlefield::addBattlefieldItemToScene(QGraphicsScene* scene){
    for(int i = 0; i < HeightScreen; i++){
            for(int j = 0; j < WidthScreen; j++){
                if(Matrixfield[i][j] == 1){
                    scene->addItem(new MapPixel(j,i));
                 }
            }
    }
}
