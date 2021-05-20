#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {

    class Virologist: public Player{

        public:

            Virologist(Board& board, City city);

            Virologist& treat(City city) override;

            std::string role() const override{
                return "Virologist";
            }
    };
}