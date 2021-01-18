//
//  structures.h
//  Doudizhu project
//
//  Created by ARCK on 17/11/2020.
//

#ifndef structures_h
#define structures_h

#include<string>
#include<iostream>
#include<deque>
#include<algorithm>
#include<vector>
using namespace std;

class Card{            //The class for each card
  public:
    int value;
    string suit, displayed_name;
    void new_card(int new_value,string new_suit,string new_displayed_name)  //This method looks not very useful.
    {
        value=new_value;
        suit=new_suit;
        displayed_name=new_displayed_name;
    }
};

enum Type{      //Any possible valid group of cards
  Unknown=0,//Unknown type
    Single,//single card
    Pair,//a pair of cards
    Triplet,//Three cards with the same number
    Straight,
    PairSeq,//Pair sequence
    ThreeSeq,//  Triplet+2
    ThreePlus,//Three plus one   Triplet+1
    Plane,
    Quadruplet,//Four plus two
    Bomb,
  Rocket,
};

//extern bool checkContinuous(int cards[],int len);

struct Card_index{     //This is a structure to store the number of each card in a cardGroup
    vector<string> single_index;
    vector<string> double_index;
    vector<string> three_index;
    vector<string> four_index;
};

class CardGroup{   //A group of cards
    
  private:
    Type type=Unknown; //The type of a group of cards
    int count=0; //the number of cards
    int value=0; //the weight of this group, used for AI to decide to play cards
    deque<Card> cards;// the cards in the group
    Card_index card_index;
  public:
    void clear() //reset this group
    {
      count=0;
      value=0;
      type=Unknown;
      cards.clear();
    }
    void getCard(Card newCard)
    {
        cards.push_back(newCard);
        count++;
       
    }
    int getCount()    //return the number of cards
    {
        
        return count;
    }

    void DeleteCard(int cardOrder)   //delete a card selected and the cards after it move front
    {
        cardOrder = cardOrder - 1;
        deque<Card>::iterator iter = cards.begin()+cardOrder;
        cards.erase(iter);
        count--;
    }
    
    void sort_cards()   //Sort cards
    {
    
      std::sort(cards.begin(),cards.end(),[](const Card &i, const Card &j){return i.value<j.value;});
    
    }
    
    void show_cards()   //Print cards
    {
        for (int i = 0; i < count; i++) {
            cout << cards.at(i).displayed_name << ", ";
        }
        cout<<endl;      //******Here is a print. REMEMBER to change it after GUI
        
    }
    
    void analysis_card_index()   //Analysis the number of each card in a cardGroup
    {
        int card_num[18]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    //initialise an array
        for(int i=0;i<=count-1;i++)
        {
            card_num[cards.at(i).value]=card_num[cards.at(i).value]+1;   //the index of the card_num means the value of cards, and the data stored in the array means the number of cards
        }
        for(int i=3;i<=17;i++)
        {
            string tmp;    //perform codes well
            if ((i>=11) && (i<=17))
            {
                if(i==11)
                {
                    tmp = 'J';
                }
                if(i==12)
                {
                    tmp = 'Q';
                }
                if(i==13)
                {
                    tmp = 'K';
                }
                
                if(i==14)
                {
                    tmp = 'A';
                }
                if(i==15)
                {
                    tmp = '2';
                }
                if(i==16)
                {
                    tmp = "Black Joker";
                }
                if(i==17)
                {
                    tmp = "Red Joker";
                }
            }
            else if ((i>=3) && (i<=10))
            {
                 tmp = to_string(i);
            }
            
            if(card_num[i]==1)
            {
                card_index.single_index.push_back(tmp);
            }
            if(card_num[i]==2)
            {
                card_index.double_index.push_back(tmp);
            }
            if(card_num[i]==3)
            {
                card_index.three_index.push_back(tmp);
            }
            if(card_num[i]==4)
            {
                card_index.four_index.push_back(tmp);
            }
            
            
        }
    }
    
