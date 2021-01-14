//
//  main.cpp
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//


#include "structures.h"
#include "functions.h"




int main(int argc, const char * argv[]) {
  
    CardGroup test_buffer;
    generate_cards();
    allocate_cards();
    player[1].become_landlord();
    allocate_cards_for_landlord();
    player[1].show_cardsInHand();
    player[2].show_cardsInHand();
    player[3].show_cardsInHand();
    test_buffer.getCard(player[2].pick_one_card(5));  //4
    test_buffer.getCard(player[1].pick_one_card(1));//4
    test_buffer.getCard(player[1].pick_one_card(2));//7
    test_buffer.getCard(player[1].pick_one_card(6));//6
    test_buffer.getCard(player[3].pick_one_card(5));//5
    test_buffer.getCard(player[2].pick_one_card(1));//5
    test_buffer.getCard(player[3].pick_one_card(1));//6
    test_buffer.getCard(player[3].pick_one_card(0));//3
    test_buffer.getCard(player[1].pick_one_card(5));  //3
    test_buffer.getCard(player[2].pick_one_card(6));  //10
    test_buffer.sort_cards();
    test_buffer.analysis_type();
    cout<<test_buffer.getType()<<endl;;
    

    
    
}
