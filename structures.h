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
#include<algorithm>
using namespace std;

class Card{            //The class for each card
  public:
    int value;
    string suit, displayed_name;
    void new_card(int new_value,string new_suit,string new_displayed_name)
    {
        value=new_value;
        suit=new_suit;
        displayed_name=new_displayed_name;
    }
};


class Player{   //The class for each player
    
private:
    deque<Card> cardsInHand;
    bool landlord_identifier=false;
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
        cardOrder = cardOrder - 1;
        deque<Card>::iterator iter = cardsInHand.begin()+cardOrder;
        cardsInHand.erase(iter);
    }
    void become_landlord()
    {
        landlord_identifier=true;
    }
    bool isLandlord()
    {
        return landlord_identifier;
    }
    
    bool comp(Card i,Card j)   //This function is for the procedure of sorting cards in hand
    {
      return (i.value<j.value);
    }

    void sort_cardsInHand()  //unfinished
    {
    for(int player_id=1;player_id<=3;player_id++)
    {     //Here use an array to export cards in hand, then erase the deque and sort the array, import the array into the deque
      sort(cardsInHand.begin(),cardsInHand.end(),comp);
    

    }
}
    
    
};

extern Card card[];
extern Player player[];



#endif /* structures_h */