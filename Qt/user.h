#ifndef USER_H
#define USER_H

#include <sstream>
#include <iostream>
#include <QDate>
#include <regex>

class StringFormatNotValidException {};

class PhoneNumberFormatNotValidException {};

class EmailFormatNotValidException {};

class DateFormatNotValidException {};

class DateNotValidException {};

class RoleFormatNotValidException {};

class user {

public:
    typedef enum {
        ADMIN = 0,
        USER = 1
    } Role;

    typedef enum {
        MALE = 0,
        FEMALE = 1
    } Gender;

    typedef enum {
        PHONENUMBER = 0,
        NAME = 1,
        SURNAME = 2,
        GENDER = 3,
        BIRTHDAY = 4,
        PASSWORD = 5,
        EMAIL = 6,
        ROLE = 7,
        COUNT = 8
    } Attr;

private:

    QString _phoneNumber;
    QString _name;
    QString _surname;
    Gender _gender;
    QDate _birthday;
    QString _password;
    QString _email;
    Role _role;

    void init(QString phoneNumber, QString name, QString surname, Gender gender, QDate birthday, QString password, QString email, Role role);

public:

    static QString DEFAULT_DATE_FORMAT;
    static QString PHONENUMBER_PATTERN;
    static QString EMAIL_PATTERN;

    user();

    bool operator==(const user &other);

    bool operator!=(const user &other);

    explicit user(QString phoneNumber, QString name, QString surname, Gender gender, QDate birthday, QString password, QString email, Role role);

    QString getPhoneNumber(void) const;
    void setPhoneNumber(QString phoneNumber);

    QString getName(void) const;
    void setName(QString name);

    QString getSurname(void) const;
    void setSurname(QString surname);

    Gender getGender();
    QString getGenderString();
    static Gender getGenderFromString(QString gender);
    bool isMale(void) const;
    bool isFemale(void) const;
    void setGender(Gender gender);

    QDate getBirthday(void) const;
    void setBirthday(QDate birthday);
    void setBirthdayFromString(QString birthday);

    QString getPassword(void) const;
    void setPassword(QString password);

    QString getEmail(void) const;
    void setEmail(QString email);

    static bool isPhoneNumber(QString phoneNumber);
    static bool isEmail(QString email);
    static bool isDateValid(QString date);
    static bool isDateValid(QDate date);

    Role getRole(void) const;
    QString getRoleString(void) const;
    void setRole(Role role);
    bool isAdmin(void) const;
    bool isUser(void) const;

    static user fromString(QString csvUser);
    QString toString(void) const;
};

#endif // USER_H
