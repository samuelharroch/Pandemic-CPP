#include "doctest.h"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"

using namespace pandemic;

#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

void take_5_red_cards(Player& player) {
	player.take_card(City::Sydney)
	      .take_card(City::HoChiMinhCity)
	      .take_card(City::HongKong)
	      .take_card(City::Bangkok)
          .take_card(City::Tokyo);
}

TEST_CASE("drive"){

    Board board;
    OperationsExpert expert {board, City::Bogota};

    CHECK_NOTHROW(expert.drive(City::MexicoCity));
    CHECK_NOTHROW(expert.drive(City::MexicoCity));// should'nt throw if you "drive" to the current city  

    //check chain call 
    CHECK_NOTHROW(expert.drive(City::LosAngeles).drive(City::MexicoCity));

    //illegal drives
    CHECK_THROWS(expert.drive(City::BuenosAires));
    CHECK_THROWS(expert.drive(City::Paris));

}

TEST_CASE("build and OperationsExpert skills"){

    Board board;

    Dispatcher dispatcher{board, City::MexicoCity};
    OperationsExpert expert {board, City::Bogota};

    CHECK_NOTHROW(expert.build()); // should build even no Bogota card
    CHECK_NOTHROW(expert.build());//should not trhow even there is research station in Bogota

    CHECK_THROWS(dispatcher.build()); // illegal cause no MexicoCity card yet to the dispatcher

    dispatcher.take_card(City::MexicoCity);
    CHECK_NOTHROW(dispatcher.build()); // should build and discard the MexicoCity card
    
}

TEST_CASE("fly_direct and Dispatcher skills"){

    Board board;

    Dispatcher dispatcher{board, City::LosAngeles};
    OperationsExpert expert {board, City::Bogota};

    CHECK_THROWS(expert.fly_direct(City::LosAngeles));//have not the LA card 

    // build station in Bogota and take LosAngeles card
    expert.build()
        .take_card(City::LosAngeles);

    CHECK_NOTHROW(expert.fly_direct(City::LosAngeles));// then legal direct fly 
    expert.build() ;// build station in LA

    /*legal action for dipatcher even no card cause there are station in LA and Bogota
    */
    CHECK_NOTHROW(dispatcher.fly_direct(City::Bogota));
    CHECK_NOTHROW(dispatcher.fly_direct(City::Paris));

    CHECK_THROWS(dispatcher.fly_direct(City::Bogota));// no station in Paris 
    //take Bogota card and fly - legal 
    CHECK_NOTHROW(dispatcher.take_card(City::Bogota).fly_direct(City::Bogota));

}

TEST_CASE("fly_charter"){
    Board board;

    Dispatcher dispatcher{board, City::LosAngeles};

    CHECK_THROWS(dispatcher.fly_charter(City::Paris));

    CHECK_NOTHROW(dispatcher.take_card(City::LosAngeles).fly_charter(City::Paris));

    CHECK_THROWS(dispatcher.fly_charter(City::London));

    CHECK_NOTHROW(dispatcher.take_card(City::Paris).fly_charter(City::London));
}

TEST_CASE("fly_shuttle "){
    Board board;

    Dispatcher dispatcher{board, City::LosAngeles};
    OperationsExpert expert {board, City::Bogota};

    expert.build();// expert build in Bogota 
    dispatcher.take_card(City::LosAngeles).build();// dispatcher build in Bogota 

    //now we can make fly shuttle between them 
    CHECK_NOTHROW(expert.fly_shuttle(City::LosAngeles));
    CHECK_NOTHROW(dispatcher.fly_shuttle(City::Bogota));
    
    CHECK_THROWS(dispatcher.fly_shuttle(City::Paris));
    CHECK_THROWS(expert.fly_shuttle(City::Paris));

    dispatcher.take_card(City::Paris).take_card(City::Bogota);
    CHECK_THROWS(dispatcher.fly_shuttle(City::Paris));// should throw even we have Paris and Bogota card

}