    bool isContinuousForThreeIndex()   //This subroutine is specifically to check the continuity of the set, which includes that the number of cards is three
    {
        if (card_index.three_index.empty())
        {
            return false;
        }
        extern bool checkContinuous(int cards[],unsigned int len);
        string transporter_1[20];
        int transporter_2[20];
        for(unsigned long item=0;item<=card_index.three_index.size()-1;item++)
        {
            transporter_1[item] = card_index.three_index[item];  //copy data in three_index into a local array
        }
        for(unsigned long item=0;item<=card_index.three_index.size()-1;item++)  //transfer string into integer, so checkContinuous can be used
        {
            if(transporter_1[item] == "A")
            {
                transporter_2[item] = 14;
            }
            else if(transporter_1[item] == "2")
            {
                transporter_2[item] = 15;
            }
            else if(transporter_1[item] == "3")
            {
                transporter_2[item] = 3;
            }
            else if(transporter_1[item] == "4")
            {
                transporter_2[item] = 4;
            }
            else if(transporter_1[item] == "5")
            {
                transporter_2[item] = 5;
            }
            else if(transporter_1[item] == "6")
            {
                transporter_2[item] = 6;
            }
            else if(transporter_1[item] == "7")
            {
                transporter_2[item] = 7;
            }
            else if(transporter_1[item] == "8")
            {
                transporter_2[item] = 8;
            }
            else if(transporter_1[item] == "9")
            {
                transporter_2[item] = 9;
            }
            else if(transporter_1[item] == "10")
            {
                transporter_2[item] = 10;
            }
            else if(transporter_1[item] == "J")
            {
                transporter_2[item] = 11;
            }
            else if(transporter_1[item] == "Q")
            {
                transporter_2[item] = 12;
            }
            else if(transporter_1[item] == "K")
            {
                transporter_2[item] = 13;
            }
            else if(transporter_1[item] == "Black Joker")
            {
                transporter_2[item] = 16;
            }
            else if(transporter_1[item] == "Red Joker")
            {
                transporter_2[item] = 17;
            }
        }
        if(checkContinuous(transporter_2, card_index.three_index.size()) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool isContinuousForDoubleIndex()   //This subroutine is specifically to check the continuity of the set, which includes that the number of cards is two
    {
        if (card_index.double_index.empty())
        {
            return false;
        }
        extern bool checkContinuous(int cards[],unsigned int len);
        string transporter_1[20];
        int transporter_2[20];
        for(unsigned long int item=0;item<=card_index.double_index.size()-1;item++)
        {
            transporter_1[item] = card_index.double_index[item];  //copy data in double_index into a local array
        }
        for(unsigned long int item=0;item<=card_index.double_index.size()-1;item++)  //transfer string into integer, so checkContinuous can be used
        {
            if(transporter_1[item] == "A")
            {
                transporter_2[item] = 14;
            }
            else if(transporter_1[item] == "2")
            {
                transporter_2[item] = 15;
            }
            else if(transporter_1[item] == "3")
            {
                transporter_2[item] = 3;
            }
            else if(transporter_1[item] == "4")
            {
                transporter_2[item] = 4;
            }
            else if(transporter_1[item] == "5")
            {
                transporter_2[item] = 5;
            }
            else if(transporter_1[item] == "6")
            {
                transporter_2[item] = 6;
            }
            else if(transporter_1[item] == "7")
            {
                transporter_2[item] = 7;
            }
            else if(transporter_1[item] == "8")
            {
                transporter_2[item] = 8;
            }
            else if(transporter_1[item] == "9")
            {
                transporter_2[item] = 9;
            }
            else if(transporter_1[item] == "10")
            {
                transporter_2[item] = 10;
            }
            else if(transporter_1[item] == "J")
            {
                transporter_2[item] = 11;
            }
            else if(transporter_1[item] == "Q")
            {
                transporter_2[item] = 12;
            }
            else if(transporter_1[item] == "K")
            {
                transporter_2[item] = 13;
            }
            else if(transporter_1[item] == "Black Joker")
            {
                transporter_2[item] = 16;
            }
            else if(transporter_1[item] == "Red Joker")
            {
                transporter_2[item] = 17;
            }
        }
        if(checkContinuous(transporter_2, card_index.double_index.size()) == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void analysis_type()   //Here assume cards have already been sorted
    {
        extern bool isEven(int num);
        analysis_card_index();
        
        if(count == 1) //single card
        {
            type=Single;
        }
        
        else if(count == 2)   //two cards
        {
            if(cards.at(0).displayed_name == cards.at(1).displayed_name)
            {
                type = Pair;
            }
            
            else if((cards.at(0).displayed_name == "Black Joker")&&(cards.at(1).displayed_name == "Red Joker"))
            {
                type = Rocket;    //*****This part very requires testing*****
            }
        }
        
        else if(count == 3)  //three cards
        {
            if((cards.at(0).displayed_name == cards.at(1).displayed_name)&&((cards.at(1).displayed_name == cards.at(2).displayed_name)))
            {
                type = Triplet;
            }
        }
        
        else if(count == 4)  //four cards
        {
            if((cards.at(0).displayed_name == cards.at(1).displayed_name)&&(cards.at(1).displayed_name == cards.at(2).displayed_name)&&(cards.at(2).displayed_name == cards.at(3).displayed_name))
            {
                type = Bomb;
            }
            else if(cards.at(1).displayed_name == cards.at(2).displayed_name)
            {
                if(cards.at(1).displayed_name == cards.at(0).displayed_name)
                {
                    if(cards.at(0).displayed_name != cards.at(3).displayed_name)
                    {
                        type = ThreePlus;
                    }
                }
                else if(cards.at(1).displayed_name == cards.at(3).displayed_name)
                {
                    if(cards.at(0).displayed_name != cards.at(3).displayed_name)
                    {
                        type = ThreePlus;
                    }
                }
            }
        }
        
        else if(count >= 5)
        {
            for(int item=0;item<=count-1;item++)
            {
                if((cards.at(item).displayed_name == "Black Joker")||(cards.at(item).displayed_name == "Red Joker"))    //If a joker is included in this group, any combo is impossible.
                {
                    return;
                }
            }
            //Straight
            for(int item=0;item<count-1;item++)
            {
                
                if((cards.at(item).value+1) != cards.at(item+1).value)
                {
                    break;
                }
                if(item == count-1-1)      //It means that the for loop runs into the last step successfully
                {
                    type = Straight;
                    return;   //there is no need to continue to match with other situations
                }
            }
            
            // Pair Sequence
            if (isEven(count) == true)
            {
                for(int item=0;item<count;item=item+2)
                {
                    if (cards.at(item).value != cards.at(item+1).value)
                    {
                        break;
                    }
                    if(item == count-1-1)
                    {
                        if (isContinuousForDoubleIndex())
                        {
                            type = PairSeq;
                            return;  //there is no need to continue to match with other situations
                        }
                        
                    }
                }
                
            }
            
            
            // Triplet+2
            if(count==5)
            {
                if ((cards.at(0).displayed_name == cards.at(1).displayed_name) && (cards.at(1).displayed_name == cards.at(2).displayed_name) && (cards.at(3).displayed_name == cards.at(4).displayed_name))
                {
                    type = ThreeSeq;
                    return;
                }
                else if ((cards.at(0).displayed_name == cards.at(1).displayed_name) && (cards.at(2).displayed_name == cards.at(3).displayed_name) && (cards.at(3).displayed_name == cards.at(4).displayed_name))
                {
                    type = ThreeSeq;
                    return;
                }
            }
            
            // Quadruplet
            if(cards.at(2).displayed_name == cards.at(3).displayed_name)   //If this is a Quadruplet, this condition must be satisfied
            {
                if(cards.at(1).displayed_name == cards.at(2).displayed_name)
                {
                    if(cards.at(0).displayed_name == cards.at(2).displayed_name)
                    {
                        if ((cards.at(4).displayed_name != cards.at(2).displayed_name) && (cards.at(5).displayed_name != cards.at(2).displayed_name))
                            {
                            type = Quadruplet;
                            return;
                        }
                    }
                    else if(cards.at(4).displayed_name == cards.at(2).displayed_name)
                    {
                        if (cards.at(5).displayed_name != cards.at(2).displayed_name)
                            {
                            type = Quadruplet;
                            return;
                        }
                    }
                }
                else if((cards.at(4).displayed_name == cards.at(2).displayed_name) && (cards.at(5).displayed_name == cards.at(2).displayed_name))
                {
                    if(cards.at(0).displayed_name != cards.at(2).displayed_name)
                    {
                        type = Quadruplet;
                        return;
                    }
                }
            }
            // Plane
           
            if ((card_index.four_index.empty() == true) && (isContinuousForThreeIndex() == true))
            {
                if ((card_index.single_index.empty() == true) && (card_index.double_index.empty() == true) && (card_index.three_index.size() == 2) )
                {
                    type = Plane;
                    return;
                }
                else if ((card_index.single_index.size() == 2) && (card_index.double_index.empty() == true) && (card_index.three_index.size() == 2) )
                {
                    type = Plane;
                    return;
                }
                else if ((card_index.single_index.empty() == true) && (card_index.double_index.size() == 2) && (card_index.three_index.size() == 2))
                {
                    type = Plane;
                    return;
                }
                
            }
            
            
            
            
        }
        
        
    }
    
    string getType()
    {
        switch(type)
        {
                
            case 0: return "Unknown"; break;
            case 1: return "Single";break;
            case 2: return "Pair";break;
            case 3: return "Triplet";break;
            case 4: return "Straight";break;
            case 5: return "PairSeq";break;
            case 6: return "ThreeSeq";break;
            case 7: return "ThreePlus";break;
            case 8: return "Plane";break;
            case 9: return "Quadruplet";break;
            case 10: return "Bomb";break;
            case 11: return "Rocket";break;
        };
    }

};


class Player{   //The class for each player
    
private:
    deque<Card> cardsInHand;
    bool landlord_identifier=false;
public:
    void getCard(Card newCard)
    {
        cardsInHand.push_back(newCard);
       
    }
    int getNumberOfCards()    //return how many cards in hand
    {
        int size = (unsigned int)cardsInHand.size();
        return size;
    }
    void playCard(int cardOrder)   //delete a card selected and the cards after it move front
    {
        cardOrder = cardOrder - 1;
        deque<Card>::iterator iter = cardsInHand.begin()+cardOrder;
        cardsInHand.erase(iter);
    }   
    void become_landlord()  //Change the identifier status of the landlord
    {
        landlord_identifier=true;
    }
    bool isLandlord()   //Check if this player is a landlord
    {
        return landlord_identifier;
    }
    

    void sort_cardsInHand()   //Sort cards in hand
    {
    
      std::sort(cardsInHand.begin(),cardsInHand.end(),[](const Card &i, const Card &j){return i.value<j.value;});
    

    
    }
    
    void show_cardsInHand()   //Print cards in hand
    {
        for (unsigned long int i = 0; i < cardsInHand.size(); i++) {
            cout << cardsInHand.at(i).displayed_name << ", ";
        }
        cout<<endl;  //******Here is a print. REMEMBER to change it after GUI
        
    }
    
    
    void clear_cardsInHand()  //Clear cards in hand
    {
        cardsInHand.clear();
    }
       
    Card pick_one_card(int num)   
    {
        return cardsInHand.at(num);
    }
    
    
    
};

extern Card card[];
extern Player player[];



#endif /* structures_h */
