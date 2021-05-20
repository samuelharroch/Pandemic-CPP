#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {

    class Scientist: public Player{

        private :
         int n;

        public:

            Scientist(Board& board, City city,  int n);

            Scientist& discover_cure(Color color) override;

            std::string role() const override{
                return "Scientist";
            }

    };
}