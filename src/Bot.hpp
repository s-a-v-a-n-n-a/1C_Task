#ifndef BOT_HPP
#define BOT_HPP

#include "Player.hpp"
#include "Chessboard.hpp"
#include "Checker.hpp"

enum Difficulty_level
{
    EASY,
    DIFFICULT
};

class Bot : public Player
{
private:
    Difficulty_level level_;

public:
    Bot() = delete;
    Bot(Chessboard *chessboard, Checker_color checkers_color, Difficulty_level level = EASY);
};

#endif // BOT_HPP
