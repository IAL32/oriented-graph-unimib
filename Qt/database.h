#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>

class AdminNotFoundInFileException {};

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

    user findUserByPhoneNumber(std::string phoneNumber);

    user findUserByEmail(std::string email);

    user findUserByPhoneNumberOrEmail(std::string phoneNumberOrEmail);

    bool userExistsByPhoneNumber(const std::string phoneNumber);

    bool userExistsByEmail(const std::string email);

    bool userExistsByPhoneNumberPassword(const std::string phoneNumber, const std::string password);

    bool userExistsByEmailPassword(const std::string email, const std::string password);

    bool userExists(const user u);

    std::string toString(void) const;

    void save(void);

};

#endif // DATABASE_H
