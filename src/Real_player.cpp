#include "Real_player.hpp"
#include "Application.hpp"

Real_player::Real_player(Chessboard *chessboard, Checker_color checkers_color)
: Player(chessboard, checkers_color)
{
}

void Real_player::make_move()
{
    Vector_ll from = {0, 1};
    Vector_ll to = {-1, -1};

    bool first_enter = true;
    
    printf("> Please, enter your move.\n");

    Checker *to_eat = nullptr;
    find_eatable(to_eat);

    Checker *checker = find_checker(from);
    if (must_eat_)
    {
        while(must_eat_)
        {
            do
            {
                if (!first_enter) printf("> There is checker on your way. Please, enter another move.\n");
                
                bool find_first_enter = true;
                do
                {
                    if (!find_first_enter) printf("> Checker wasn't found. Please, enter another move.\n");
                    
                    parse_answer(from, to);

                    checker = find_checker(from);
                    find_first_enter = false;
                } while (!checker);

                first_enter = false;

                if (!checker->is_attackable() && must_eat_)
                {
                    printf("> You must eat enemy's checker. Please, enter anther move.\n");
                    continue;
                }

            } while (!Application::get_app()->get_game()->is_free(to));
        }
    }
    else
    {
        do
        {
            if (!first_enter) printf("> There is checker on your way. Please, enter another move.\n");
            
            bool find_first_enter = true;
            do
            {
                if (!find_first_enter) printf("> Checker wasn't found. Please, enter another move.\n");
                
                parse_answer(from, to);

                checker = find_checker(from);
                find_first_enter = false;
            } while (!checker);

            first_enter = false;

            if (checker && !checker->is_attackable() && must_eat_)
            {
                printf("> You must eat enemy's checker. Please, enter anther move.\n");
                continue;
            }

        } while (!Application::get_app()->get_game()->is_free(to));
    }

    checker->set_place(to);
    chessboard_->move_checker(from, to);
}

Checker *Real_player::find_checker(Vector_ll place)
{
    for (size_t i = 0; i < checkers_.size(); ++i)
    {
        // printf("checker %lu : %lld %lld\n", i, checkers_[i]->get_place().get_x(), checkers_[i]->get_place().get_y());
        if (checkers_[i]->get_place() == place)
        {
            return checkers_[i];
        }
    }

    return nullptr;
}

void Real_player::parse_answer(Vector_ll &from, Vector_ll &to)
{
    std::string answer1 = {};
    std::string answer2 = {};

    size_t x1 = 0;
    size_t y1 = 0;

    size_t x2 = 0;
    size_t y2 = 0;

    bool correct = true;

    do
    {   
        std::cin >> answer1;
        if (answer1.size() < 2)
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }
       
        if (!isalpha(answer1[0]))
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        if (!isdigit(answer1[1]))
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        y1 = answer1[0] - 'a';
        if (y1 > 7)
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        x1 = answer1[1] - '1';
        if (x1 > 7)
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        std::cin >> answer2;

        if (!isalpha(answer2[0]))
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        if (!isdigit(answer2[1]))
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        y2 = answer2[0] - 'a';
        if (y2 > 7)
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        x2 = answer2[1] - '1';
        if (x2 > 7)
        {
            correct = false;
            printf("> Move is incorrect. Please, enter another one.\n");
            continue;
        }

        correct = true;
    } while (!correct);

    from = Vector_ll(x1, y1);
    to = Vector_ll(x2, y2);
}
