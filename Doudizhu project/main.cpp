//
//  main.cpp
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//


#include "structures.h"
#include "functions.h"




int main(int argc, const char * argv[]) {
   
    generate_cards();
    shuffle_cards();
    allocate_cards();
    sort_cardsInHand();
    select_landlord();
    allocate_cards_for_landlord();
    sort_cardsInHand();

    return 0;
}
