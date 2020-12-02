//
//  main.cpp
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#include<iostream>
#include "functions.h"
#include "structures.h"
using namespace std;



int main(int argc, const char * argv[]) {
    
    generate_cards();
    shuffle_cards();
    allocate_cards();
    
}
