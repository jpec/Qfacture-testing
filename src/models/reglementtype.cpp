#include "reglementtype.h"

ReglementType::ReglementType() : id(0), name("")
{
}

void ReglementType::setId(int id)
{
    if(this->id != 0)
        return;

    if(id <= 0)
        return;

    this->id = id;
}

int ReglementType::getId() const
{
    return this->id;
}

void ReglementType::setName(const QString &name)
{
    if(name.isEmpty())
        return;

    this->name = name;
}

QString ReglementType::getName() const
{
    return this->name;
}
