#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string>
#include <exception>
using namespace std;
using namespace pandemic;

const unsigned int cards_to_cure = 5;

Player::Player(Board& board, City city):board(board), current_city(city){

}

Player& Player::take_card(City city){
    this->cards.insert(city);
    return *this;
}
Player& Player::drive(City city){
    if(board.connections.at(this->current_city).count(city) == 0 || current_city == city){
        throw invalid_argument {"the destination is not accessable"};
    }
    this->current_city = city;
    return *this;
}
Player& Player::fly_direct(City city){

    if(cards.count(city) == 0 || current_city == city){
        throw invalid_argument {"You don't have the destination card \\ you are already in the city"};
    }
    cards.erase(city);
    this->current_city = city;
    return *this;
}
Player& Player::fly_charter(City city){

    if(cards.count(current_city) == 0 || current_city == city){
        throw invalid_argument {"You don't have the current city card \\ you are already in the city"};
    }
    cards.erase(current_city);
    this->current_city = city;
    return *this;
}
Player& Player::fly_shuttle(City city){

    if(  board.getSations().count(current_city) == 0 || board.getSations().count(city) == 0 || current_city == city){
        throw invalid_argument {"There is no research station in the destination city \\ you are already in the city"};
    }
    this->current_city = city;

    return *this;
}
Player& Player::build(){
    if (board.getSations().count(current_city) != 0 ){
        return *this;
    }
    
    if(cards.count(current_city) == 0 ){
            throw invalid_argument {"You don't have the current city card "};
    }
         
    cards.erase(current_city);
    board.build_station(current_city);

    return *this;
}

Player& Player::discover_cure(Color color){

    if (board.getSations().count(current_city) == 0 ){
        throw invalid_argument {"There is no research station in the destination city "};
    }
    if(board.getDiscovers_cures().count(color) != 0){
        return *this;
    }

    unsigned int count = 0;

    for( City city : this->cards){
        if(board.colors.at(city) == color){
            count++;
        }
    }

    if (count< cards_to_cure){
        throw invalid_argument {"You don't have enough cards"};
    }

    count = cards_to_cure; // reset counter to num of card to erase

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

Player& Player::treat(City city){

    if (current_city != city){
        throw invalid_argument {"You can't treat this city "};
    }

    if (board[city] == 0){
        throw invalid_argument {"There is not infection in this city"};
    }

    if (board.getDiscovers_cures().count(board.colors.at(city)) == 0){
        board[city]--;
    }
    else{
        board[city] = 0;
    }
    return *this;
}

void Player::remove_cards(){
    this->cards.clear();
}