TEST_CASE("discover_cure and Scientist, Researcher and GeneSplicer skills "){

    Board board;
    OperationsExpert expert {board, City::LosAngeles};
    Scientist scientist {board, City::Bangkok, 4};
    Researcher researcher {board, City::Tokyo};
    GeneSplicer geneSplicer {board, City::HongKong};

    take_5_red_cards(expert);
    
    CHECK_THROWS(expert.discover_cure(Color::Red)); // still not station in LA
    CHECK_NOTHROW(expert.build().discover_cure(Color::Red));// legal 

    /**
     * let's test case of scientist and cure an color red disease
     * which as already a cure .
     */
    take_5_red_cards(scientist);
    scientist.build();// Build station in Bankok- 4 red card now 

    CHECK_NOTHROW(scientist.discover_cure(Color::Red)); // not throw and still has 4 red cards
    board.remove_cures(); // now no cure at all
    CHECK_NOTHROW(scientist.discover_cure(Color::Red));// legal for scientist with 4 card
    board.remove_cures(); // now no cure at all
    CHECK_THROWS(scientist.discover_cure(Color::Red));// illegal with 0 card

    /**
     * let's test case of researcher and cure an color red disease
     * which as already a cure .
     */
    take_5_red_cards(researcher);
    CHECK_NOTHROW(scientist.discover_cure(Color::Red));// legal for researcher with 5 card even no station in ToKyo
    
    take_5_red_cards(researcher);
    CHECK_NOTHROW(researcher.discover_cure(Color::Red)); // not throw and still has 5 red cards
    
    board.remove_cures(); // now no cure at all
    researcher.build();// build station in Tokyo - 4 red card now 
    CHECK_THROWS(scientist.discover_cure(Color::Red));// illegal with 4 card for a researcher
    board.remove_cures(); // now no cure at all

     /**
     * let's test case of GeneSplicer and cure an color red disease
     * which as already a cure .
     */
    take_5_red_cards(geneSplicer);
    geneSplicer.build();// station HongKong
    geneSplicer.take_card(City::Paris);// still 5 card, 4 red 1 blue
    CHECK_NOTHROW(geneSplicer.discover_cure(Color::Yellow));// can discover yellow cur with any 5 cards 
}

TEST_CASE("Board [] operator "){
    Board board;

    //the board should be clean 
    CHECK(board.is_clean()== true);

    board[City::MexicoCity] = 3;      // put 3 yellow disease cubes in MexicoCity.
	board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
	board[City::LosAngeles] = 3;    // put 3 yellow disease cubes in LosAngeles
	board[City::Bogota] = 1;        // put 1 red disease cube in Bogota
	board[City::BuenosAires] = 1;   // put 1 red disease cube in BuenosAires

    /* check if the [] operator work correctly to "set" disease cubes
    */
    CHECK(board[City::MexicoCity] == 2);
    CHECK(board[City::LosAngeles] == 3);
    CHECK(board[City::Bogota] == 1);
    CHECK(board[City::BuenosAires] == 1);
}

TEST_CASE("treat and Medic, Virologist and FieldDoctor skills"){

    Board board;

    OperationsExpert expert{board, City::LosAngeles};
    Medic medic{board, City::Bogota};
    Virologist viro {board, City::Miami};
    FieldDoctor doctor {board, City::MexicoCity};

    board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
	board[City::LosAngeles] = 3;    // put 3 yellow disease cubes in LosAngeles
	board[City::Bogota] = 4;        // put 1 red disease cube in Bogota
	board[City::Miami] = 4;   // put 1 red disease cube in BuenosAires

    /*simple treat by the expert */
    CHECK_NOTHROW(expert.treat(City::LosAngeles));
    CHECK(board[City::LosAngeles] == 2);

    CHECK_THROWS(expert.treat(City::Washington));// expert are not in Washington

    /*test Medic
    */
   CHECK_THROWS(medic.treat(City::LosAngeles)); // Medic not in LA
   CHECK_NOTHROW(medic.treat(City::Bogota));// Bogota should be clean now 
   CHECK(board[City::Bogota] == 0);
   CHECK_THROWS(medic.treat(City::Bogota));// Bogota is already clean

   expert.build();// in LA
   // create GeneSplicer and discover cure for yellow desaese
   GeneSplicer geneSplicer {board, City::LosAngeles};
   take_5_red_cards(geneSplicer);
   geneSplicer.discover_cure(Color::Yellow);

   board[City::Bogota]=2; // 2 cubes in Bogota
   CHECK(board[City::Bogota] == 0); // even no treat was execute
   
   //should cure all the City 
   medic.drive(City::Miami).drive(City::MexicoCity).drive(City::LosAngeles);
   CHECK(board[City::Miami] == 0);
   CHECK(board[City::MexicoCity] == 0);
   CHECK(board[City::LosAngeles] == 0);

    /*test Virologist
    */
    board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
    board[City::LosAngeles] = 3;    // put 3 yellow disease cubes in LosAngeles
	board[City::Bogota] = 4;        // put 1 red disease cube in Bogota
	board[City::Miami] = 4;
    
    CHECK_NOTHROW(viro.treat(City::Miami));
    CHECK(board[City::Miami] == 0); //only miami 
    CHECK(board[City::MexicoCity] == 2);
   CHECK(board[City::LosAngeles] == 3);
   CHECK(board[City::Bogota] == 4);

    viro.take_card(City::Miami);
    CHECK_THROWS(viro.treat(City::Miami));// should throw!!!! 0 cube in Miami so no treat accept 

    viro.take_card(City::MexicoCity);
    // should cure all the yellow disaese
    CHECK_NOTHROW(viro.drive(City::MexicoCity).treat(City::MexicoCity));
    CHECK(board[City::MexicoCity] == 0);
   CHECK(board[City::LosAngeles] == 0);
   CHECK(board[City::Bogota] == 0);

    /*test FieldDoctor 
    */
    board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
    board[City::LosAngeles] = 3;    // put 3 yellow disease cubes in LosAngeles
	board[City::Bogota] = 4;        // put 1 red disease cube in Bogota
	board[City::Miami] = 4;

    CHECK_NOTHROW(doctor.treat(City::MexicoCity));
    CHECK(board[City::MexicoCity] == 0);
    CHECK(board[City::Miami] == 0);
   CHECK(board[City::LosAngeles] == 0);
   CHECK(board[City::Bogota] == 0);

    board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
    board[City::BuenosAires] = 3;      // change number of disease cubes in BuenosAires to 3.
    CHECK_NOTHROW(doctor.treat(City::MexicoCity));
    CHECK(board[City::MexicoCity] == 0);// only MexicoCity was cure - 
    CHECK(board[City::BuenosAires] == 3);//BuenosAires is not adjacent 
    

}

