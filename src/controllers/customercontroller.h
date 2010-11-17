#ifndef CUSTOMERCONTROLLER_H
#define CUSTOMERCONTROLLER_H

#include "managers/customermanager.h"

#include <QObject>


/**
 * Contrôleur permettant de gérer les clients
 */
class CustomerController : public QObject
{
    Q_OBJECT

public:
    /**
     * Retourne une instance unique du contrôleur
     *
     * @return CustomerController* L'instance du contrôleur
     */
    static CustomerController* getInstance();

    /**
     * Enregistre ou met à jour un client.
     *
     * \note En cas d'un nouveau client, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le client à enregistrer
     */
    bool save(Customer &p);

    /**
     * Récupère un client
     *
     * @param id L'identifiant du client
     *
     * @return Customer Le client chargé.
     */
    Customer get(int id);

    /**
     * Supprime un client
     *
     * @param id L'identifiant du client
     */
    bool erase(int id);

signals:
    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     *
     * @param error Le message d'erreur retourné
     */
    void DBError(const QString &error);

private:
    CustomerController();
    CustomerController(const CustomerController&);
    CustomerController& operator =(const CustomerController&);

    /**
     * Instance du gestionnaire de clients
     */
    CustomerManager manager;
};

#endif // CUSTOMERCONTROLLER_H
