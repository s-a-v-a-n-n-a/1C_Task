#include "Bot.hpp"

Bot::Bot(Chessboard *chessboard, Checker_color checkers_color, Difficulty_level level)
: Player(chessboard, checkers_color),
  level_(level)
{
}

