#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic {

    class FieldDoctor: public Player{

        public:

            FieldDoctor(Board& board, City city);

            FieldDoctor& treat(City city) override;

            std::string role() const override{
                return "FieldDoctor";
            }
    };
}