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
    if (select_landlord()==true)
    {
        player[1].become_landlord();
    }

    return 0;
}