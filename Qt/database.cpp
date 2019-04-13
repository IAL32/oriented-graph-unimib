#include <database.h>

void database::init(std::string sourceFilename) {
    std::ifstream input(sourceFilename);
    std::list<user> users;
    for (std::string line; getline(input, line);) {
        users.push_back(user::fromString(line));
    }
    input.close();

    _sourceFilename = sourceFilename;
    _users = users;
}

database::database(void) : _users(0), _sourceFilename(nullptr) {  }

database::database(std::string sourceFilename) {
    init(sourceFilename);
}

std::list<user> database::getUsers() {
    return _users;
}

void database::addUser(const user u) {
    if (userExists(u))
        throw UserAlreadyRegisteredException();
    _users.push_back(u);
}

user* database::findUserByPhoneNumber(std::string phoneNumber) {
    if (!user::isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();
    std::list<user>::iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; i++)
        if (i->getPhoneNumber() == phoneNumber)
            return &(*i);
    return nullptr;
}

bool database::userExistsByPhoneNumber(const std::string phoneNumber) {
    if (!user::isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();

    std::list<user>::const_iterator i, ie;

    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        if (i->getPhoneNumber() == phoneNumber)
            return true;
    return false;
}

bool database::userExistsByEmail(const std::string email) {
    if (!user::isEmail(email))
        throw EmailFormatNotValidException();

    std::list<user>::const_iterator i, ie;

    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        if (i->getEmail() == email)
            return true;
    return false;
}

bool database::userExists(const user u) {
    std::list<user>::const_iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; ++i) {
        if (u.getPhoneNumber() == i->getPhoneNumber())
            return true;
        if (u.getEmail() == i->getEmail())
            return true;
    }
    return false;
}
