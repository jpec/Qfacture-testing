#include "product.h"

Product::Product() : id(0), name(""), price(0.f), description("")
{
}

void Product::setId(int id)
{
    if(this->id != 0)
        return;

    if(id <= 0)
        return;

    this->id = id;
}

int Product::getId() const
{
    return this->id;
}

void Product::setName(const string &name)
{
    if(name.empty())
        return;

    this->name = name;
}

string Product::getName() const
{
    return this->name;
}

void Product::setPrice(float price)
{
    this->price = price;
}

float Product::getPrice() const
{
    return this->price;
}

void Product::setDescription(const string &description)
{
    this->description = description;
}

string Product::getDescription() const
{
    return this->description;
}
