#include "invoiceline.h"

InvoiceLine::InvoiceLine() : base_article_id(0)
{
}

void InvoiceLine::setBaseProductId(int base_id)
{
    if(base_article_id != 0)
        return;

    this->base_article_id = base_id;
}

int InvoiceLine::getBaseProductId() const
{
    return this->base_article_id;
}

void InvoiceLine::setQte(int qte)
{
    if(qte < 1)
        qte = 1;

    this->qte = qte;
}

int InvoiceLine::getQte() const
{
    return qte;
}

void InvoiceLine::setOffPercentage(float off)
{
    if(off < 0)
        off = 0;

    if(off > 100)
        off = 100;

    this->off = off;
}

float InvoiceLine::getOffPercentage() const
{
    return off;
}

float InvoiceLine::getAmount() const
{
    return (qte * getPrice()) -  qte * getPrice() * off / 100.0;
}

InvoiceLine InvoiceLine::fromProduct(const Product &p)
{
    InvoiceLine line;

    line.setName(p.getName());
    line.setDescription(p.getDescription());
    line.setPrice(p.getPrice());
    line.setQte(1);
    line.setOffPercentage(0);
    line.setBaseProductId(p.getId());

    return line;
}

bool InvoiceLine::operator==(const InvoiceLine &l)
{
    return (getId() == l.getId() && getQte() == l.getQte() &&
            getName() == l.getName() && getDescription() == l.getDescription());
}
