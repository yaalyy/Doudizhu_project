#ifndef CARD_H
#define CARD_H

//the values of poker
enum CardPoint
{
    Card_Begin,

    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,

    Card_SJ,
    Card_BJ,

    Card_End
};

//the suit of poker
enum CardSuit
{
    Suit_Begin,

    Diamond,
    Club,
    Heart,
    Spade,

    Suit_End
};

//the groups of poker
enum HandType
{
    Hand_Unknown,
    Hand_Pass,
    Hand_Single,
    Hand_Pair,
    Hand_Triple,
    Hand_Triple_Single,
    Hand_Triple_Pair,
    Hand_Plane,
    Hand_Plane_Two_Single,
    Hand_Plane_Two_Pair,
    Hand_Seq_Single,
    Hand_Seq_Pair,
    Hand_Bomb,
    Hand_Bomb_Jokers,
};


class card
{
public:
    card(CardPoint p=Card_Begin,CardSuit s=Suit_Begin);
    card(int number);
    CardPoint point;    //value of card
    CardSuit suit;      //the suit of card

    void setPoint(CardPoint p);// set a value
    CardPoint getPoint();      // get a value
    void setSuit(CardSuit s);  // set a suit
    CardSuit getSuit();        // get a suit
};

#endif // CARD_H
