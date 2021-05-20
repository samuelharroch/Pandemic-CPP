#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic {

    class OperationsExpert: public Player{

        public:

            OperationsExpert(Board& board, City city);

            OperationsExpert& build() override;

            std::string role() const override{
                return "OperationsExpert";
            }
    };
}