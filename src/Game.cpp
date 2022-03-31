#include "Game.hpp"

const size_t DEFAULT_PLAYGROUND_SIZE = 8;
const size_t DEFAULT_PLAYGROUND_SQUARE = 64;

Game::Game(Checker_color& chosen_color)
: chessboard_(), person_(&chessboard_, chosen_color), bot_(&chessboard_, (Checker_color)((chosen_color + 1) % 2))
{
    if (chosen_color == WHITE)
    {
        current_player_ = &person_;
        next_player_ = &bot_;
    }
    else
    {
        current_player_ = &bot_;
        next_player_ = &person_;
    }

    for (size_t i = 0; i < 3; ++i)
    {
        size_t start = i % 2 == 0 ? 0 : 1;
        for (size_t j = start; j < 8; j += 2)
        {
            Checker *white_checker = new Checker(Vector_ll(i, j), WHITE);
            
            chessboard_.set_checker(white_checker, Vector_ll(i, j));

            if (chosen_color == WHITE)
            {
                person_.add_checker(white_checker);
            }
            else
            {
                bot_.add_checker(white_checker);
            }
        }
    }

    for (size_t i = 5; i < 8; ++i)
    {
        size_t start = i % 2 == 0 ? 0 : 1; 
        for (size_t j = start; j < 8; j += 2)
        {
            // Player *owner = (chosen_color == BLACK) ? (Player*)&person_ : (Player*)&bot_;
            
            Checker *black_checker = new Checker(Vector_ll(i, j), BLACK);
            chessboard_.set_checker(black_checker, Vector_ll(i, j));

            if (chosen_color == BLACK)
            {
                person_.add_checker(black_checker);
            }
            else
            {
                bot_.add_checker(black_checker);
            }
        }
    }
}

Game::~Game()
{
    ;
}

void Game::start()
{
    ;

    // TODO: Print the winner
}

void Game::make_move()
{
    current_player_->make_move();
    change_player();
}

void Game::change_player()
{
    Player *tmp = std::move(current_player_);
    current_player_ = std::move(next_player_);
    next_player_ = std::move(tmp);
}

bool Game::is_ended()
{
    if (person_.get_game_state() == Player_game_state::LOSE)
    {
        bot_.set_game_state(Player_game_state::WIN);
        winner = bot_.get_color();
        return true;
    }

    if (bot_.get_game_state() == Player_game_state::LOSE)
    {
        person_.set_game_state(Player_game_state::WIN);
        winner = person_.get_color();
        return true;
    }

    return false;
}

