//
//  structures.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef structures_h
#define structures_h

#include<string>
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


#endif /* structures_h */
