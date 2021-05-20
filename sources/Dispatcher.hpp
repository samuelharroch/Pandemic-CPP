#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic {

    class Dispatcher: public Player{

        public:

            Dispatcher(Board& board, City city);

            Dispatcher& fly_direct(City city) override;

            std::string role() const override{
                return "Dispatcher";
            }
    };
}