Vector_ll Game::find_free(Checker *checker)
{
    Vector_ll place = checker->get_place();
    size_t x = place.get_x();
    size_t y = place.get_y();

    Checker_color color = checker->get_color();
    State state = checker->get_state();

    if (color == WHITE && state == State::SIMPLE)
    {
        if (x != 7 && y != 7 && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].no_checker_present())
            return Vector_ll(x + 1, y + 1);

        if (x != 7 && y != 0 && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].no_checker_present())
            return Vector_ll(x + 1, y - 1); 
    }
    else if (color == BLACK && state == State::SIMPLE)
    {
        if (x != 0 && y != 7 && chessboard_[(x - 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].no_checker_present())
            return Vector_ll(x - 1, y + 1);

        if (x != 0 && y != 0 && chessboard_[(x - 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].no_checker_present())
            return Vector_ll(x - 1, y - 1); 
    }
    else
    {
        if (x != 7 && y != 7 && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].no_checker_present())
            return Vector_ll(x + 1, y + 1);

        if (x != 7 && y != 0 && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].no_checker_present())
            return Vector_ll(x + 1, y - 1);
        
        if (x != 0 && y != 7 && chessboard_[(x - 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].no_checker_present())
            return Vector_ll(x - 1, y + 1);

        if (x != 0 && y != 0 && chessboard_[(x - 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].no_checker_present())
            return Vector_ll(x - 1, y - 1); 
    }

    return Vector_ll(-1, -1);
}

bool Game::is_free(Vector_ll place)
{
    if (place.get_x() < 0 || place.get_y() < 0 || place.get_x() > 7 || place.get_y() > 7)
        return false;
    
    if (chessboard_[place.get_x() * DEFAULT_PLAYGROUND_SIZE + place.get_y()].no_checker_present())
        return true;

    return false;
}

Checker *Game::check_eatable(Checker_color desired, Checker *to_eat)
{
    Checker *result = nullptr;
    
    result = check_a1_h8(desired, to_eat);
    if (result) return result;
    result = check_g1_a7(desired, to_eat);
    if (result) return result;
    result = check_h2_b8(desired, to_eat);
    if (result) return result;
    result = check_c1_a3(desired, to_eat);
    if (result) return result;
    result = check_c1_h6(desired, to_eat);
    if (result) return result;
    result = check_h6_f8(desired, to_eat);
    if (result) return result;
    result = check_a3_f8(desired, to_eat);
    if (result) return result;
    result = check_a5_d8(desired, to_eat);
    if (result) return result;
    result = check_h4_d8(desired, to_eat);
    if (result) return result;
    result = check_e1_a5(desired, to_eat);
    if (result) return result;
    result = check_e1_h4(desired, to_eat);

    return result;
}

Checker *Game::check_a1_h8(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 0;

    // size_t x_limit = 7;
    // size_t y_limit = 7;

    return check_right(desired, Vector_ll(0, 0), Vector_ll(7, 7), to_eat);
}

Checker *Game::check_g1_a7(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 6;

    // size_t x_limit = 6;
    // size_t y_limit = 0;

    return check_left(desired, Vector_ll(0, 6), Vector_ll(6, 0), to_eat);
}

Checker *Game::check_h2_b8(Checker_color desired, Checker *to_eat)
{
    // size_t x = 1;
    // size_t y = 7;

    // size_t x_limit = 7;
    // size_t y_limit = 1;

    return check_left(desired, Vector_ll(1, 7), Vector_ll(7, 1), to_eat);
}

Checker *Game::check_c1_a3(Checker_color desired, Checker *to_eat) // Three
{
    return check_simple_left(desired, Vector_ll(0, 2), Vector_ll(2, 0), to_eat);
}

Checker *Game::check_c1_h6(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 2;

    // size_t x_limit = 5;
    // size_t y_limit = 7;
    
    return check_right(desired, Vector_ll(0, 2), Vector_ll(5, 7), to_eat);
}

Checker *Game::check_h6_f8(Checker_color desired, Checker *to_eat) // Three
{
    Checker *result = check_simple_left(desired, Vector_ll(5, 7), Vector_ll(7, 5), to_eat);
    return result;
}

Checker * Game::check_a3_f8(Checker_color desired, Checker *to_eat)
{
    // size_t x = 2;
    // size_t y = 0;

    // size_t x_limit = 7;
    // size_t y_limit = 5;

    return check_right(desired, Vector_ll(2, 0), Vector_ll(7, 5), to_eat);
}

Checker *Game::check_a5_d8(Checker_color desired, Checker *to_eat)
{
    // size_t x = 4;
    // size_t y = 0;

    // size_t x_limit = 7;
    // size_t y_limit = 3;

    return check_right(desired, Vector_ll(4, 0), Vector_ll(7, 3), to_eat);
}

Checker *Game::check_h4_d8(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 7;

    // size_t x_limit = 7;
    // size_t y_limit = 3;

    return check_left(desired, Vector_ll(0, 7), Vector_ll(7, 3), to_eat);
}

Checker * Game::check_e1_a5(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 4;

    // size_t x_limit = 4;
    // size_t y_limit = 0;
    
    return check_left(desired, Vector_ll(0, 4), Vector_ll(4, 0), to_eat);
}

Checker * Game::check_e1_h4(Checker_color desired, Checker *to_eat)
{
    // size_t x = 0;
    // size_t y = 4;

    // size_t x_limit = 3;
    // size_t y_limit = 7;
    
    return check_right(desired, Vector_ll(0, 4), Vector_ll(3, 7), to_eat);
}

Checker *Game::check_left(Checker_color desired, Vector_ll low_limit, Vector_ll high_limit, Checker *to_eat)
{
    size_t x = low_limit.get_x();
    size_t y = low_limit.get_y();

    size_t x_limit = high_limit.get_x();
    size_t y_limit = high_limit.get_y();

    size_t length = std::abs((long long)(x - x_limit)) - 1;
    
    Checker *result = nullptr;

    for (size_t i = 0; i < length; ++i)
    {
        if ((chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].is_checker_present(desired)))
        {
            State state = chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].get_checker()->get_state();
            if (state == State::SIMPLE)
            {
                result = check_simple_left(desired, Vector_ll(x + i, y - i), Vector_ll(x + 2 + i, y - 2 - i), to_eat);
                if (result) return result;
            }
            else if (state == State::QUEEN)
            {
                result = check_queen_right_down(desired, Vector_ll(x + i, y - i), Vector_ll(x, y), to_eat);
                if (result) return result;
                result = check_queen_left_up(desired, Vector_ll(x + i, y - i), Vector_ll(x_limit, y_limit), to_eat);
                if (result) return result;
            }
        }
    }

    return result;
}

