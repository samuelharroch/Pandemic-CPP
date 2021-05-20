#pragma once
#include "City.hpp"
#include "Board.hpp"
#include "Color.hpp"
#include<set>
#include <string>

namespace pandemic {
    
    class Player{

        protected:
            Board& board; 
            City current_city;
            std::set<City> cards;
            Player(Board& board, City city);
        public: 

            Player& take_card(City city);
            virtual Player& drive(City city);
            virtual Player& fly_direct(City city);
            virtual Player& fly_charter(City city);
            virtual Player& fly_shuttle(City city);
            virtual Player& build();
            virtual Player& discover_cure(Color color);
            virtual Player& treat(City city);
            virtual std::string role() const = 0 ;
            void remove_cards();
    };
}