#ifndef USER_H
#define USER_H

#include <sstream>
#include <iostream>
#include <QDate>

class StringFormatNotValidException {};

class PhoneNumberFormatNotValidException {};

class EmailFormatNotValidException {};

class DateNotValidException {};

class RoleFormatNotValidException {};

class user {

private:

    typedef enum {
        ADMIN = 0,
        USER = 1
    } Role;

    typedef enum {
        PHONENUMBER = 0,
        NAME = 1,
        SURNAME = 2,
        GENDER = 3,
        BIRTHDAY = 4,
        PASSWORD = 5,
        EMAIL = 6,
        ROLE = 7
    } Attr;

    std::string _phoneNumber;
    std::string _name;
    std::string _surname;
    bool _gender;
    QDate _birthday;
    std::string _password;
    std::string _email;
    Role _role;

    void init(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email, Role role);

public:

    static std::string DEFAULT_DATE_FORMAT;

    user();

    explicit user(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email, Role role);

    std::string getPhoneNumber(void) const;
    void setPhoneNumber(std::string phoneNumber);

    std::string getName(void) const;
    void setName(std::string name);

    std::string getSurname(void) const;
    void setSurname(std::string surname);

    bool isMale(void) const;
    bool isFemale(void) const;
    void setGender(bool gender);

    QDate getBirthday(void) const;
    void setBirthday(QDate birthday);
    void setBirthdayFromString(std::string birthday);

    std::string getPassword(void) const;
    void setPassword(std::string password);

    std::string getEmail(void) const;
    void setEmail(std::string email);

    static bool isPhoneNumber(std::string phoneNumber);
    static bool isEmail(std::string email);

    Role getRole(void) const;
    void setRole(Role role);
    bool isAdmin(void) const;
    bool isUser(void) const;

    static user fromString(std::string csvUser);
    std::string toString(void) const;
};

#endif // USER_H
