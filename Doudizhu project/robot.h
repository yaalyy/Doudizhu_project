//
//  robot.h
//  Doudizhu project
//
//  Created by ARCK on 26/01/2021.
//

#ifndef ROBOT_H
#define ROBOT_H


#include <QWidget>
#include <QThread>
#include "player.h"
#include "method.h"


class Robot:public Player
{
public:
    Robot(QWidget* parent);
    void beginPlayingHand();
    void beginCallingLord();
};

#endif // ROBOT_H
