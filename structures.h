//
//  structures.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef structures_h
#define structures_h

#include<string>
#include<iostream>
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
    void become_landlord()  //Change the identifier status of the landlord
    {
        landlord_identifier=true;
    }
    bool isLandlord()   //Check if this player is a landlord
    {
        return landlord_identifier;
    }
    

    void sort_cardsInHand()   //Sort cards in hand
    {
    
      std::sort(cardsInHand.begin(),cardsInHand.end(),[](const Card &i, const Card &j){return i.value<j.value;});
    

    
    }
    
    void show_cardsInHand()   //Print cards in hand
    {
        for (int i = 0; i < cardsInHand.size(); i++) {
            cout << cardsInHand.at(i).displayed_name << ", ";
        }
        cout<<endl;
        
    }
    
    void clear_cardsInHand()  //Clear cards in hand
    {
        cardsInHand.clear();
    }
    
    
};

extern Card card[];
extern Player player[];



#endif /* structures_h */