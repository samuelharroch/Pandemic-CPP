#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {

    class Researcher: public Player{

        public:

            Researcher(Board& board, City city);

            Researcher& discover_cure(Color color) override;

            std::string role() const override{
                return "Researcher";
            }
    };
}