#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include "Cell.hpp"
#include "Checker.hpp"

#include "Visualisation/sfml_drawing/screen_functions.hpp"

class Chessboard
{
private:
    Cell *chessboard_;

public:
    Chessboard();
    ~Chessboard();

    void set_checker(Checker *checker, Vector_ll place);
    bool move_checker(Vector_ll from, Vector_ll to);

    Cell& operator [] (size_t index);

    void draw(Screen_information *screen);
};

#endif // CHESSBOARD_HPP
