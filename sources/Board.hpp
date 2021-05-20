#pragma once
#include "City.hpp"
#include "Color.hpp"
#include <map>
#include <set>
#include <iostream>

namespace pandemic
{

    class Board
    {
    private:

        std::map<City,  int> cubes;
        std::set<City> stations;
        std::set<Color> discovers_cures;

    public:
        Board();
        bool is_clean() const;

        Board &remove_cures();

        Board &remove_stations();

         int &operator[](City city); /// set 

         int operator[](City city) const; //get 

        friend std::ostream &operator<<(std::ostream &out, const Board &b)
        {   
           // std::boolalpha; 
            for( const auto &it : b.cubes){

                bool station_flag = false;
                if (b.stations.count(it.first)>0){
                    station_flag = true;
                }
                out<< b.cities_names.at(it.first)<< " : num of diseases: "<< b.cubes.at(it.first)<< " ,  station : " << station_flag << endl;

            }

            for (const auto &it : b.colors_names){
                bool cure_flag = false;
                if (b.discovers_cures.count(it.first)>0){
                    cure_flag = true;
                }
                out<< b.colors_names.at(it.first)<<"  cure: "<< cure_flag<< endl ;
            }
            return out;
        }

        std::map<City,  int> getCubes() const{
            return cubes;
        }

        std::set<City> getSations() const{
            return stations;
        }
        std::set<Color> getDiscovers_cures() const {
            return discovers_cures;
        }

        void add_cure(Color color){
            discovers_cures.insert(color);
        }

        void build_station(City city){

            stations.insert(city);
        }

