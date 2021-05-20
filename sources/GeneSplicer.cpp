#include "Player.hpp"
#include "GeneSplicer.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;


const unsigned int cards_to_cure_g = 5;

GeneSplicer::GeneSplicer(Board& board, City city):Player(board, city){

}

GeneSplicer& GeneSplicer::discover_cure(Color color){

    if (board.getSations().count(current_city) == 0 ){
        throw invalid_argument {"There is no research station in the destination city "};
    }
    if(board.getDiscovers_cures().count(color) != 0){
        return *this;
    }


    if (this->cards.size()< cards_to_cure_g){
        throw invalid_argument {"You don't have enough cards"};
    }

    unsigned int count = cards_to_cure_g; // reset counter to num of card to erase

    for( auto it=cards.begin(); it!= cards.end();){
        
        if (count==0){ break;}
        it = this->cards.erase(it);
        count--;
        
    }

    board.add_cure(color); // update the board about the discovered cure 

    return *this;
}