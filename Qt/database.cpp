#include <database.h>

database::database(void) : _users(0) {  }

database::~database(void) {
    _sourceFilename = nullptr;
}

database::database(std::string sourceFilename) {
    _sourceFilename = sourceFilename;
}

database::database(std::list<user> users) {
    _users = users;
}

void database::addUser(user u) {
    if (userExists(u))
        throw UsernameAlreadyRegisteredException();
    _users.push_back(u);
}

bool database::userExists(user u) {
    std::list<user>::const_iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; ++i) {
        if (u.getPhoneNumber() == i->getPhoneNumber())
            return true;
        if (u.getEmail() == i->getEmail())
            return true;
    }
    return false;
}
