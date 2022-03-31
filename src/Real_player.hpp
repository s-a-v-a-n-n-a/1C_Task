#ifndef REAL_PLAYER_HPP
#define REAL_PLAYER_HPP

#include <string>

#include "Player.hpp"

class Real_player : public Player
{
public:
    Real_player() = delete;
    Real_player(Chessboard *chessboard, Checker_color checkers_color);

    void make_move() override;
    // Checker *find_eatable(Checker *to_eat) override;
    // bool eat() override;
    // void move_any_checker() override;

    Checker *find_checker(Vector_ll place);

    void parse_answer(Vector_ll &from, Vector_ll &to);
    void check_answer(Vector_ll place);
};

#endif // REAL_PLAYER_HPP
