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

void Product::setName(const QString &name)
{
    if(name.isEmpty())
        return;

    this->name = name;
}

QString Product::getName() const
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

void Product::setDescription(const QString &description)
{
    this->description = description;
}

QString Product::getDescription() const
{
    return this->description;
}
