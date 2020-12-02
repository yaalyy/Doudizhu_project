//
//  functions.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef functions_h
#define functions_h


#include<cstdlib>
#include<ctime>
#include "structures.h"

void generate_cards()  //The index of the first card is 1 instead of 0
{
    
    char suit[4][10]={"Hearts","Diamonds","Spades","Clubs"};
    char name[15][12]={"A","2","3","4","5","6","7","8","9","10","J","Q","K","Black Joker","Red Joker"};
    for (int i=0;i<=3;i++)
    {
        for(int name_num=0;name_num<=12;name_num++)
        {
            card[13*i+name_num+1].displayed_name = name[name_num];
            card[13*i+name_num+1].value = name_num+1;
        }
    }
    
    for(int i=1;i<=52;i++)
    {
        if (card[i].displayed_name == "A")
        {
            card[i].value=14;
        }
        if (card[i].displayed_name == "2")
        {
            card[i].value=15;
        }
    }
    
    for (int i=0;i<13;i++)
    {
        for(int suit_num=0;suit_num<=3;suit_num++)
        {
            card[4*i+suit_num+1].suit = suit[suit_num];
        }
    }
    
    card[53].new_card(16, "NULL", name[13]);
    card[54].new_card(17, "NULL", name[14]);

}

void shuffle_cards()
{
    srand((unsigned int) time(NULL));
    int n=54,index;
    Card tmp;
    for(int i=1; i<54; i++)
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
  while(card_index<=51)
  {
    for(int player_index=1;player_index<=3;player_index++)
    {
      player[player_index].getCard(card[card_index]);
      card_index=card_index+1;
    }
  }                                 //Here should wait for a landlord


}
#endif /* functions_h */
