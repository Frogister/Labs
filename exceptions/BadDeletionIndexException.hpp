#ifndef LAB1_BADDELETIONINDEXEXCEPTION_HPP
#define LAB1_BADDELETIONINDEXEXCEPTION_HPP

class BadDeletionIndexException : public exception
{
public:
    explicit BadDeletionIndexException(const char* error) : error(error) {}
    const char* what() const noexcept override
    {
        return error.c_str();
    }

private:
    string error;
};

#endif //LAB1_BADDELETIONINDEXEXCEPTION_HPP
