#include "person.h"


Person::Person() : id(0), name(""), address(""), zip_code(""), city(""), mail(""), phone("")
{

}

void Person::setId(int id)
{
    if(this->id != 0)
        return;

    if(id <= 0)
        return;

    this->id = id;
}

int Person::getId() const
{
    return this->id;
}

void Person::setName(const QString &name)
{
    if(name.isEmpty())
        return;

    this->name = name;
}

QString Person::getName() const
{
    return this->name;
}

void Person::setAddress(const QString &address)
{
    this->address = address;
}

QString Person::getAddress() const
{
    return this->address;
}

void Person::setZipCode(const QString &zip)
{
    this->zip_code = zip;
}

QString Person::getZipCode() const
{
    return this->zip_code;
}

void Person::setCity(const QString &city)
{
    this->city = city;
}

QString Person::getCity() const
{
    return this->city;
}

void Person::setMail(const QString &mail)
{
    this->mail = mail;
}

QString Person::getMail() const
{
    return this->mail;
}

void Person::setPhone(const QString &phone)
{
    QString p = phone;
    p.replace(' ', "");

    if(!p.isEmpty() && strspn(p.toStdString().c_str(), "0123456789") != p.toStdString().size())
        return;

    this->phone = p;
}

QString Person::getPhone() const
{
    return this->phone;
}
