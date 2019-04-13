#ifndef USER_H
#define USER_H

#include <iostream>

class user {

private:

    std::string _username;
    std::string _password;
    std::string _email;

    void init(std::string username, std::string password, std::string email);

public:

    user();

    ~user();

    explicit user(std::string username, std::string password, std::string email);

    user& operator=(const user &other);

    std::string getUsername(void) const;
    void setUsername(std::string username);

    std::string getPassword(void) const;
    void setPassword(std::string password);

    std::string getEmail(void) const;
    void setEmail(std::string email);

    void swap(user &other);
};

#endif // USER_H
