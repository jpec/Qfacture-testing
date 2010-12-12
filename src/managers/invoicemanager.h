#ifndef INVOICEMANAGER_H
#define INVOICEMANAGER_H

#include "models/invoice.h"

#include <QSqlQuery>

/**
 * Gestionnaire de factures
 */
class InvoiceManager
{
public:
    /**
     * Récupère le détail d'une facture
     *
     * @param id L'identifiant de la facture
     *
     * @throws DBErrorException Si la requête à la DB échoue
     *
     * @return Invoice La facture chargée.
     */
    Invoice get(int id);

    /**
     * Enregistre ou met à jour le détail d'une facture.
     *
     * \note En cas d'une nouvelle facture, l'id est renseigné lors de l'enregistrement
     *
     * @param p La facture à enregistrer
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Invoice &Invoice);

    /**
     * Supprime une facture.
     *
     * @param p La facture à supprimer
     *
     * @return bool Succès de la suppression
     */
    bool erase(int id);

private:
    /**
     * Créé une facture à partir des résultats d'une requête
     *
     * \note On suppose que tous les champs d'une facture sont
     *       retournés par la requête
     *
     * @param query La requête qui vient d'être exécutée
     *
     * @return Invoice La facture créé
     */
    Invoice makeInvoice(QSqlQuery &query);

    /**
     * Réalise l'enregistrement d'une nouvelle facture
     *
     * \note l'id est renseigné ici.
     *
     * @param Invoice La facture à enregistrer
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Invoice &Invoice);

    /**
     * Réalise la mise à jour d'une facture
     *
     * @param Invoice La facture à mettre à jour
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Invoice &Invoice);

    /**
     * Effectue un bindValue() sur la query avec les champs.
     *
     * @param Invoice Client à binder
     * @param query Query à laquelle lier le profile
     */
    void bindInvoice(const Invoice &Invoice, QSqlQuery &query);
};

#endif // INVOICEMANAGER_H
