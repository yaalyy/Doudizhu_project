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
    
    allocate_cards();
    CardGroup buffer;
    buffer.getCard(player[1].pick_one_card(0));
    buffer.getCard(player[2].pick_one_card(4));
    buffer.analysis_type();
    return 0;
}
