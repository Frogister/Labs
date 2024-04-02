#ifndef LAB1_BADDELETIONPERIMETEREXCEPTION_HPP
#define LAB1_BADDELETIONPERIMETEREXCEPTION_HPP

#define BAD_DELETION_PERIMETER_EXCEPTION "Perimeter with this value can not exist"

class BadDeletionPerimeterException : public exception
{
public:
    explicit BadDeletionPerimeterException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_BADDELETIONPERIMETEREXCEPTION_HPP
