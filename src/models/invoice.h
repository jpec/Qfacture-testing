#ifndef INVOICE_H
#define INVOICE_H

#include "models/customer.h"
#include "models/reglementtype.h"
#include "models/documenttype.h"

#include <QString>
#include <QDate>


/**
 * Classe représentant une facture
 */
class Invoice : public ModelBase
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

    /**
     * Définit le type du document.
     *
     * @param type Le nouveau type.
     */
    void setType(const DocumentType &type);

    /**
     * Retourne le type.
     *
     * @return DocumentType Le type.
     */
    DocumentType getType() const;

    /**
     * Définit la date d'établissement de la facture.
     *
     * @param date La nouvelle date.
     */
    void setDate(const QDate &date);

    /**
     * Retourne la date d'établissement de la facture
     *
     * @return QDate La Date.
     */
    QDate getDate() const;

    /**
     * Définit le montant de la facture.
     *
     * @param price Le montant de la facture.
     */
    void setAmount(float price);

    /**
     * Retourne le montant de la facture.
     *
     * @return float Le montant de la facture.
     */
    float getAmount() const;

    /**
     * Définit la description de la facture.
     *
     * @param description La nouvelle description.
     */
    void setDescription(const QString &description);

    /**
     * Retourne la description de la facture.
     *
     * @return QString La description.
     */
    QString getDescription() const;

    /**
     * Le mode de règlement de la facture.
     *
     * @param reglement Le mode de règlement
     */
    void setReglement(const ReglementType &reglement);

    /**
     * Retourne le mode de règlement de la facture.
     *
     * @return QString Le mode de règlement.
     */
    ReglementType getReglement() const;

    /**
     * Définit le client auquel est liée la facture
     *
     * @param customer Le nouveau client.
     */
    void setCustomer(const Customer &customer);

    /**
     * Retourne le client auquel est liée la facture.
     *
     * @return Customer Le client.
     */
    Customer getCustomer() const;

private:
    /**
     * Identifiant de la facture.
     */
    int id;

    /**
     * Référence de la facture.
     */
    QString ref;

    /**
     * Le montant de la facture
     */
    float amount;

    /**
     * La date d'établissement de la facture
     */
    QDate date;

    /**
     * Brève description de la facture.
     */
    QString description;

    /**
     * Type de la facture
     */
    DocumentType type;

    /**
     * Type de règlement de la facture
     */
    ReglementType reglement;

    /**
     * Client
     */
    Customer customer;
};

#endif // INVOICE_H
