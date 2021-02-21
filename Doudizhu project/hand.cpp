//
//  hand.cpp
//  Doudizhu project
//
//  Created by ARCK on 25/01/2021.
//


#include "hand.h"

Hand::Hand()
{

}

//define by type, values and the number of cards
Hand::Hand(HandType type, CardPoint base, int extra)
{
    m_handtype = type;
    m_basepoint = base;
    m_extra = extra;
}

//convert
Hand::Hand(QList<card> cards)
{
    InitByCardsList(cards);
    DefineHandType();
}

//judge if a group of cards can defeat the other group of cards
bool Hand::Defeat(Hand &hand)
{
    //mine is Rocket
    if(m_handtype==Hand_Bomb_Jokers) return true;
    //Opponent is Rocket
    if(hand.m_handtype== Hand_Bomb_Jokers) return false;
    //mine is Bomb
    if(hand.m_handtype>=Hand_Single&&hand.m_handtype<=Hand_Seq_Pair
            &&m_handtype==Hand_Bomb)
        return true;
    //types are same
    if(m_handtype==hand.m_handtype)
    {
        if(m_handtype==Hand_Seq_Pair||m_handtype==Hand_Seq_Single)
            return ((m_basepoint>hand.m_basepoint)&&(m_extra==hand.m_extra));
        else
            return m_basepoint>hand.m_basepoint;
    }

    return false;
}

//judge the type of a group of cards
void Hand::DefineHandType()
{
    if(m_oneCard.size()==0 &&
            m_twoCard.size()==0 &&
            m_threeCard.size()==0 &&
            m_fourCard.size()==0)
    {
        m_handtype=Hand_Pass;
        m_basepoint=0;
        m_extra=0;
    }
    else if(m_oneCard.size()==1&&
            m_twoCard.size()==0&&
            m_threeCard.size()==0&&
            m_fourCard.size()==0
            )
    {
        m_handtype  = Hand_Single;
        m_basepoint = (int)m_oneCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==0&&
            m_twoCard.size()==1&&
            m_threeCard.size()==0&&
            m_fourCard.size()==0)
    {
        m_handtype=Hand_Pair;
        m_basepoint = (int)m_twoCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==0&&
            m_twoCard.size()==0&&
            m_threeCard.size()==1&&
            m_fourCard.size()==0
            )
    {
        m_handtype  = Hand_Triple;
        m_basepoint = (int)m_threeCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==1&&
            m_oneCard[0]!=Card_SJ&&
            m_oneCard[0]!=Card_BJ&&
            m_twoCard.size()==0&&
            m_threeCard.size()==1&&
            m_fourCard.size()==0
            )
    {
        m_handtype=Hand_Triple_Single;
        m_basepoint = (int)m_threeCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==0&&
            m_twoCard.size()==1&&
            m_threeCard.size()==1&&
            m_fourCard.size()==0
            )
    {
        m_handtype  = Hand_Triple_Pair;
        m_basepoint = (int)m_threeCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==0&&
            m_twoCard.size()==0&&
            m_threeCard.size()==2&&
            m_threeCard[0]+1==m_threeCard[1]&&
            m_fourCard.size()==0
            )
    {
        m_handtype=Hand_Plane;
        m_basepoint=m_threeCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==2&&
            m_oneCard[0]!=Card_SJ&&
            m_oneCard[1]!=Card_BJ&&
            m_oneCard[0]!=m_oneCard[1]&&
            m_twoCard.size()==0&&
            m_threeCard.size()==2&&
            m_threeCard[0]+1==m_threeCard[1]&&
            m_fourCard.size()==0
            )
    {
        m_handtype=Hand_Plane_Two_Single;
        m_basepoint=(int)m_threeCard[0];
        m_extra=0;
    }
    else if(
            m_oneCard.size()==0&&
            m_twoCard.size()==2&&
            m_threeCard.size()==2&&
            m_threeCard[0]+1==m_threeCard[1]&&
            m_fourCard.size()==0)
    {
        m_handtype=Hand_Plane_Two_Pair;
        m_basepoint=m_threeCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()>=5&&
            m_twoCard.size()==0&&
            m_threeCard.size()==0&&
            m_fourCard.size()==0)
    {
        qSort(m_oneCard.begin(),m_oneCard.end());
        if(m_oneCard.first()>=Card_3&&m_oneCard.last()<=Card_2&&
                m_oneCard.last()-m_oneCard.first()==(m_oneCard.size()-1))
        {
            m_handtype = Hand_Seq_Single;
            m_basepoint= m_oneCard[0];
            m_extra = m_oneCard.size();
        }
        else
            m_handtype=Hand_Unknown;
    }
    else if(
            m_oneCard.size()==0&&
            m_twoCard.size()>=3&&
            m_threeCard.size()==0&&
            m_fourCard.size()==0
            )
    {
        qSort(m_twoCard.begin(),m_twoCard.end());
        if(m_twoCard.first()>=Card_3 && m_twoCard.last()<=Card_2&&
                m_twoCard.last()-m_twoCard.first()==(m_twoCard.size()-1))
        {
            m_handtype= Hand_Seq_Pair;
            m_basepoint=m_twoCard[0];
            m_extra=m_twoCard.size();
        }
        else
            m_handtype=Hand_Unknown;
    }
    else if(m_oneCard.size()==0 &&
            m_twoCard.size()==0&&
            m_threeCard.size()==0&&
            m_fourCard.size()==1)
    {
        m_handtype=Hand_Bomb;
        m_basepoint=m_fourCard[0];
        m_extra=0;
    }
    else if(m_oneCard.size()==2 &&
            m_oneCard[0]==Card_SJ &&
            m_oneCard[1]==Card_BJ &&
            m_twoCard.size()==0&&
            m_threeCard.size()==0&&
            m_fourCard.size()==0)
    {
        m_handtype=Hand_Bomb_Jokers;
    }
    else {
        m_handtype=Hand_Unknown;
        m_basepoint=0;
        m_extra=0;
    }
}

//initialise containers
void Hand::InitByCardsList(QList<card> cardList)
{
    int CardPointRecord[16];        //an array to store the value of each card
    for(int i=0;i<16;i++)
        CardPointRecord[i]=0;

    for(int i=0;i<cardList.size();i++)
    {
        CardPointRecord[(int)cardList[i].point]++;
    }

    m_oneCard.clear();
    m_twoCard.clear();
    m_threeCard.clear();
    m_fourCard.clear();

    for(int i=1;i<16;i++)
    {
        if(CardPointRecord[i]==1)
            m_oneCard.append((CardPoint)i);
        else if(CardPointRecord[i]==2)
            m_twoCard.append((CardPoint)i);
        else if(CardPointRecord[i]==3)
            m_threeCard.append((CardPoint)i);
        else if(CardPointRecord[i]==4)
            m_fourCard.append((CardPoint)i);
    }

}

//get type
HandType Hand::getHandType()
{
    return m_handtype;
}

//get values
int Hand::getBasePoint()
{
    return m_basepoint;
}

//get the number of cards
int Hand::getExtra()
{
    return m_extra;
}

