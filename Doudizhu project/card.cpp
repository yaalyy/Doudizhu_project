//
//  card.cpp
//  Doudizhu project
//
//  Created by ARCK on 22/01/2021.
//

#include "card.h"

//create a card by value and suit
card::card(CardPoint p, CardSuit s)
{
    point=p;
    suit=s;
}

//create a card by the number
card::card(int number)
{
    if(number>=1 && number<=54){
        point=CardPoint((number-1)/4+1);
        if(number==53||number==54)
            suit=Suit_Begin;
        else
            suit=CardSuit((number-1)%4+1);
    }
}

//set a value
void card::setPoint(CardPoint p)
{
    point=p;
    return;
}

//get a value
CardPoint card::getPoint()
{
    return point;
}

//set a suit
void card::setSuit(CardSuit s)
{
    suit=s;
    return;
}

//get a suit
CardSuit card::getSuit()
{
    return suit;
}
