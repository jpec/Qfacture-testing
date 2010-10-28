#include "template.h"

Template::Template() : id(0), name(""), type(UNKNOWN)
{
}


int Template::getId() const
{
    return this->id;
}

void Template::setName(const string &name)
{
    if(name.empty())
        return;

    this->name = name;
}

string Template::getName() const
{
    return this->name;
}

void Template::setType(Type type)
{
    this->type = type;
}

Template::Type Template::getType() const
{
    return this->type;
}

void Template::setContent(const string &content)
{
    if(content.empty())
        return;
    
    this->content = content;
}

string Template::getContent() const
{
    return this->content;
}
