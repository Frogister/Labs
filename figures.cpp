#include "Figures/figures.hpp"
#include "exceptions/NotNumberException.hpp"

Figure::Figure(string name) : inputName(std::move(name)) {}

string Figure::name()
{
    return inputName;
}