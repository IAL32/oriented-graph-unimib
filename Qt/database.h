#ifndef DATABASE_H
#define DATABASE_H

#include "user.h"
#include <iostream>
#include <vector>

class UsernameAlreadyRegisteredException {};

class EmailAlreadyRegisteredException {};

class PasswordNotCorrectException {};

class UserNotFoundException {};

class database {

private:
    std::vector<user> users;


public:

    database();

    ~database();

    database(const database &other);

    database& operator=(const database &other);

    explicit database(unsigned int capacity);

    void swap(database &other);

    unsigned int getCount(void) const;

    const user &operator[](unsigned int index) const;

};

#endif // DATABASE_H