TEST_CASE("Board functions"){
    Board board;

    //the board should be clean 
    CHECK(board.is_clean()== true);

    board[City::MexicoCity] = 3;      // put 3 yellow disease cubes in MexicoCity.
	board[City::MexicoCity] = 2;      // change number of disease cubes in MexicoCity to 2.
	board[City::LosAngeles] = 3;    // put 3 yellow disease cubes in LosAngeles
	board[City::Bogota] = 1;        // put 1 red disease cube in Bogota
	board[City::BuenosAires] = 1;   // put 1 red disease cube in BuenosAires

    /* check if the [] operator work correctly to "set" disease cubes
    */
    CHECK(board[City::MexicoCity] == 2);
    CHECK(board[City::LosAngeles] == 3);
    CHECK(board[City::Bogota] == 1);
    CHECK(board[City::BuenosAires] == 1);

    //the board shouldn't  be clean 
    CHECK_FALSE(board.is_clean());

    /*create an OperationsExpert placed in BuenosAires (one Yellow cube )
    and treat the disease, should be now 0 disease cube in BuenosAires */
    OperationsExpert expert {board, City::BuenosAires};
    expert.treat(City::BuenosAires);
    CHECK(board[City::BuenosAires] == 0); //check if the board is update 

    //same as above for Bogota
    expert.drive(City::Bogota);
    expert.treat(City::Bogota);
    CHECK(board[City::Bogota] == 0);//check if the board is update
    // another way to check if there are not disease cubes in Bogota
    CHECK_THROWS(expert.treat(City::Bogota));

    /*build an research station in Bogota 
    and take 5 Yellow cards */
    expert.build();
    expert.take_card(City::Bogota)
        .take_card(City::LosAngeles)
        .take_card(City::BuenosAires)
        .take_card(City::Kinshasa)
        .take_card(City::MexicoCity);
    /*
    discover a yellow cure (legal cause we have 5 yellow cards),
    then drive to MexicoCity and treat the disease - should cure all 
    the disease cubes; same for LosAngeles*/
    expert.discover_cure(Color::Yellow)
        .drive(City::MexicoCity)
        .treat(City::MexicoCity)
        .drive(City::LosAngeles)
        .treat(City::LosAngeles);

    //the board should be clean now 
    CHECK(board[City::MexicoCity] == 0);
    CHECK(board[City::LosAngeles] == 0);
    CHECK(board.is_clean()== true);
    
    //remove the yellow cure and add disease cubes in LosAngeles
    board.remove_cures();
    board[City::LosAngeles] = 3;

    //we dont have a yellow cure so the treat operation should cure only one cube
    expert.treat(City::LosAngeles);
    // two ways to check that the boards remove properly the yellow cure 
    CHECK_NE(board[City::LosAngeles] , 0);
    CHECK_FALSE(board.is_clean()); 
}