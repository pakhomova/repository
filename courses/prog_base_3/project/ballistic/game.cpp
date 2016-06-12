#include <QObject>
#include <QBrush>
#include <QGraphicsTextItem>
#include <QImage>
#include <typeinfo>
#include "lemon.h"
#include "orange.h"
#include "eat.h"
#include "game.h"
#include "button.h"

#include <QDebug>

extern Game* game;

Game::Game(){

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WidthScreen, HeightScreen);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, WidthScreen, HeightScreen);
    setScene(scene);
}


void Game::start(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/background3.png")));

    battlefield = new Battlefield();
    battlefield->addBattlefieldItemToScene(scene);

    player = new Gun();
    player->setPixmap(QPixmap(":/images/gorillaskinwhite_35x44.png"));
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    player->setTransformOriginPoint(player->pixmap().width(), player->pixmap().height());
    player->setRotation(-20);
    scene->addItem(player->getScoresText());
    scene->addItem(player->HealthText);

    palm = new Palm();
    scene->addItem(palm);

    enemy_player = new Enemygun(player, palm);
    enemy_player->setPixmap(QPixmap(":/images/blackskingorilla_35x37.png"));
    enemy_player->setPos(800 - 40 - enemy_player->pixmap().width(), 150);
    scene->addItem(enemy_player);
    scene->addItem(enemy_player->HealthText);
}

void Game::restart(){

    for(int i = 0; i < GameOverListMenu.size(); i++){
        scene->removeItem(GameOverListMenu[i]);
        delete GameOverListMenu[i];
    }
    while(GameOverListMenu.size() > 0)
        GameOverListMenu.removeFirst();

    player->setDefault();
    player->setFocus();
    //battlefield = new Battlefield();
    //battlefield->addBattlefieldItemToScene(scene);
    palm->setDefault();

    enemy_player = new Enemygun(player, palm);
    enemy_player->setPixmap(QPixmap(":/images/blackskingorilla_35x37.png"));
    enemy_player->setPos(800 - 40 - enemy_player->pixmap().width(), 150);
    scene->addItem(enemy_player);
    scene->addItem(enemy_player->HealthText);
}

void Game::displayMainMenu(){
    scene->clear();
    setBackgroundBrush(QBrush(QImage(":/images/MenuBackground.png")));

    Button* newGameButton = new Button(592, 127, QString(":/images/NewGame.png"), QString(":/images/NewGameBlink.png"));
    scene->addItem(newGameButton);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(start()));

    Button* QuitButton = new Button(592, 237, QString(":/images/Quit.png"), QString(":/images/QuitBlink.png"));
    scene->addItem(QuitButton);
    connect(QuitButton, SIGNAL(clicked()), this, SLOT(close()));

    Button* ScoresButton = new Button(592, 347, QString(":/images/Scores.png"), QString(":/images/ScoresBlink.png"));
    scene->addItem(ScoresButton);
    //connect(ScoresButton, SIGNAL(clicked()), this, SLOT(showScores()));

}

void Game::GameOver(int scores){
    scene->removeItem(enemy_player);
    scene->removeItem(enemy_player->HealthText);
    delete enemy_player->HealthText;
    delete enemy_player;

    QGraphicsRectItem* GreyPanel = new QGraphicsRectItem(0, 0, 800, 600);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);

    GreyPanel->setBrush(brush);
    GreyPanel->setOpacity(0.5);
    scene->addItem(GreyPanel);
    GameOverListMenu.push_back(GreyPanel);

    QGraphicsPixmapItem* GameOverMenu = new QGraphicsPixmapItem(QPixmap(":/images/GameOverMenu.png"));
    GameOverMenu->setPos(800 - GameOverMenu->pixmap().width(), 0);
    scene->addItem(GameOverMenu);
    GameOverListMenu.push_back(GameOverMenu);

    Button* newGameButton = new Button(592, 127, QString(":/images/NewGame.png"), QString(":/images/NewGameBlink.png"));
    scene->addItem(newGameButton);
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(restart()));
    GameOverListMenu.push_back(newGameButton);

    Button* QuitButton = new Button(592, 237, QString(":/images/Quit.png"), QString(":/images/QuitBlink.png"));
    scene->addItem(QuitButton);
    connect(QuitButton, SIGNAL(clicked()), this, SLOT(close()));
    GameOverListMenu.push_back(QuitButton);

    Button* ScoresButton = new Button(592, 347, QString(":/images/Scores.png"), QString(":/images/ScoresBlink.png"));
    scene->addItem(ScoresButton);
    //connect(ScoresButton, SIGNAL(clicked()), this, SLOT(showScores()));
    GameOverListMenu.push_back(ScoresButton);

    QGraphicsTextItem* resultText = new QGraphicsTextItem();
    resultText->setPlainText(QString("You lose!\n") + QString("Your scores: ") + QString::number(scores));
    resultText->setDefaultTextColor(Qt::white);
    resultText->setFont(QFont("times", 30));
    resultText->setPos(220 - resultText->textWidth(), 200);
    scene->addItem(resultText);
    GameOverListMenu.push_back(resultText);
}

