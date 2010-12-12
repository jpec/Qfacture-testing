#include "invoice.h"

Invoice::Invoice() : id(0), ref(""), description("")
{
}

void Invoice::setId(int id)
{
    if(this->id != 0)
        return;

    if(id <= 0)
        return;

    this->id = id;
}

int Invoice::getId() const
{
    return this->id;
}

void Invoice::setRef(const QString &ref)
{
    if(ref.isEmpty())
        return;

    this->ref = ref;
}

QString Invoice::getRef() const
{
    return this->ref;
}

//void Invoice::setPrice(float price)
//{
//    this->price = price;
//}
//
//float Invoice::getPrice() const
//{
//    return this->price;
//}

void Invoice::setDescription(const QString &description)
{
    this->description = description;
}

QString Invoice::getDescription() const
{
    return this->description;
}
