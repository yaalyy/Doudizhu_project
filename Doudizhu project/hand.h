#ifndef HAND_H
#define HAND_H


#include"card.h"
#include<QList>

//this class is used to judge what a group of cards is, and judge if a group can beat the other group
class Hand
{
public:
    Hand();
    Hand(QList<card> cards); //declare a class from cards
    Hand(HandType type, CardPoint base, int extra);//declare a class from a type, a value and the number of cards
    bool Defeat(Hand &hand);                    //to judge if a group can beat the other group
    void DefineHandType();                      //judge the group of cards
    void InitByCardsList(QList<card> cardList); //use 4 containers to store the number of each card
    HandType getHandType();      //get the type of cards
    int getBasePoint();          //get values of cards
    int getExtra();              //get the number of cards
private:
    HandType m_handtype;         //the type of group of cards
    int m_basepoint;             //the value of cards
    int m_extra;                 //the number of cards
    QList<CardPoint> m_oneCard;  //a container that stores the single card
    QList<CardPoint> m_twoCard;  //container that stores the double cards
    QList<CardPoint> m_threeCard;//container that stores the triple cards
    QList<CardPoint> m_fourCard; //container that stores the quadruple cards
};

#endif // HAND_H
