#ifndef LAB1_ERRORSANDEXCEPTIONS_HPP
#define LAB1_ERRORSANDEXCEPTIONS_HPP

#include <exception>
#include <string>
using namespace std;

class NonViableNumber : public exception
{
public:
    explicit NonViableNumber(const char* error) : error(error) { this->error = error; }
    const char* errorMessage() { return error.c_str(); }

private:
    std::string error;
};

class NotNumber : public exception
{
public:
    explicit NotNumber(const char* error) : error(error) { this->error = error; }
    const char* errorMessage() { return error.c_str(); }

private:
    string error;
};

#endif //LAB1_ERRORSANDEXCEPTIONS_HPP

