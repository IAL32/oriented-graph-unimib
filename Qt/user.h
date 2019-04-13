#ifndef USER_H
#define USER_H

#include <iostream>
#include <QDate>

class EmailFormatNotValid {};

class DateNotValid {};

class user {

private:

    std::string _phoneNumber;
    std::string _name;
    std::string _surname;
    bool _gender;
    QDate _birthday;
    std::string _password;
    std::string _email;

    void init(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email);

public:

    user();

    ~user();

    explicit user(std::string phoneNumber, std::string name, std::string surname, bool gender, QDate birthday, std::string password, std::string email);

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

    user fromString(std::string);
    std::string toString(void) const;
};

#endif // USER_H
