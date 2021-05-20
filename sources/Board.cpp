#include "Board.hpp"
#include <iostream>

using namespace std;
using namespace pandemic;

Board::Board(){}

bool Board::is_clean() const{

    for (const auto &it : cubes ){
        if (it.second != 0){
            return false;
        }
    }
    return true;
}

Board& Board::remove_cures (){
            discovers_cures.clear();
            return *this;
        }

Board& Board::remove_stations(){
            stations.clear();
            return *this ;
        }

 int& Board::operator[](City city) {
    
    return this->cubes[city];
}

 int Board::operator[](City city) const{
    
    return this->cubes.at(city);
}


// std::ostream& operator<<(std::ostream& output, const Board& board){
//     output<< 1;
//     return output;
// }