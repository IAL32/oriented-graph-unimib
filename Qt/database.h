#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>

class UserAlreadyRegisteredException {};

class CredentialsNotCorrectException {};

class UserNotFoundException {};

class database {

private:
    std::list<user> _users;
    std::string _sourceFilename;

    void init(std::string sourceFilename);

public:

    database();

    database(const database &other);

    explicit database(std::string sourceFilename);

    std::list<user> getUsers(void);

    void addUser(user u);

    user* findUserByPhoneNumber(std::string phoneNumber);

    bool userExistsByPhoneNumber(const std::string phoneNumber);

    bool userExistsByEmail(const std::string email);

    bool userExistsByPhoneNumberPassword(const std::string phoneNumber, const std::string password);

    bool userExistsByEmailPassword(const std::string email, const std::string password);

    bool userExists(const user u);

};

#endif // DATABASE_H
