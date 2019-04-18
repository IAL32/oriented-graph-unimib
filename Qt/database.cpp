#include <database.h>

void database::init(QString sourceFilename) {
    std::ifstream input(sourceFilename.toStdString());
    _sourceFilename = sourceFilename;

    if (!input.good() || input.peek() == std::ifstream::traits_type::eof()) {
        // file does not exists yet
        save();
    }

    QString qLine;
    for (std::string line; getline(input, line);) {
        qLine = QString::fromStdString(line);
        _users.push_back(user::fromString(qLine));
    }

    if (!userExistsByEmail("admin@pas.com"))
        throw AdminNotFoundInFileException();

    input.close();
}

database::database(void) : _users(0),  _sourceFilename("") {  }

database::database(QString sourceFilename) {
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

user database::findUserByPhoneNumber(QString phoneNumber) {
    if (!user::isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();
    std::list<user>::iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; i++)
        if (i->getPhoneNumber() == phoneNumber)
            return *i;
    throw UserNotFoundException();
}

user database::findUserByEmail(QString email) {
    email = email.toLower();
    if (!user::isEmail(email))
        throw EmailFormatNotValidException();
    std::list<user>::iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; i++)
        if (i->getEmail() == email)
            return *i;
    throw UserNotFoundException();
}

user database::findUserByPhoneNumberOrEmail(QString phoneNumberOrEmail) {
    if (user::isEmail(phoneNumberOrEmail))
        return findUserByEmail(phoneNumberOrEmail);
    else if (user::isPhoneNumber(phoneNumberOrEmail))
        return findUserByPhoneNumber(phoneNumberOrEmail);
    else throw StringFormatNotValidException();
}

bool database::userExistsByPhoneNumber(QString phoneNumber) {
    if (!user::isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();
    std::list<user>::const_iterator i, ie;

    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        if (i->getPhoneNumber() == phoneNumber)
            return true;
    return false;
}

bool database::userExistsByEmail(QString email) {
    if (!user::isEmail(email))
        throw EmailFormatNotValidException();
    std::list<user>::const_iterator i, ie;

    email = email.toLower();
    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        if (i->getEmail() == email)
            return true;
    return false;
}

bool database::userExists(const user u) const {
    std::list<user>::const_iterator i, ie;
    for (i = _users.begin(), ie = _users.end(); i != ie; ++i) {
        if (u == *i) return true;
    }
    return false;
}

QString database::toString() const {
    std::list<user>::const_iterator i, ie;
    QString acc = "";

    for (i = _users.begin(), ie = _users.end(); i != ie; ++i)
        acc += i->toString() + '\n';

    return acc;
}

void database::save() {
    std::ofstream output(_sourceFilename.toStdString());

    if (_users.size() == 0) {
        QDate today = QDate::currentDate();
        user admin("", "admin", "admin", user::Gender::FEMALE, today, "admin", "admin@pas.com", user::Role::ADMIN);

        _users.push_back(admin);
    }

    output << toString().toStdString();
    output.close();
}

user database::login(QString phoneOrEmail, QString password) {
    if (!user::isStringValid(password))
        throw StringFormatNotValidException();
    user u = findUserByPhoneNumberOrEmail(phoneOrEmail);
    if (u.getPassword() != password)
        throw CredentialsNotCorrectException();
    return u;
}
