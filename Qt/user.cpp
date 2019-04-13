#include "user.h"

std::string user::DEFAULT_DATE_FORMAT = "dd/MM/yyyy";

void user::init(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email, Role role) {
    _phoneNumber = phoneNumber;
    _name = name;
    _surname = surname;
    _gender = gender;
    _birthday = birthday;
    _password = password;
    _email = email;
    _role = role;
}

user::user(void) : _phoneNumber(nullptr), _name(nullptr), _surname(nullptr), _gender(false), _password(nullptr), _email(nullptr) {}

user::user(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email, Role role) : _phoneNumber(nullptr), _name(nullptr), _surname(nullptr), _gender(false), _password(nullptr), _email(nullptr) {
    init(phoneNumber, name, surname, gender, birthday, password, email, role);
}

std::string user::getPhoneNumber() const { return _phoneNumber; }
void user::setPhoneNumber(std::string phoneNumber) { _phoneNumber = phoneNumber; }

std::string user::getName() const { return _name; }
void user::setName(std::string name) { _name = name; }

std::string user::getSurname() const { return _surname; }
void user::setSurname(std::string surname) { _surname = surname; }

bool user::isMale() const { return _gender; }
bool user::isFemale() const { return !_gender; }
void user::setGender(bool gender) { _gender = gender; }

QDate user::getBirthday() const { return _birthday; }
void user::setBirthday(QDate birthday) {
    _birthday = birthday;
}

void user::setBirthdayFromString(std::string birthday) {
    QString qbirthday = QString::fromStdString(birthday);
    QDate d = QDate::fromString(qbirthday, "dd/MM/yyyy");
    setBirthday(d);
}

std::string user::getPassword(void) const {return _password; }
void user::setPassword(std::string password) { _password = password; }

std::string user::getEmail(void) const { return _email; }
void user::setEmail(std::string email) { _email = email; }

user::Role user::getRole() const { return _role; }
void user::setRole(Role role) { _role = role; }
bool user::isAdmin() const { return _role == user::Role::ADMIN; }
bool user::isUser() const { return _role == user::Role::USER; }

user user::fromString(std::string csvUser) {
    std::istringstream input(csvUser);
    int i = 0;
    std::string
            phoneNumber,
            name,
            surname,
            password,
            email;
    bool gender = false;
    QDate birthday;
    Role role = Role::USER;
    user u;
    for (std::string value; getline(input, value, ','); i++) {
        switch (i) {
        case Attr::PHONENUMBER: {
            if (!user::isPhoneNumber(value))
                throw PhoneNumberFormatNotValidException();
            phoneNumber = value;
            break;
        }
        case Attr::NAME: {
            name = value;
            break;
        }
        case Attr::SURNAME: {
            surname = value;
            break;
        }
        case Attr::GENDER: {
            gender = value == "f";
            break;
        }
        case Attr::BIRTHDAY: {
            QString qbirthday = QString::fromStdString(value);
            QString qDEFAULT_DATE_FORMAT = QString::fromStdString(DEFAULT_DATE_FORMAT);
            birthday = QDate::fromString(qbirthday, qDEFAULT_DATE_FORMAT);
            break;
        }
        case Attr::PASSWORD: {
            password = value;
            break;
        }
        case Attr::EMAIL: {
            if (!user::isPhoneNumber(value))
                throw PhoneNumberFormatNotValidException();
            email = value;
            break;
        }
        case Attr::ROLE: {
            int _role;
            std::istringstream iss(value);
            iss >> _role;
            if (!iss.good())
                throw RoleFormatNotValidException();
            if (_role < Role::ADMIN || _role > Role::ADMIN)
                throw RoleFormatNotValidException();
            role = static_cast<Role>(_role);
            break;
        }
        default: {
            throw StringFormatNotValidException();
        }
        }
    }
    u = user(phoneNumber, name, surname, gender, birthday, password, email, role);

    return u;
}
std::string user::toString() const {
    QString qDEFAULT_DATE_FORMAT = QString::fromStdString(DEFAULT_DATE_FORMAT);
    return getPhoneNumber() + ","
            + getName() + ","
            + getSurname() + ","
            + (isMale() ? "m" : "f") + ","
            + getBirthday().toString(qDEFAULT_DATE_FORMAT).toUtf8().constData() + ","
            + getEmail();
}

std::ostream& operator<<(std::ostream &os, const user &a) {
    return os << a.toString();
}
