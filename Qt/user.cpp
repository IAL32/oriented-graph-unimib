#include "user.h"

std::string user::DEFAULT_DATE_FORMAT = "dd/MM/yyyy";
std::string user::PHONENUMBER_PATTERN = "^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$";
std::string user::EMAIL_PATTERN = "^[0-9a-zA-Z_\\-\\.]+@[0-9a-zA-Z_\\-\\.]+\\.[0-9a-zA-Z]+$";

void user::init(std::string phoneNumber, std::string name, std::string surname, Gender gender, QDate birthday, std::string password, std::string email, Role role) {
    _phoneNumber = phoneNumber;
    _name = name;
    _surname = surname;
    _gender = gender;
    _birthday = birthday;
    _password = password;
    _email = email;
    _role = role;
}

user::user(void) {}

user::user(std::string phoneNumber, std::string name, std::string surname, Gender gender, QDate birthday, std::string password, std::string email, Role role) {
    init(phoneNumber, name, surname, gender, birthday, password, email, role);
}

bool user::operator==(const user &other) {
    if (!_email.empty() && !_phoneNumber.empty() && !other.getEmail().empty() && !other.getPhoneNumber().empty())
        return _email == other.getEmail() || _phoneNumber == other.getPhoneNumber();
    return false;
}

bool user::operator!=(const user &other) {
    return !(*this == other);
}

std::string user::getPhoneNumber() const { return _phoneNumber; }
void user::setPhoneNumber(std::string phoneNumber) { _phoneNumber = phoneNumber; }

std::string user::getName() const { return _name; }
void user::setName(std::string name) { _name = name; }

std::string user::getSurname() const { return _surname; }
void user::setSurname(std::string surname) { _surname = surname; }

bool user::isMale() const { return _gender == Gender::MALE; }
bool user::isFemale() const { return _gender == Gender::FEMALE; }
void user::setGender(Gender gender) { _gender = gender; }

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

bool user::isPhoneNumber(std::string phoneNumber) {
    return std::regex_match(phoneNumber, std::regex(PHONENUMBER_PATTERN));
}
bool user::isEmail(std::string email) {
    return std::regex_match(email, std::regex(EMAIL_PATTERN));
}
bool user::isDateValid(std::string date) {
    QString qDateString = QString::fromStdString(date);
    QString qDEFAULT_DATE_FORMAT = QString::fromStdString(DEFAULT_DATE_FORMAT);
    QDate qDate = QDate::fromString(qDateString, qDEFAULT_DATE_FORMAT);
    return isDateValid(qDate);
}
bool user::isDateValid(QDate date) {
    return date.isValid();
}

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
    Gender gender = Gender::MALE;
    QDate birthday;
    Role role = Role::USER;
    for (std::string value; getline(input, value, ','); i++) {
        switch (i) {
        case Attr::PHONENUMBER: {
            if (!value.empty() && !user::isPhoneNumber(value))
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
            gender = (value == "f") ? Gender::FEMALE : Gender::MALE ;
            break;
        }
        case Attr::BIRTHDAY: {
            if (value.empty())
                throw DateFormatNotValidException();

            QString qbirthday = QString::fromStdString(value);
            QString qDEFAULT_DATE_FORMAT = QString::fromStdString(DEFAULT_DATE_FORMAT);
            QDate qDateBirthday = QDate::fromString(qbirthday, qDEFAULT_DATE_FORMAT);

            if (!qDateBirthday.isValid())
                throw DateNotValidException();

            birthday = qDateBirthday;
            break;
        }
        case Attr::PASSWORD: {
            password = value;
            break;
        }
        case Attr::EMAIL: {
            if (!value.empty() && !user::isEmail(value))
                throw EmailFormatNotValidException();
            email = value;
            break;
        }
        case Attr::ROLE: {
            int _role;
            std::istringstream iss(value);
            iss >> _role;
            if (_role < Role::ADMIN || _role > Role::USER)
                throw RoleFormatNotValidException();
            role = static_cast<Role>(_role);
            break;
        }
        default: {
            throw StringFormatNotValidException();
        }
        }
    }

    return user(phoneNumber, name, surname, gender, birthday, password, email, role);
}
std::string user::toString() const {
    QString qDEFAULT_DATE_FORMAT = QString::fromStdString(DEFAULT_DATE_FORMAT);
    return _phoneNumber + ","
            + _name + ","
            + _surname + ","
            + (isMale() ? "m" : "f") + ","
            + _birthday.toString(qDEFAULT_DATE_FORMAT).toUtf8().constData() + ","
            + _password + ","
            + _email + ","
            + ((isAdmin()) ? "0" : "1");
}

std::ostream& operator<<(std::ostream &os, const user &a) {
    return os << a.toString();
}
