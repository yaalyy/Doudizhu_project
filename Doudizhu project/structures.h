//
//  structures.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef structures_h
#define structures_h

#include<string>
#include<deque>
using namespace std;

class Card{            
  public:                            
    int value;
    string suit, displayed_name;
    void new_card(int new_value,string new_suit,string new_displayed_name)
    {
        value=new_value;
        suit=new_suit;
        displayed_name=new_displayed_name;
    }
}card[55];


class Player{
    
private:
    deque<Card> cardsInHand;
    
public:
    void getCard(Card newCard)
    {
        cardsInHand.push_back(newCard);
       
    }
    int getNumberOfCards()    //return how many cards in hand
    {
        int size = (unsigned int)cardsInHand.size();
        return size;
    }
    void playCard(int cardOrder)   //delete a card selected and the cards after it move front
    {
        deque<Card>::iterator iter = cardsInHand[cardorder];      //Here is a problem using deque
        cardsInHand.erase(iter);
    }
    
    
    
    
}player[4];


#endif /* structures_h */
