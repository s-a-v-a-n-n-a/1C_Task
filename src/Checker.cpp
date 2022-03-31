#include "Checker.hpp"

Checker::Checker(Vector_ll place, Checker_color color, State state)
: place_(place), color_(color), state_(state), can_attack_(false), attack_amount_(0)
{
}

