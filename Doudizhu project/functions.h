//
//  functions.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef functions_h
#define functions_h

#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include "structures.h"

using namespace std;
void generate_cards()  //The index of the first card is 1 instead of 0
{
    
    char suit[4][10]={"Hearts","Diamonds","Spades","Clubs"};
    char name[15][12]={"A","2","3","4","5","6","7","8","9","10","J","Q","K","Black Joker","Red Joker"};
    for (int i=0;i<=3;i++)                   //set displayed_name and value
    {
        for(int name_num=0;name_num<=12;name_num++)
        {
            card[13*i+name_num+1].displayed_name = name[name_num];
            card[13*i+name_num+1].value = name_num+1;
        }
    }
    
    for(int order=1;order<=52;order++)    //Update the value of "A" and "2" to the actual values
    {
        if (card[order].displayed_name == "A")
        {
            card[order].value=14;
        }
        if (card[order].displayed_name == "2")
        {
            card[order].value=15;
        }
    }
    
    for (int i=0;i<13;i++)    //Set suits
    {
        for(int suit_num=0;suit_num<=3;suit_num++)
        {
            card[4*i+suit_num+1].suit = suit[suit_num];
        }
    }
    
    card[53].new_card(16, "NULL", name[13]);   //Set special jokers
    card[54].new_card(17, "NULL", name[14]);

}

void shuffle_cards()    //A shuffle algorithem from the Internet, which can make every card has the same probability to be each position in a deck.
{
    srand((unsigned int) time(NULL));
    int n=55,index;
    Card tmp;
    for(int i=1; i<=54; i++)
        {
            index=rand()%(n-i)+i;
            if(index!=i)
            {
                tmp=card[i];
                card[i]=card[index];
                card[index]=tmp;
            }
     
        }

}

void allocate_cards() //Every player can get 17 cards, and then the landlord will get extra 3 cards
{
    int card_index=1;
    for(int player_index=1;player_index<=3;player_index++)
    {
        player[player_index].clear_cardsInHand();
    }
    while(card_index<=51)
    {
        for(int player_index=1;player_index<=3;player_index++)
        {
            
            player[player_index].getCard(card[card_index]);
            card_index=card_index+1;
        }
    }
    

}

void allocate_cards_for_landlord()
{
    for(int player_index=1;player_index<=3;player_index++)
    {
        if (player[player_index].isLandlord() == true)
        {
            player[player_index].getCard(card[52]);
            player[player_index].getCard(card[53]);
            player[player_index].getCard(card[54]);
            break;
        }
    }
}


void sort_cardsInHand()
{
    for(int player_id=1;player_id<=3;player_id++)
    {
        player[player_id].sort_cardsInHand();
    }
}

void select_landlord()   //If nobody decides to be the landlord, return false
{
    cout<<"Your cards in hand are:"<<endl;
    player[1].show_cardsInHand();
    cout<<"The landlord cards are "<<card[52].displayed_name<<" , "<<card[53].displayed_name<<" and "<<card[54].displayed_name<<endl;
    cout<<"Do you want to be a landlord?"<<endl;
    string response;
    cin>>response;
    if ((response=="yes")||(response=="Yes")||(response=="YES"))
    {
        player[1].become_landlord();
    }
    else
    {
        shuffle_cards();
        allocate_cards();
        sort_cardsInHand();
        select_landlord();
    }
    
}

#endif /* functions_h */
