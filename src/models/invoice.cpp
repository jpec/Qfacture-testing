#include "invoice.h"

#include <QDate>


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

void Invoice::setType(const DocumentType &type)
{
    this->type = type;
}

DocumentType Invoice::getType() const
{
    return this->type;
}

void Invoice::setDate(const QDate &date)
{
    this->date = date;
}

QDate Invoice::getDate() const
{
    return date;
}

void Invoice::setAmount(float amount)
{
    this->amount = amount;
}

float Invoice::getAmount() const
{
    return this->amount;
}

void Invoice::setDescription(const QString &description)
{
    this->description = description;
}

QString Invoice::getDescription() const
{
    return this->description;
}

void Invoice::setCustomer(const Customer &customer)
{
    if(customer.isNew())
        return;

    this->customer = customer;
}

Customer Invoice::getCustomer() const
{
    return customer;
}

void Invoice::setReglement(const ReglementType &reglement)
{
    this->reglement = reglement;
}

ReglementType Invoice::getReglement() const
{
    return this->reglement;
}
