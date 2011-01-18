#ifndef INVOICELINE_H
#define INVOICELINE_H

#include <models/product.h>

class InvoiceLine;


class InvoiceLine : public Product
{
public:
    InvoiceLine();

    void setBaseProductId(int base_id);

    int getBaseProductId() const;

    void setQte(int qte);

    int getQte() const;

    void setOffPercentage(float off);

    float getOffPercentage() const;

    float getAmount() const;

    static InvoiceLine fromProduct(const Product &p);

    bool operator==(const InvoiceLine &l);

private:
    /**
     * Quantité de produit commandé
     */
    int qte;

    /**
     * Pourcentage de remise accordé
     */
    float off;

    int base_article_id;
};

#endif // INVOICELINE_H
