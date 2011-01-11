#ifndef INVOICECONTROLLER_H
#define INVOICECONTROLLER_H

#include "managers/invoicemanager.h"


/**
 * Contrôleur permettant de gérer les factures
 */
class InvoiceController
{
    friend class QfactureCore;

private:
    /**
     * Retourne une instance unique du contrôleur
     *
     * @return InvoiceController* L'instance du contrôleur
     */
    static InvoiceController* getInstance();

    /**
     * Enregistre ou met à jour une facture.
     *
     * \note En cas d'une nouvelle facture, l'id est renseigné lors de l'enregistrement
     *
     * @param i La facture à enregistrer
     * @param uid Identifiant du profil "possédant" la facture
     */
    bool save(Invoice &i, int uid);

    /**
     * Récupère une facture
     *
     * @param id L'identifiant de la facture
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return Invoice La facture chargée.
     */
    Invoice get(int id, int uid);

    /**
     * Retourne les types de reglement disponibles
     */
    QHash<int, QString> getReglements(int uid);

    /**
     * Retourne les types de documents disponibles
     */
    QHash<int, QString> getTypes(int uid);

    /**
     * Supprime une facture
     *
     * @param id L'identifiant de la facture
     * @param uid Identifiant du profil "possédant" la facture
     */
    bool erase(int id, int uid);


    InvoiceController();
    InvoiceController(const InvoiceController&);
    InvoiceController& operator =(const InvoiceController&);

    /**
     * Instance du gestionnaire de factures
     */
    InvoiceManager manager;
};

#endif // INVOICECONTROLLER_H
