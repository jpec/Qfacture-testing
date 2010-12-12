#ifndef INVOICE_H
#define INVOICE_H

#include <QString>


/**
 * Classe représentant une facture
 */
class Invoice
{
public:
    Invoice();

    /**
     * Définit l'identifiant de cette facture.
     *
     * \warning Ce n'est possible que s'il n'a pas déjà été défini.
     *
     * @param id L'identifiant à associer à la facture.
     */
    void setId(int id);

    /**
     * Retourne l'identiant de cette facture.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    int getId() const;

    /**
     * Définit la référence de la facture.
     *
     * @param Ref La nouvelle référence (ne doit pas être vide).
     */
    void setRef(const QString &Ref);

    /**
     * Retourne la référence.
     *
     * @return QString La référence.
     */
    QString getRef() const;

//    /**
//     * Définit le prix HT de ce produit.
//     *
//     * @param price Le prix du produit.
//     */
//    void setPrice(float price);
//
//    /**
//     * Retourne le prix de ce produit.
//     *
//     * @return float Le prix.
//     */
//    float getPrice() const;

    /**
     * Définit la description de la facture.
     *
     * @param Ref La nouvelle description.
     */
    void setDescription(const QString &description);

    /**
     * Retourne la description de la facture.
     *
     * @return QString La description.
     */
    QString getDescription() const;

private:
    /**
     * Identifiant de la facture.
     */
    int id;

    /**
     * Référence de la facture.
     */
    QString ref;

//    /**
//     * Prix du produit (HT, logique)
//     */
//    float price;

    /**
     * Brève description de la facture.
     */
    QString description;
};

#endif // INVOICE_H
