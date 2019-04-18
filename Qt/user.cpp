#include "user.h"

QString user::DEFAULT_DATE_FORMAT = "dd/MM/yyyy";
QString user::PHONENUMBER_PATTERN = "^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$";
QString user::EMAIL_PATTERN = "^[0-9a-zA-Z_\\-\\.]+@[0-9a-zA-Z_\\-\\.]+\\.[0-9a-zA-Z]+$";

void user::init(QString phoneNumber, QString name, QString surname, Gender gender, QDate birthday, QString password, QString email, Role role) {
    setPhoneNumber(phoneNumber);
    setName(name);
    setSurname(surname);
    _gender = gender;
    setBirthday(birthday);
    setPassword(password);
    setEmail(email);
    _role = role;
}

user::user(void) {}

user::user(QString phoneNumber, QString name, QString surname, Gender gender, QDate birthday, QString password, QString email, Role role) {
    init(phoneNumber, name, surname, gender, birthday, password, email, role);
}

bool user::operator==(const user &other) const {
    if (!_email.isEmpty() && !other.getEmail().isEmpty())
        return _email.toLower() == other.getEmail().toLower();
    if (!_phoneNumber.isEmpty() && !other.getPhoneNumber().isEmpty())
        return _phoneNumber == other.getPhoneNumber();
    return false;
}

bool user::operator!=(const user &other) const {
    return !(*this == other);
}

QString user::getPhoneNumber() const { return _phoneNumber; }
void user::setPhoneNumber(QString phoneNumber) {
    if (!phoneNumber.isEmpty() && !isPhoneNumber(phoneNumber))
        throw PhoneNumberFormatNotValidException();
    _phoneNumber = phoneNumber;
}

QString user::getName() const { return _name; }
void user::setName(QString name) {
    if (!user::isStringValid(name))
        throw StringFormatNotValidException();
    _name = name;
}

QString user::getSurname() const { return _surname; }
void user::setSurname(QString surname) {
    if (!user::isStringValid(surname))
        throw StringFormatNotValidException();
    _surname = surname;
}

user::Gender user::getGender() {
    return _gender;
}
QString user::getGenderString() {
    return (isMale()) ? "m" : "f";
}
user::Gender user::getGenderFromString(QString gender) {
    return (gender == "m") ? user::Gender::MALE : user::Gender::FEMALE;
}
bool user::isMale() const { return _gender == Gender::MALE; }
bool user::isFemale() const { return _gender == Gender::FEMALE; }
void user::setGender(Gender gender) { _gender = gender; }

QDate user::getBirthday() const { return _birthday; }
void user::setBirthday(QDate birthday) {
    if (!birthday.isValid())
        throw DateNotValidException();
    _birthday = birthday;
}

void user::setBirthdayFromString(QString birthday) {
    QDate d = QDate::fromString(birthday, DEFAULT_DATE_FORMAT);
    setBirthday(d);
}

QString user::getPassword(void) const {return _password; }
void user::setPassword(QString password) {
    if (!user::isStringValid(password))
        throw StringFormatNotValidException();
    _password = password;
}

QString user::getEmail(void) const { return _email; }
void user::setEmail(QString email) {
    if (!email.isEmpty() && !isEmail(email))
        throw EmailFormatNotValidException();
    _email = email;
}

bool user::isPhoneNumber(QString phoneNumber) {
    return std::regex_match(phoneNumber.toStdString(), std::regex(PHONENUMBER_PATTERN.toStdString()));
}
bool user::isEmail(QString email) {
    return std::regex_match(email.toStdString(), std::regex(EMAIL_PATTERN.toStdString()));
}
bool user::isDateValid(QString date) {
    QDate qDate = QDate::fromString(date, DEFAULT_DATE_FORMAT);
    return isDateValid(qDate);
}
bool user::isDateValid(QDate date) {
    return date.isValid();
}

user::Role user::getRole() const { return _role; }
QString user::getRoleString() const {
    return (_role == Role::ADMIN) ? "Administrator" : "User";
};
void user::setRole(Role role) { _role = role; }
bool user::isAdmin() const { return _role == user::Role::ADMIN; }
bool user::isUser() const { return _role == user::Role::USER; }

bool user::isStringValid(QString str) {
    return !str.contains(',');
}

user user::fromString(QString csvUser) {
    std::istringstream input(csvUser.toStdString());
    int i = 0;
    QString
            phoneNumber,
            name,
            surname,
            password,
            email;
    Gender gender = Gender::MALE;
    QDate birthday;
    Role role = Role::USER;
    QString qValue;
    for (std::string value; getline(input, value, ','); i++) {
        qValue = QString::fromStdString(value);
        switch (i) {
        case Attr::PHONENUMBER: {
            if (!value.empty() && !user::isPhoneNumber(qValue))
                throw PhoneNumberFormatNotValidException();
            phoneNumber = qValue;
            break;
        }
        case Attr::NAME: {
            name = qValue;
            break;
        }
        case Attr::SURNAME: {
            surname = qValue;
            break;
        }
        case Attr::GENDER: {
            gender = user::getGenderFromString(qValue);
            break;
        }
        case Attr::BIRTHDAY: {
            if (value.empty())
                throw DateFormatNotValidException();
            QDate qDateBirthday = QDate::fromString(qValue, DEFAULT_DATE_FORMAT);

            if (!qDateBirthday.isValid())
                throw DateNotValidException();

            birthday = qDateBirthday;
            break;
        }
        case Attr::PASSWORD: {
            password = qValue;
            break;
        }
        case Attr::EMAIL: {
            if (!value.empty() && !user::isEmail(qValue))
                throw EmailFormatNotValidException();
            email = qValue;
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
QString user::toString() const {
    return _phoneNumber + ","
            + _name + ","
            + _surname + ","
            + (isMale() ? "m" : "f") + ","
            + _birthday.toString(DEFAULT_DATE_FORMAT).toUtf8() + ","
            + _password + ","
            + _email + ","
            + ((isAdmin()) ? "0" : "1");
}

std::ostream& operator<<(std::ostream &os, const user &a) {
    return os << a.toString().toStdString();
}
