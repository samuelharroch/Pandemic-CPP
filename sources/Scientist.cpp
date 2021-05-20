#include "Player.hpp"
#include "Scientist.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

Scientist::Scientist(Board& board, City city,  int n):Player(board, city), n(n){

}

Scientist& Scientist::discover_cure(Color color){

    if (board.getSations().count(current_city) == 0 ){
        throw invalid_argument {"There is no research station in the destination city "};
    }
    if(board.getDiscovers_cures().count(color) != 0){
        return *this;
    }

    int count = 0;

    for( City city : this->cards){
        if(board.colors.at(city) == color){
            count++;
        }
    }

    if (count< this->n){
        throw invalid_argument {"You don't have enough cards"};
    }

    count = this->n; // reset counter to num of card to erase

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