#include "Player.hpp"
#include "Virologist.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

Virologist::Virologist(Board &board, City city) : Player(board, city)
{
}

Virologist &Virologist::treat(City city)
{

    if (current_city == city)
    {
        Player::treat(city);
    }
    else
    {

        if (this->cards.count(city) != 0)
        {

            if (board[city] == 0)
            {
                throw invalid_argument{"There is not infection in this city"};
            }

            this->cards.erase(city);

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
    }
    return *this;
}