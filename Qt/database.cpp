#include <database.h>

void database::init(std::string sourceFilename) {
    std::ifstream input(sourceFilename);
    _sourceFilename = sourceFilename;

    if (!input.good() || input.peek() == std::ifstream::traits_type::eof()) {
        // file does not exists yet
        save();
    }

    for (std::string line; getline(input, line);) {
        _users.push_back(user::fromString(line));
    }

    if (!userExistsByEmail("admin@pas.com"))
        throw AdminNotFoundInFileException();

    input.close();
}

database::database(void) : _users(0),  _sourceFilename("") {  }

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
    save();
}

user database::findUserByPhoneNumber(std::string phoneNumber) {
    if (!user::isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();
    std::list<user>::iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; i++)
        if (i->getPhoneNumber() == phoneNumber)
            return *i;
    throw UserNotFoundException();
}

user database::findUserByEmail(std::string email) {
    if (!user::isEmail(email))
        throw EmailFormatNotValidException();
    std::list<user>::iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; i++)
        if (i->getEmail() == email)
            return *i;
    throw UserNotFoundException();
}

user database::findUserByPhoneNumberOrEmail(std::string phoneNumberOrEmail) {
    if (user::isEmail(phoneNumberOrEmail))
        return findUserByEmail(phoneNumberOrEmail);
    else if (user::isPhoneNumber(phoneNumberOrEmail))
        return findUserByPhoneNumber(phoneNumberOrEmail);
    else throw UserNotFoundException();
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
        if (!u.getPhoneNumber().empty() && i->getPhoneNumber().empty() && u.getPhoneNumber() == i->getPhoneNumber())
            return true;
        if (!u.getEmail().empty() && i->getEmail().empty() && u.getEmail() == i->getEmail())
            return true;
    }
    return false;
}

std::string database::toString() const {
    std::list<user>::const_iterator i, ie;
    std::string acc = "";

    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        acc += i->toString() + '\n';

    return acc;
}

void database::save() {
    std::ofstream output(_sourceFilename);

    if (_users.size() == 0) {
        QDate today = QDate::currentDate();
        user admin("", "admin", "admin", user::Gender::FEMALE, today, "admin", "admin@pas.com", user::Role::ADMIN);

        _users.push_back(admin);
    }

    output << toString();
    output.close();
}
