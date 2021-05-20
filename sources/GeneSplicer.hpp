#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {

    class GeneSplicer: public Player{

        public:

            GeneSplicer(Board& board, City city);

            GeneSplicer& discover_cure(Color color) override;

            std::string role() const override{
                return "GeneSplicer";
            }
    };
}