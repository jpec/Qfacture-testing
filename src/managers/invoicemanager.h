#ifndef INVOICEMANAGER_H
#define INVOICEMANAGER_H

#include "models/invoice.h"

#include <QHash>
#include <QSqlQuery>
#include <QStringList>


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
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return Invoice La facture chargée.
     */
    Invoice get(int id, int uid=-1);

    /**
     * Retourne les types de documents disponibles
     */
    QStringList getTypes(int uid);

    /**
     * Retourne les types de reglement disponibles
     */
    QHash<int, QString> getReglements(int uid);

    /**
     * Enregistre ou met à jour le détail d'une facture.
     *
     * \note En cas d'une nouvelle facture, l'id est renseigné lors de l'enregistrement
     *
     * @param Invoice La facture à enregistrer
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Invoice &Invoice, int uid);

    /**
     * Supprime une facture.
     *
     * @param id La facture à supprimer
     *
     * @return bool Succès de la suppression
     */
    bool erase(int id, int uid=-1);

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
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Invoice &Invoice, int uid);

    /**
     * Réalise la mise à jour d'une facture
     *
     * @param Invoice La facture à mettre à jour
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Invoice &Invoice, int uid);

    /**
     * Effectue un bindValue() sur la query avec les champs.
     *
     * @param Invoice Client à binder
     * @param query Query à laquelle lier la facture
     * @param uid Identifiant du profil "possédant" la facture
     */
    void bindInvoice(const Invoice &Invoice, QSqlQuery &query, int uid=-1);
};

#endif // INVOICEMANAGER_H