Checker *Game::check_right(Checker_color desired, Vector_ll low_limit, Vector_ll high_limit, Checker *to_eat)
{
    size_t x = low_limit.get_x();
    size_t y = low_limit.get_y();

    size_t x_limit = high_limit.get_x();
    size_t y_limit = high_limit.get_y();

    size_t length = std::abs((long long)(x - x_limit)) - 1;
    
    Checker *result = nullptr;

    for (size_t i = 0; i < length; ++i)
    {
        if ((chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].is_checker_present(desired)))
        {
            State state = chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].get_checker()->get_state();
            if (state == State::SIMPLE)
            {
                result = check_simple_right(desired, Vector_ll(x + i, y + i), Vector_ll(x + 2 + i, y + 2 + i), to_eat);
                if (result) return result;
            }
            else if (state == State::QUEEN)
            {
                result = check_queen_right_up(desired, Vector_ll(x + i, y + i), Vector_ll(x_limit, y_limit), to_eat);
                if (result) return result;
                result = check_queen_left_down(desired, Vector_ll(x + i, y + i), Vector_ll(x, y), to_eat);
                if (result) return result;
            }
        }
    }

    return result;
}

Checker *Game::check_simple_right(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    long long x = from.get_x();
    long long y = from.get_y();
    
    if ((chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired)) 
        && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].is_checker_present(get_other_color(desired))
        && chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y + 2)].no_checker_present())
    {
        chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
        to_eat = chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].get_checker();
        return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
    }

    if ((chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y + 2)].is_checker_present(desired)) 
        && (chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].is_checker_present(get_other_color(desired)))
        && chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].no_checker_present())
    {
        chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y + 2)].get_checker()->set_attackable(true);
        to_eat = chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y + 1)].get_checker();
        return chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y + 2)].get_checker();
    }

    return nullptr;
}

Checker *Game::check_simple_left(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    long long x = from.get_x();
    long long y = from.get_y();
    
    if ((chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired)) 
        && chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].is_checker_present(get_other_color(desired))
        && chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y - 2)].no_checker_present())
    {
        chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
        to_eat = chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].get_checker();
        return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
    }

    if ((chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y - 2)].is_checker_present(desired)) 
        && (chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].is_checker_present(get_other_color(desired)))
        && chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].no_checker_present())
    {
        chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y - 2)].get_checker()->set_attackable(true);
        to_eat = chessboard_[(x + 1) * DEFAULT_PLAYGROUND_SIZE + (y - 1)].get_checker();
        return chessboard_[(x + 2) * DEFAULT_PLAYGROUND_SIZE + (y - 2)].get_checker();
    }

    return nullptr;
}

