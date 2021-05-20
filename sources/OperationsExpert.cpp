#include "Player.hpp"
#include "OperationsExpert.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <string.h>
using namespace std;
using namespace pandemic;

OperationsExpert::OperationsExpert(Board& board, City city):Player(board, city){

}

OperationsExpert& OperationsExpert::build(){
         
    board.build_station(current_city);

    return *this;
}

