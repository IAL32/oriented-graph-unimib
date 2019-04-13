#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include <iostream>
#include <list>
#include <algorithm>

class UsernameAlreadyRegisteredException {};

class EmailAlreadyRegisteredException {};

class PasswordNotCorrectException {};

class UserNotFoundException {};

class database {

private:
    std::list<user> _users;
    std::string _sourceFilename;

    void init(std::string );

public:

    database();

    ~database();

    database(const database &other);

    explicit database(std::list<user> users);

    explicit database(std::string sourceFilename);

    unsigned int getCount(void) const;

    std::list<user> getUsers(void) const;

    user getUser(unsigned int index);

    void addUser(user u);

    bool userExistsByPhoneNumber(std::string phoneNumber);

    bool userExistsByEmail(std::string email);

    bool userExistsByPhoneNumberPassword(std::string phoneNumber, std::string password);

    bool userExistsByEmailPassword(std::string email, std::string password);

    bool userExists(user u);

};

#endif // DATABASE_H
