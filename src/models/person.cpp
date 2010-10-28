#include "person.h"
#include <string.h>

using namespace std;


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

void Person::setName(const string &name)
{
    if(name.empty())
        return;

    this->name = name;
}

string Person::getName() const
{
    return this->name;
}

void Person::setAddress(const string &address)
{
    this->address = address;
}

string Person::getAddress() const
{
    return this->address;
}

void Person::setZipCode(const string &zip)
{
    this->zip_code = zip;
}

string Person::getZipCode() const
{
    return this->zip_code;
}

void Person::setCity(const string &city)
{
    this->city = city;
}

string Person::getCity() const
{
    return this->city;
}

void Person::setMail(const string &mail)
{
    this->mail = mail;
}

string Person::getMail() const
{
    return this->mail;
}

void Person::setPhone(const string &phone)
{
    if(!phone.empty() && strspn(phone.c_str(), "0123456789") != phone.size())
        return;
    
    this->phone = phone;
}

string Person::getPhone() const
{
    return this->phone;
}
