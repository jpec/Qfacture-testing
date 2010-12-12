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
     */
    bool save(Invoice &i);

    /**
     * Récupère une facture
     *
     * @param id L'identifiant de la facture
     *
     * @return Invoice La facture chargée.
     */
    Invoice get(int id);

    /**
     * Supprime une facture
     *
     * @param id L'identifiant de la facture
     */
    bool erase(int id);


    InvoiceController();
    InvoiceController(const InvoiceController&);
    InvoiceController& operator =(const InvoiceController&);

    /**
     * Instance du gestionnaire de factures
     */
    InvoiceManager manager;
};

#endif // INVOICECONTROLLER_H
