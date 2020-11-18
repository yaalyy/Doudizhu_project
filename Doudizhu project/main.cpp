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
    cout<<card[54].displayed_name<<endl;
    return 0;
}
