#include "Player.hpp"
#include "Researcher.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <iostream>
#include <string.h>
using namespace std;
using namespace pandemic;

const unsigned int cards_to_cure_r = 5; 

Researcher::Researcher(Board& board, City city):Player(board, city){

}

Researcher& Researcher::discover_cure(Color color){
    
    if(board.getDiscovers_cures().count(color) != 0){
        return *this;
    }

    unsigned int count = 0;

    for( City city : this->cards){
        if(board.colors.at(city) == color){
            count++;
        }
    }

    if (count< cards_to_cure_r){
        throw invalid_argument {"You don't have enough cards"};
    }

    count = cards_to_cure_r; // reset counter to num of card to erase

    for(auto it=cards.begin(); it!= cards.end(); ){

        if (count==0){ break;}
        if(board.colors.at(*it) == color){
            it = cards.erase(it);
            count--;
        }
        else{
            it++;
        }
    }


    board.add_cure(color); // update the board about the discovered cure
    return *this;
}