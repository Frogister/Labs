#ifndef LAB1_FIGURENONVIABLEEXCEPTION_HPP
#define LAB1_FIGURENONVIABLEEXCEPTION_HPP

#define FIGURE_NON_VIABLE "Figure with such parameters are non viable"

class FigureNonViableException : public exception
{
public:
    explicit FigureNonViableException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_FIGURENONVIABLEEXCEPTION_HPP
