#ifndef LAB1_EMPTYLISTEXCEPTION_HPP
#define LAB1_EMPTYLISTEXCEPTION_HPP

#define EMPTY_LIST "The list of figures is empty"

class EmptyListException : public exception
{
public:
    explicit EmptyListException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_EMPTYLISTEXCEPTION_HPP
