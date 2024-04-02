#ifndef LAB1_NONVIABLENUMBEREXCEPTION_HPP
#define LAB1_NONVIABLENUMBEREXCEPTION_HPP

#define NON_VIABLE_NUMBER "Non viable number"

class NonViableNumberException : public exception
{
public:
    explicit NonViableNumberException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_NONVIABLENUMBEREXCEPTION_HPP
