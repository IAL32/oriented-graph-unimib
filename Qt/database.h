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
    QString _sourceFilename;

    void init(QString sourceFilename);

public:

    database();

    database(const database &other);

    explicit database(QString sourceFilename);

    std::list<user> getUsers(void);

    void addUser(user u);

    user findUserByPhoneNumber(QString phoneNumber);

    user findUserByEmail(QString email);

    user findUserByPhoneNumberOrEmail(QString phoneNumberOrEmail);

    bool userExistsByPhoneNumber(const QString phoneNumber);

    bool userExistsByEmail(const QString email);

    bool userExistsByPhoneNumberPassword(const QString phoneNumber, const QString password);

    bool userExistsByEmailPassword(const QString email, const QString password);

    bool userExists(const user u) const;

    QString toString(void) const;

    void save(void);

    user login(QString phoneOrEmail, QString password);

};

#endif // DATABASE_H
