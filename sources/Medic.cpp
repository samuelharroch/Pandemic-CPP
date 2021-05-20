#include "Player.hpp"
#include "Medic.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

Medic::Medic(Board& board, City city):Player(board, city){
}

Medic& Medic::treat(City city){

    if(current_city != city){
        throw invalid_argument {"You can't treat this city "};
    }

    if (board[city] == 0){
        throw invalid_argument {"There is not infection in this city"};
    }

    board[city] = 0;

    return *this;
    
 }

 Medic& Medic::drive(City city){

    Player::drive(city);

    if(board.getDiscovers_cures().count(board.colors.at(city))!= 0 ){
        board[city] = 0;
    }

    return *this;

 }

 Medic& Medic::fly_direct(City city){
    Player::fly_direct(city);

     if(board.getDiscovers_cures().count(board.colors.at(city))!= 0 ){
        board[city] = 0;
    }

    return *this;
 }

 Medic& Medic::fly_charter(City city){

     Player::fly_charter(city);
     if(board.getDiscovers_cures().count(board.colors.at(city))!= 0 ){
        board[city] = 0;
    }

    return *this;
 }

 Medic& Medic::fly_shuttle(City city){

     Player::fly_shuttle(city);
     
     if(board.getDiscovers_cures().count(board.colors.at(city))!= 0 ){
        board[city] = 0;
    }

    return *this;
 }
            
 