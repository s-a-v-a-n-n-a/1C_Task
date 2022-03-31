#ifndef CELL_HPP
#define CELL_HPP

#include "Utils/Radius_vector.hpp"

#include "Checker.hpp"

class Cell
{
private:
    const Vector_ll place_;
    const Checker_color color_;

    Checker* checker_;

public:
    Cell() = delete;
    Cell(Vector_ll place);
    Cell(Vector_ll place, Checker_color color);

    Checker* get_checker() { return checker_; }

    void set_checker(Checker *checker) { checker_ = checker; }

    bool is_checker_present(Checker_color color) { if (!checker_) return false; return checker_->get_color() == color; }
    bool no_checker_present() { return (checker_ == nullptr); }
};

#endif // CELL_HPP
