#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <cstdlib>

// class Player;

#include "Utils/Radius_vector.hpp"

// #include "Player.hpp"

#include "Settings.hpp"

class Checker
{
private:
    // Player *owner_;
    
    Vector_ll place_;

    Checker_color color_;

    State state_;
    bool can_attack_;
    size_t attack_amount_;

public:
    Checker() = delete;
    Checker(Vector_ll place, Checker_color color, State state = State::SIMPLE); // Player *owner, 
    
    void set_attackable(bool attackable) { can_attack_ = attackable; }
    void set_place(Vector_ll &place) 
    { 
        place_ = place; 
        if (color_ == WHITE && place.get_x() == 7 || color_ == BLACK && place.get_x() == 0) 
            set_state(State::QUEEN); 
    }
    void set_state(State state) { state_ = state; }

    bool is_attackable() { return can_attack_; }
    State get_state() { return state_; }
    Vector_ll get_place() { return place_; }
    Checker_color get_color() { return color_; }

    void die() { set_state(State::DEAD); }  
};

#endif // CHECKER_HPP
