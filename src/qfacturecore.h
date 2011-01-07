#ifndef QFACTURECORE_H
#define QFACTURECORE_H

#include "controllers/profilecontroller.h"
#include "controllers/productcontroller.h"
#include "controllers/customercontroller.h"
#include "controllers/invoicecontroller.h"

#include <QObject>


/**
 * Fait office de wrapper pour tous les contrôleurs et sera le seul
 * utilisé par la GUI.
 */
class QfactureCore : public QObject
{
    Q_OBJECT

public:
    QfactureCore();

    /**
     * Retourne le numéro de version du logiciel.
     *
     * \todo Déplacer la définition du n° ailleurs (fichier dédié ?).
     */
    QString version() const { return "1.0 testing"; }


    /* Wrapper pour les méthodes du contrôleur de la DB */

    /**
     * @see DBController::getAvailableDrivers()
     */
    QStringList getAvailableDrivers() const;

    /**
     * @see DBController::connectDB()
     */
    void connectDB(const QString &server, int port, const QString &login,
                   const QString &pass, const QString &db_name, const QString &db_type="QMYSQL");

    /**
     * @see DBController::disconnectDB()
     */
    void disconnectDB();

    /**
     * @see DBController::isDBConnected()
     */
    bool isDBConnected() const;

    /**
     * @see DBController::getLabels()
     */
    QStringList getDBLabels(const QString& table, const QStringList& except) const;

    /**
     * @see DBController::getColumns()
     */
    QStringList getDBColumns(const QString& table, const QStringList& except) const;

    /**
     * @see DBController::getJoinClause()
     */
    QString getDBJoinClause(const QString &from, const QString &with) const;


    /* Wrapper pour les méthodes du contrôleur des profils */

    /**
     * @see ProfileController::loadLastProfile()
     */
    bool loadLastProfile();

    /**
     * @see ProfileController::getCurrent()
     */
    Profile& getCurrentProfile();

    /**
     * @see ProfileController::save()
     */
    bool save(Profile &p);

    /**
     * @see ProfileController::get()
     */
    Profile getProfile(int id);

    /**
     * @see ProfileController::saveCurrent()
     */
    bool saveCurrentProfile();


    /* Wrapper pour les méthodes du contrôleur des produits */

    /**
     * @see ProductController::save()
     */
    bool save(Product &p);

    /**
     * @see ProductController::get()
     */
    Product getProduct(int id);

    /**
     * @see ProductController::erase()
     */
    bool eraseProduct(int id);


    /* Wrapper pour les méthodes du contrôleur des clients */

    /**
     * @see ProductController::save()
     */
    bool save(Customer &p);

    /**
     * @see ProductController::get()
     */
    Customer getCustomer(int id);

    /**
     * @see CustomerController::getList()
     */
    QList<Customer> getCustomersList(const QString &name_filter="");

    /**
     * @see CustomerController::erase()
     */
    bool eraseCustomer(int id);

    /* Wrapper pour les méthodes du contrôleur des factures */

    /**
     * @see InvoiceController::get()
     */
    Invoice getInvoice(int id);

    /**
     * @see InvoiceController::getReglements()
     */
    QHash<int, QString> getReglements();

signals:

    /* Wrapper pour les signaux du contrôleur de la DB */

    /**
     * @see DBController::DBError()
     */
    void DBError(const QString &error);

    /**
     * @see DBController::DBConnected()
     */
    void DBConnected();

    /**
     * @see DBController::DBDisconnected()
     */
    void DBDisconnected();

    /**
     * @see DBController::DBConnectionError()
     */
    void DBConnectionError(const QString &error);


    /* Wrapper pour les signaux du contrôleur des profils */

    /**
     * Émit après la connexion à la DB, lorsque le profil de
     * l'utilisateur a été chargé.
     */
    void lastProfileLoaded();

private:
    /**
     * Initialise les signaux émis par le wrapper et ceux qu'il réémet (car
     * émis par d'autres contrôleurs)
     */
    void initSignals();
};

#endif // QFACTURECORE_H
