#include "Chessboard.hpp"

Chessboard::Chessboard()
{
    chessboard_ = (Cell*)(new unsigned char[64 * sizeof(Cell)]);
    for (size_t i = 0; i < 64; ++i)
    {
        new(chessboard_ + i * sizeof(Cell)) Cell(Vector_ll(i / 8, i % 8));
    }

    for (size_t i = 0; i < 64; ++i)
    {
        chessboard_[i].set_checker(nullptr);
    }
}

Chessboard::~Chessboard()
{
    for (size_t i = 0; i < 64; ++i)
        chessboard_[i].~Cell();
    
    delete chessboard_;
}

void Chessboard::set_checker(Checker *checker, Vector_ll place)
{
    chessboard_[place.get_x() * 8 + place.get_y()].set_checker(checker);
}

bool Chessboard::move_checker(Vector_ll from, Vector_ll to)
{
    if (chessboard_[from.get_x() * 8 + from.get_y()].no_checker_present())
        return false;

    if (!chessboard_[to.get_x() * 8 + to.get_y()].no_checker_present())
        return false;

    Checker *moved = chessboard_[from.get_x() * 8 + from.get_y()].get_checker();
    chessboard_[from.get_x() * 8 + from.get_y()].set_checker(nullptr);
    chessboard_[to.get_x() * 8 + to.get_y()].set_checker(moved);

    return true;
}

Cell& Chessboard::operator [] (size_t index)
{
    return chessboard_[index];
}

void Chessboard::draw(Screen_information *screen)
{
    screen->draw_rectangle(Vector_ll(0, 0), 800, 800, {255, 255, 255, 255}, {255, 255, 255, 255});

    for (size_t i = 0; i < 8; ++i)
    {
        for (size_t j = 0; j < 8; ++j)
        {
            if ((i + j) % 2 != 0)
            {
                screen->draw_rectangle(Vector_ll(j * 80, i * 80), 80, 80, {69, 40, 0, 255}, {69, 40, 0, 255});
            }
            else
            {
                screen->draw_rectangle(Vector_ll(j * 80, i * 80), 80, 80, {242, 211, 167, 255}, {242, 211, 167, 255});
            }

            if (chessboard_[i * 8 + j].is_checker_present(WHITE) && !chessboard_[i * 8 + j].no_checker_present() && chessboard_[i * 8 + j].get_checker()->get_state() == State::SIMPLE)
            {
                screen->draw_circle(Vector_ll(j * 80 + 2, i * 80 + 2), 38, {255, 255, 255, 255}, {255, 255, 255, 255});
            }
            else if (chessboard_[i * 8 + j].is_checker_present(WHITE) && !chessboard_[i * 8 + j].no_checker_present() && chessboard_[i * 8 + j].get_checker()->get_state() == State::QUEEN)
            {
                screen->draw_circle(Vector_ll(j * 80 + 2, i * 80 + 2), 38, {200, 200, 200, 255}, {200, 200, 200, 255});
            }
            else if (chessboard_[i * 8 + j].is_checker_present(BLACK) && !chessboard_[i * 8 + j].no_checker_present() && chessboard_[i * 8 + j].get_checker()->get_state() == State::SIMPLE)
            {
                screen->draw_circle(Vector_ll(j * 80 + 2, i * 80 + 2), 38, {0, 0, 0, 255}, {0, 0, 0, 255});
            }
            else if (chessboard_[i * 8 + j].is_checker_present(BLACK) && !chessboard_[i * 8 + j].no_checker_present() && chessboard_[i * 8 + j].get_checker()->get_state() == State::QUEEN)
            {
                screen->draw_circle(Vector_ll(j * 80 + 2, i * 80 + 2), 38, {100, 100, 100, 255}, {100, 100, 100, 255});
            }
        }
    }
}