Checker *Game::check_queen_left_up(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    if (std::abs(to.get_y() - from.get_y()) == 2)
    {
        return check_simple_left(desired, from, to, to_eat);
    }
    
    long long x = from.get_x();
    long long y = from.get_y();

    Checker_color other = get_other_color(desired);
    
    if (chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired))
    {
        size_t iterations = to.get_x() - from.get_x() - 1;
        
        bool checkers_found = false;
        Checker *found = nullptr;
        // bool one_checker_om_way = false;
        for (size_t i = 1; i <= iterations; ++i)
        {
            if (chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].is_checker_present(other))
            {
                if (!checkers_found)
                {
                    checkers_found = true;
                    found = chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].get_checker();
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (checkers_found)
                {
                    chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
                    to_eat = found;
                    return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
                }
            }
        }
    }

    return check_queen_left_up(desired, Vector_ll(x + 1, y - 1), to, to_eat);
}

Checker *Game::check_queen_left_down(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    if (std::abs(from.get_y() - to.get_y()) == 2)
    {
        return check_simple_left(desired, to, from, to_eat);
    }
    
    long long x = from.get_x();
    long long y = from.get_y();

    Checker_color other = get_other_color(desired);
    
    if (chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired))
    {
        size_t iterations = std::abs(from.get_x() - to.get_x()) - 1;
        
        bool checkers_found = false;
        Checker *found = nullptr;
        // bool one_checker_om_way = false;
        for (size_t i = 1; i <= iterations; ++i)
        {
            if (chessboard_[(x - i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].is_checker_present(other))
            {
                if (!checkers_found)
                {
                    checkers_found = true;
                    found = chessboard_[(x - i) * DEFAULT_PLAYGROUND_SIZE + (y - i)].get_checker();
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (checkers_found)
                {
                    chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
                    to_eat = found;
                    return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
                }
            }
        }
    }

    return check_queen_left_up(desired, Vector_ll(x - 1, y - 1), to, to_eat);
}

Checker *Game::check_queen_right_up(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    if (std::abs(to.get_x() - from.get_x()) == 2)
    {
        return check_simple_left(desired, from, to, to_eat);
    }
    
    long long x = from.get_x();
    long long y = from.get_y();

    Checker_color other = get_other_color(desired);
    
    if (chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired))
    {
        size_t iterations = std::abs(to.get_x() - from.get_x()) - 1;
        
        bool checkers_found = false;
        Checker *found = nullptr;
        // bool one_checker_om_way = false;
        for (size_t i = 1; i <= iterations; ++i)
        {
            if (chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].is_checker_present(other))
            {
                if (!checkers_found)
                {
                    checkers_found = true;
                    found = chessboard_[(x + i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].get_checker();
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (checkers_found)
                {
                    chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
                    to_eat = found;
                    return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
                }
            }
        }
    }

    return check_queen_right_up(desired, Vector_ll(x + 1, y + 1), to, to_eat);
}

Checker *Game::check_queen_right_down(Checker_color desired, Vector_ll from, Vector_ll to, Checker *to_eat)
{
    if (std::abs(from.get_x() - to.get_x()) == 2)
    {
        return check_simple_left(desired, to, from, to_eat);
    }
    
    long long x = from.get_x();
    long long y = from.get_y();

    Checker_color other = get_other_color(desired);
    
    if (chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].is_checker_present(desired))
    {
        size_t iterations = std::abs(from.get_x() - to.get_x()) - 1;
        
        bool checkers_found = false;
        Checker *found = nullptr;
        // bool one_checker_om_way = false;
        for (size_t i = 1; i <= iterations; ++i)
        {
            if (chessboard_[(x - i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].is_checker_present(other))
            {
                if (!checkers_found)
                {
                    checkers_found = true;
                    found = chessboard_[(x - i) * DEFAULT_PLAYGROUND_SIZE + (y + i)].get_checker();
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (checkers_found)
                {
                    chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker()->set_attackable(true);
                    to_eat = found;
                    return chessboard_[x * DEFAULT_PLAYGROUND_SIZE + y].get_checker();
                }
            }
        }
    }

    return check_queen_right_up(desired, Vector_ll(x - 1, y + 1), to, to_eat);
}


Checker_color Game::get_other_color(Checker_color color)
{
    return (Checker_color)((color + 1) % 2);
}


void Game::draw(Screen_information *screen)
{
    chessboard_.draw(screen);
}
