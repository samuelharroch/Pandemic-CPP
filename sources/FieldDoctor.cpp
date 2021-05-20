#include "Player.hpp"
#include "FieldDoctor.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

FieldDoctor::FieldDoctor(Board &board, City city) : Player(board, city)
{
}

FieldDoctor &FieldDoctor::treat(City city)
{

    if (current_city == city)
    {
        Player::treat(city);
        return *this;
    }

    if (board.connections.at(current_city).count(city) != 0)
    {
        if (board[city] == 0)
        {
            throw invalid_argument{"There is not infection in this city"};
        }

        if (board.getDiscovers_cures().count(board.colors.at(city)) == 0)
        {
            board[city]--;
        }
        else
        {
            board[city] = 0;
        }
        
    }else{
        throw invalid_argument{"You don't have the city card"};
    }

    return *this;
}