#ifndef USERPLAYER_H
#define USERPLAYER_H


#include <QWidget>
#include "player.h"

class UserPlayer:public Player
{
public:
    UserPlayer(QWidget* parent);
    void beginPlayingHand();
    void beginCallingLord();

private:

};

#endif // USERPLAYER_H