        const std::map<City, std::set<City>> connections{
            {Algiers, {Madrid, Paris, Istanbul, Cairo}},
            {Atlanta, {Chicago, Miami, Washington}},
            {Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi}},
            {Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}},
            {Beijing, {Shanghai, Seoul}},
            {Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}},
            {BuenosAires, {Bogota, SaoPaulo}},
            {Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}},
            {Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}},
            {Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}},
            {Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata}},
            {Essen, {London, Paris, Milan, StPetersburg}},
            {HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila}},
            {HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}},
            {Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}},
            {Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney}},
            {Johannesburg, {Kinshasa, Khartoum}},
            {Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}},
            {Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg}},
            {Kinshasa, {Lagos, Khartoum, Johannesburg}},
            {Kolkata, {Delhi, Chennai, Bangkok, HongKong}},
            {Lagos, {SaoPaulo, Khartoum, Kinshasa}},
            {Lima, {MexicoCity, Bogota, Santiago}},
            {London, {NewYork, Madrid, Essen, Paris}},
            {LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney}},
            {Madrid, {London, NewYork, Paris, SaoPaulo, Algiers}},
            {Manila, {Taipei, SanFrancisco, HoChiMinhCity, Sydney, HongKong}},
            {MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota}},
            {Miami, {Atlanta, MexicoCity, Washington, Bogota}},
            {Milan, {Essen, Paris, Istanbul}},
            {Montreal, {Chicago, Washington, NewYork}},
            {Moscow, {StPetersburg, Istanbul, Tehran}},
            {Mumbai, {Karachi, Delhi, Chennai}},
            {NewYork, {Montreal, Washington, London, Madrid}},
            {Osaka, {Taipei, Tokyo}},
            {Paris, {Algiers, Essen, Madrid, Milan, London}},
            {Riyadh, {Baghdad, Cairo, Karachi}},
            {SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila}},
            {Santiago, {Lima}},
            {SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid}},
            {Seoul, {Beijing, Shanghai, Tokyo}},
            {Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo}},
            {StPetersburg, {Essen, Istanbul, Moscow}},
            {Sydney, {Jakarta, Manila, LosAngeles}},
            {Taipei, {Shanghai, HongKong, Osaka, Manila}},
            {Tehran, {Baghdad, Moscow, Karachi, Delhi}},
            {Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco}},
            {Washington, {Atlanta, NewYork, Montreal, Miami}}};

        const std::map<City, Color> colors{
                {Algiers, {Black}},
                {Atlanta, {Blue}},
                {Baghdad, {Black}},
                {Bangkok, {Red}},
                {Beijing, {Red}},
                {Bogota, {Yellow}},
                {BuenosAires, {Yellow}},
                {Cairo, {Black}},
                {Chennai, {Black}},
                {Chicago, {Blue}},
                {Delhi, {Black}},
                {Essen, {Blue}},
                {HoChiMinhCity, {Red}},
                {HongKong, {Red}},
                {Istanbul, {Black}},
                {Jakarta, {Red}},
                {Johannesburg, {Yellow}},
                {Karachi, {Black}},
                {Khartoum, {Yellow}},
                {Kinshasa, {Yellow}},
                {Kolkata, {Black}},
                {Lagos, {Yellow}},
                {Lima, {Yellow}},
                {London, {Blue}},
                {LosAngeles, {Yellow}},
                {Madrid, {Blue}},
                {Manila, {Red}},
                {MexicoCity, {Yellow}},
                {Miami, {Yellow}},
                {Milan, {Blue}},
                {Montreal, {Blue}},
                {Moscow, {Black}},
                {Mumbai, {Black}},
                {NewYork, {Blue}},
                {Osaka, {Red}},
                {Paris, {Blue}},
                {Riyadh, {Black}},
                {SanFrancisco, {Blue}},
                {Santiago, {Yellow}},
                {SaoPaulo, {Yellow}},
                {Seoul, {Red}},
                {Shanghai, {Red}},
                {StPetersburg, {Blue}},
                {Sydney, {Red}},
                {Taipei, {Red}},
                {Tehran, {Black}},
                {Tokyo, {Red}},
                {Washington, {Blue}}
            }; 
        
        const std::map<Color, std::string> colors_names{
            {Yellow,{"Yellow"}},
            {Red,{"Red"}},
            {Blue,{"Blue"}},
            {Black, {"Black"}}
        };
        
         const std::map<City, std::string> cities_names{
                {Algiers, {"Algiers"}},
                {Atlanta, {"Atlanta"}},
                {Baghdad, {"Baghdad"}},
                {Bangkok, {"Bangkok"}},
                {Beijing, {"Beijing"}},
                {Bogota, {"Bogota"}},
                {BuenosAires, {"BuenosAires"}},
                {Cairo, {"Cairo"}},
                {Chennai, {"Chennai"}},
                {Chicago, {"Chicago"}},
                {Delhi, {"Delhi"}},
                {Essen, {"Essen"}},
                {HoChiMinhCity, {"HoChiMinhCity"}},
                {HongKong, {"HongKong"}},
                {Istanbul, {"Istanbul"}},
                {Jakarta, {"Jakarta"}},
                {Johannesburg, {"Johannesburg"}},
                {Karachi, {"Karachi"}},
                {Khartoum, {"Khartoum"}},
                {Kinshasa, {"Kinshasa"}},
                {Kolkata, {"Kolkata"}},
                {Lagos, {"Lagos"}},
                {Lima, {"Lima"}},
                {London, {"London"}},
                {LosAngeles, {"LosAngeles"}},
                {Madrid, {"Madrid"}},
                {Manila, {"Manila"}},
                {MexicoCity, {"MexicoCity"}},
                {Miami, {"Miami"}},
                {Milan, {"Milan"}},
                {Montreal, {"Montreal"}},
                {Moscow, {"Moscow"}},
                {Mumbai, {"Mumbai"}},
                {NewYork, {"NewYork"}},
                {Osaka, {"Osaka"}},
                {Paris, {"Paris"}},
                {Riyadh, {"Riyadh"}},
                {SanFrancisco, {"SanFrancisco"}},
                {Santiago, {"Santiago"}},
                {SaoPaulo, {"SaoPaulo"}},
                {Seoul, {"Seoul"}},
                {Shanghai, {"Shanghai"}},
                {StPetersburg, {"StPetersburg"}},
                {Sydney, {"Sydney"}},
                {Taipei, {"Taipei"}},
                {Tehran, {"Tehran"}},
                {Tokyo, {"Tokyo"}},
                {Washington, {"Washington"}} };

    };
    
}