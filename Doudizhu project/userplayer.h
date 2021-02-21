//
//  userplayer.h
//  Doudizhu project
//
//  Created by ARCK on 26/01/2021.
//

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
