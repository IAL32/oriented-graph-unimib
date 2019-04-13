#include "user.h"

void user::init(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email) {
    _phoneNumber = phoneNumber;
    _name = name;
    _surname = surname;
    _gender = gender;
    _birthday = birthday;
    _password = password;
    _email = email;
}

user::user(void) : _phoneNumber(nullptr), _name(nullptr), _surname(nullptr), _gender(false), _password(nullptr), _email(nullptr) {}

user::~user(void) {
    _phoneNumber = nullptr;
    _name = nullptr;
    _surname = nullptr;
    _gender = false;
    _password = nullptr;
    _email = nullptr;
}

user::user(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email) : _phoneNumber(nullptr), _name(nullptr), _surname(nullptr), _gender(false), _password(nullptr), _email(nullptr) {
    init(phoneNumber, name, surname, gender, birthday, password, email);
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

std::string user::toString() const {
    return getPhoneNumber() + ","
            + getName() + ","
            + getSurname() + ","
            + (isMale() ? "m" : "f") + ","
            + getBirthday().toString("dd/MM/yyyy").toUtf8().constData() + ","
            + getEmail();
}

std::ostream& operator<<(std::ostream &os, const user &a) {
    return os << a.toString();
}
