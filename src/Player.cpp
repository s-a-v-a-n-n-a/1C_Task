#include "Player.hpp"
#include "Application.hpp"

Player::Player(Chessboard *chessboard, Checker_color checkers_color)
: chessboard_(chessboard),
  checkers_color_(checkers_color), 
  checkers_amount_(12), 
  state_(Player_game_state::PLAYING), 
  must_eat_(false)
{   
}

void Player::checker_lost()
{
    if (checkers_amount_ > 0)
        checkers_amount_ -= 1;

    if (checkers_amount_ == 0)
    {
        state_ = Player_game_state::LOSE;
    }
}

void Player::make_move()
{
    go_throw_checkers();
    
    if (!eat())
    {
        move_any_checker();
    }

    reset_checkers_eat_state();
}

void Player::go_throw_checkers()
{
    checkers_amount_ = 0;
    for (size_t i = 0; i < checkers_.size(); ++i)
    {
        if (checkers_[i]->get_state() != State::DEAD)
            checkers_amount_++;
    }
}

void Player::reset_checkers_eat_state()
{
    for (size_t i = 0; i < checkers_.size(); ++i)
    {
        checkers_[i]->set_attackable(false);
    }

    must_eat_ = false;
}

void Player::move_any_checker()
{
    for (size_t i = 0; i < checkers_.size(); ++i)
    {
        if (checkers_[i]->get_state() == State::DEAD)
        {
            continue;
        }
        
        Vector_ll free_place = Application::get_app()->get_game()->find_free(checkers_[i]);
        if (free_place.get_x() != -1 && free_place.get_y() != -1)
        {
            Vector_ll last_place = checkers_[i]->get_place();
            checkers_[i]->set_place(free_place);
            chessboard_->move_checker(last_place, free_place);

            printf("> Move was made: %c%lld %c%lld\n", last_place.get_y() + 'a', last_place.get_x() + 1, free_place.get_y() + 'a', free_place.get_x() + 1);
            break;
        }
    }
}

Checker *Player::find_eatable(Checker *to_eat)
{
    Checker *result = Application::get_app()->get_game()->check_eatable(checkers_color_, to_eat);
    if (result)
        must_eat_ = true;

    return result;
}

bool Player::eat()
{
    Checker *to_eat = nullptr;
    Checker *attacking = find_eatable(to_eat);

    bool attacked = false;
    bool first = true;
    
    while (attacking)
    {
        if (first)
        {
            attacked = true;
            first = false;
        }

        to_eat->set_state(State::DEAD);
        Vector_ll next_place = {0, 0};
        Vector_ll prey_place = to_eat->get_place();
        Vector_ll predator_place = attacking->get_place();
        
        if (prey_place.get_x() > predator_place.get_x())
        {
            if (prey_place.get_y() > predator_place.get_y())
            {
                next_place = prey_place + Vector_ll(1, 1);
            }
            else
            {
                next_place = prey_place + Vector_ll(1, -1);
            }
        }
        else
        {
            if (prey_place.get_y() > predator_place.get_y())
            {
                next_place = prey_place + Vector_ll(-1, 1);
            }
            else
            {
                next_place = prey_place + Vector_ll(-1, -1);
            }
        }

        attacking->set_place(next_place);

        reset_checkers_eat_state();

        Checker *to_eat = nullptr;
        Checker *attacking = find_eatable(to_eat);
    }

    return attacked;
}


