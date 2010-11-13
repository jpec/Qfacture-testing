#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>


/**
 * Classe représentant un produit, un prestation.
 */
class Product
{
public:
    Product();

    /**
     * Définit l'identifiant de ce produit.
     *
     * \warning Ce n'est possible que s'il n'a pas déjà été défini.
     *
     * @param id L'identifiant à associer au produit.
     */
    void setId(int id);

    /**
     * Retourne l'identiant de ce produit.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    int getId() const;

    /**
     * Définit le nom de ce produit.
     *
     * @param name Le nouveau nom (ne doit pas être vide).
     */
    void setName(const QString &name);

    /**
     * Retourne le nom de ce produit.
     *
     * @return QString Le nom.
     */
    QString getName() const;

    /**
     * Définit le prix HT de ce produit.
     *
     * @param price Le prix du produit.
     */
    void setPrice(float price);

    /**
     * Retourne le prix de ce produit.
     *
     * @return float Le prix.
     */
    float getPrice() const;

    /**
     * Définit la description de ce produit.
     *
     * @param name La nouvelle description.
     */
    void setDescription(const QString &description);

    /**
     * Retourne la description de ce produit.
     *
     * @return QString La description.
     */
    QString getDescription() const;

private:
    /**
     * Identifiant du produit.
     */
    int id;

    /**
     * Nom du produit.
     */
    QString name;

    /**
     * Prix du produit (HT, logique)
     */
    float price;

    /**
     * Brève description du produit
     */
    QString description;
};

#endif // PRODUCT_H
