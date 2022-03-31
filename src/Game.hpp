#ifndef GAME_HPP
#define GAME_HPP

#include <cstdlib>
#include <cmath>
#include <utility>
#include <new>

#include "Settings.hpp"

// class Real_player;
// class Bot;
// class Checker;
// class Cell;
// class Chessboard;

#include "Visualisation/sfml_drawing/screen_functions.hpp"

#include "Bot.hpp"
#include "Real_player.hpp"

#include "Checker.hpp"
#include "Cell.hpp"
#include "Chessboard.hpp"

extern const size_t DEFAULT_PLAYGROUND_SIZE;
extern const size_t DEFAULT_PLAYGROUND_SQUARE;

class Game
{
private:
    Chessboard chessboard_;
    
    Real_player person_;
    Bot bot_;
    
    Player *current_player_;
    Player *next_player_;

    // Cell *chessboard_;

    bool attackable_;

    Checker_color winner;

public:
    Game() = delete;
    Game(Checker_color& chosen_color);

    ~Game();

    void start();
    void make_move();
    void change_player();

    bool is_ended();

    // void set_current_player(Player& player);
    Vector_ll find_free(Checker *checker);
    bool is_free(Vector_ll place);

    Checker *check_eatable(Checker_color desired, Checker *to_eat);

    Checker *check_a1_h8(Checker_color desired, Checker *to_eat);
    Checker *check_g1_a7(Checker_color desired, Checker *to_eat);
    Checker *check_h2_b8(Checker_color desired, Checker *to_eat);
    Checker *check_c1_a3(Checker_color desired, Checker *to_eat);
    Checker *check_c1_h6(Checker_color desired, Checker *to_eat);
    Checker *check_h6_f8(Checker_color desired, Checker *to_eat);
    Checker *check_a3_f8(Checker_color desired, Checker *to_eat);
    Checker *check_a5_d8(Checker_color desired, Checker *to_eat);
    Checker *check_h4_d8(Checker_color desired, Checker *to_eat);
    Checker *check_e1_a5(Checker_color desired, Checker *to_eat);
    Checker *check_e1_h4(Checker_color desired, Checker *to_eat);

    Checker *check_left(Checker_color desired, Vector_ll low_limit, Vector_ll high_limit, Checker *to_eat);
    Checker *check_right(Checker_color desired, Vector_ll low_limit, Vector_ll high_limit, Checker *to_eat);

    Checker *check_simple_left(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);
    Checker *check_simple_right(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);
    Checker *check_queen_left_up(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);
    Checker *check_queen_left_down(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);
    Checker *check_queen_right_up(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);
    Checker *check_queen_right_down(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat);

    Checker_color get_other_color(Checker_color color);

    void draw(Screen_information *screen);
};

#endif // GAME_HPP
