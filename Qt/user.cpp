#include "user.h"

user::user(void) : _username(nullptr), _password(nullptr), _email(nullptr) {}

user::~user(void) { _username = nullptr; _password = nullptr; _email = nullptr; }

user::user(std::string username, std::string password, std::string email) : _username(nullptr), _password(nullptr), _email(nullptr) {
    _username = username;
    _password = password;
    _email = email;
}

user& user::operator=(const user &other) {
    if (this != &other) {
        user tmp(other);
        tmp.swap(*this);
    }

    return *this;
}

std::string user::getUsername(void) const { return _username; }
void user::setUsername(std::string username) { _password = username; }

std::string user::getPassword(void) const {return _password; }
void user::setPassword(std::string password) { _password = password; }

std::string user::getEmail(void) const { return _email; }
void user::setEmail(std::string email) { _email = email; }

void user::swap(user &other) {
    std::swap(_username, other._username);
    std::swap(_password, other._password);
    std::swap(_email, other._email);
}
