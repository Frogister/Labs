#ifndef LAB1_NOTNUMBEREXCEPTION_HPP
#define LAB1_NOTNUMBEREXCEPTION_HPP

#define NOT_NUMBER "Not number"

class NotNumberException : public exception
{
public:
    explicit NotNumberException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_NOTNUMBEREXCEPTION_HPP
