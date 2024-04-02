#ifndef LAB1_INTERFACECHOICEEXCEPTION_HPP
#define LAB1_INTERFACECHOICEEXCEPTION_HPP

#define INTERFACE_CHOICE_EXCEPTION "Non viable interface choice"

class InterfaceChoiceException : public exception
{
public:
    explicit InterfaceChoiceException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_INTERFACECHOICEEXCEPTION_HPP
