#include "Player.hpp"
#include "Dispatcher.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

Dispatcher::Dispatcher(Board& board, City city):Player(board, city){

}

Dispatcher& Dispatcher::fly_direct(City city){

    if ( current_city == city){
        throw invalid_argument{"You are already i the destination city"};
    }

    if( board.getSations().count(current_city) != 0){
        this->current_city = city;
        return *this;
    }

    Player::fly_direct(city);
    
    return *this;   
}