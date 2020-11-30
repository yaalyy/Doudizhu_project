//
//  main.cpp
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#include<iostream>
#include "structures.h"
#include "functions.h"
using namespace std;



int main(int argc, const char * argv[]) {
    
    generate_cards();
    shuffle_cards();
    for(int i=1;i<=3;i++)
    {
        player[1].getCard(card[i]);
    }
    player[1].playCard(3);
    cout<<player[1].getNumberOfCards();
    
}
