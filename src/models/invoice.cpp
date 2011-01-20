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

float Invoice::getAmount() const
{
    float total = 0;

    for(int i=0; i < lines.size(); ++i)
        total += lines.at(i).getAmount();

    return total;
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

int Invoice::getLinesCount() const
{
    return lines.count();
}

void Invoice::addLine(InvoiceLine line)
{
    if(lines.contains(line))
        return;

    lines.append(line);
}

void Invoice::removeLine(int i)
{
    lines.removeAt(i);
}

InvoiceLine& Invoice::getLine(int i)
{
    return lines[i];
}
