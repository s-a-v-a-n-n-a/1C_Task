#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdlib>
#include <vector>

// class Game;

// #include "Game.hpp"
#include "Checker.hpp"
#include "Chessboard.hpp"

enum class Player_game_state
{
    WIN,
    DRAW,
    LOSE,
    PLAYING
};

class Player
{
protected:
    // Game *current_game_;
    Chessboard *chessboard_;
    
    std::vector<Checker*> checkers_;

    const Checker_color checkers_color_;
    size_t checkers_amount_;

    Player_game_state state_;

    bool must_eat_;

public:
    Player() = delete;
    Player(Chessboard *chessboard, Checker_color checkers_color);
    void add_checker(Checker *checker) { checkers_.push_back(checker); }

    size_t get_checkers_amount() { return checkers_amount_; }

    void checker_lost();

    // bool is_present_eatable() { Checker *checker = nullptr; current_game_->check_eatable(checkers_color_, checker); return must_eat_; }

    virtual void make_move();
    virtual Checker *find_eatable(Checker *to_eat);
    virtual bool eat();
    virtual void move_any_checker();

    void reset_checkers_eat_state();
    void go_throw_checkers();

    Checker_color get_color() { return checkers_color_; }
    Player_game_state get_game_state() { return state_; }

    void set_game_state(Player_game_state state) { state_ = state; }
};

#endif // PLAYER_HPP
