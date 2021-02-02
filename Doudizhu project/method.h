#ifndef METHOD_H
#define METHOD_H

//this file is for reminding players or robots to play

#include "hand.h"
#include "player.h"
#include<QWidget>
#include<QMap>



class Method
{
public:
    Method(Player* player, QList<card> cards);
    ~Method();

    int CountOfPoint(QList<card> cards, CardPoint point);
    QList<card> MakeDecision();

    QList<card> FindSamePointCards(CardPoint point, int count);// given a point and a count, find a satisfied card
    QList<QList<card> > FindCardsByCount(int count);// find cards by the count
    QList<card> GetRangeCards(CardPoint beginPoint, CardPoint endPoint);// find cards in the range
    QList<card> GetFirstSeqSingleRange();               // find the first card in a Straight

    // try to find a Straight in cards
    void PickSeqSingles(QList<QList<QList<card> > >& allSeqRecord, const QList<QList<card> >& seqInherited, QList<card> cards);
    QList<QList<card> > PickOptimalSeqSingles();

    // try to search for a group of cards to play
    QList<QList<card> >  FindHand(Hand hand, bool beat);

    QList<card> PlayFirst();// play cards at first
    QList<card> PlayBeatHand(Hand hand);// play cards to beat other cards
    bool WhetherToBeat(QList<card> &myCards);// whether to beat a group of cards

protected:
    Player* m_player;
    QList<card> m_cards;
};

#endif // METHOD_H
