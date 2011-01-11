#include "documenttype.h"

DocumentType::DocumentType() : id(0), name("")
{
}

void DocumentType::setId(int id)
{
    if(this->id != 0)
        return;

    if(id <= 0)
        return;

    this->id = id;
}

int DocumentType::getId() const
{
    return this->id;
}

void DocumentType::setName(const QString &name)
{
    if(name.isEmpty())
        return;

    this->name = name;
}

QString DocumentType::getName() const
{
    return this->name;
}
