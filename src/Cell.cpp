#include "Cell.hpp"

Cell::Cell(Vector_ll place)
: place_(place), 
  color_(place.get_x() + place.get_y() % 2 == 0 ? BLACK : WHITE), 
  checker_(nullptr)
{
}

Cell::Cell(Vector_ll place, Checker_color color)
: place_(place),
  color_(color),
  checker_(nullptr)
{
}
