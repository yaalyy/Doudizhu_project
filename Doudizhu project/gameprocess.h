#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H


#include <QWidget>
#include <QTime>
#include <QMap>
#include "robot.h"
#include "userplayer.h"

class GameProcess : public QWidget
{
    Q_OBJECT
public:
    enum GameStatus
    {
        PickingCard,
        CallingLord,
        PlayingHand,
    };

    GameProcess(QWidget *parent = 0);

    void getOneCard(Player* player);                 //add a card to cards in hand
    void setCurrentPlayer(Player* player);
    Player* getLeftPlayer();
    Player* getRightPlayer();
    Player* getDownPlayer();

    Player* getCurrentPlayer();
    Player* getNextPlayer();
    Player* getPrevPlayer();

    Player* getHitPlayer();
    void setHitPlayer(Player* player);
    QList<card> getHitCards();

    QList<card> getAllCards();
    void beginPlayHand();
    void InitCards();       //initialise m_allCards
    void Restart();         //initialisation for restarting

    GameStatus m_gamestatus;
    QMap<Player*,int> BetList;      //record the points and players

    int betLeftOrder;
    int betDownOrder;
    int betRightOrder;

signals:
    /*signals to MainInterface*/
    void TellGameProcess(GameProcess::GameStatus);
    void TellPlayerStatus(Player* player,Player::PlayerStatus status);
    void TellPlayerPlayHand(Player* player,QList<card> cards);
    void TellPlayerCallLord(Player* player,int bet);

    /*signals to Player*/
    void TellHitPlayer(Player* player,QList<card> cards);

public slots:
    void PlayerCallLord(Player* player,int bet);
    void PlayerPlayHand(Player* player,QList<card> cards);

private:
    Robot* m_LeftPlayer;
    Robot* m_RightPlayer;
    UserPlayer* m_DownPlayer;

    Player* m_currentPlayer;        //current player to play cards

    QList<card> m_allCards;         //all cards
    Player* m_hitPlayer;            //currently strongest
    QList<card> m_hitCards;         //currently strongest cards

};

#endif // GAMEPROCESS_H
