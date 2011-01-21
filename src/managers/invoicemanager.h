#ifndef INVOICEMANAGER_H
#define INVOICEMANAGER_H

#include "models/invoice.h"

#include <QList>
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
     * Retourne les types de reglement disponibles
     */
    QList<ReglementType> getReglements(int uid);

    /**
     * Retourne les types de documents disponibles
     */
    QList<DocumentType> getTypes(int uid);

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
     * Enregistre les lignes d'une facture
     *
     * @param invoice Facture à enregistrer
     */
    void insertLines(Invoice &invoice);

    /**
     * Supprime les lignes d'une facture
     *
     * @param invoice Facture à vider
     */
    bool clearLines(const Invoice &invoice);

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
    bool insert(Invoice &invoice, int uid);

    /**
     * Réalise la mise à jour d'une facture
     *
     * @param Invoice La facture à mettre à jour
     * @param uid Identifiant du profil "possédant" la facture
     *
     * @return bool Succès de la mise à jour
     */
    bool update(Invoice &Invoice, int uid);

    /**
     * Effectue un bindValue() sur la query avec les champs.
     *
     * @param Invoice Facture à binder
     * @param query Query à laquelle lier la facture
     * @param uid Identifiant du profil "possédant" la facture
     */
    void bindInvoice(const Invoice &Invoice, QSqlQuery &query, int uid=-1);

    /**
     * Effectue un bindValue() sur la query avec les champs.
     *
     * @param invoice ID de la facture
     * @param line Ligne à binder
     * @param query Query à laquelle lier la ligne
     */
    void bindInvoiceLine(int invoice, const InvoiceLine &line, QSqlQuery &query);
};

#endif // INVOICEMANAGER_H
