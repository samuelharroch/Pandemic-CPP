#pragma once
#include "City.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Color.hpp"

namespace pandemic {

    class Medic: public Player{

        public:

            Medic(Board& board, City city) ;

            Medic& drive(City city) override;

            Medic& fly_direct(City city) override;

            Medic& fly_charter(City city) override;

            Medic& fly_shuttle(City city) override;
            
            Medic& treat(City city) override;

            std::string role() const override{
                return "Medic";
            }
    };
}