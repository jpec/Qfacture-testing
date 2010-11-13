#ifndef QFACTURECORE_H
#define QFACTURECORE_H


#include "controllers/controller.h"
#include "controllers/dbcontroller.h"
#include "controllers/profilecontroller.h"
#include "controllers/customercontroller.h"
#include "controllers/productcontroller.h"

#include <QHash>
#include <QObject>
#include <QSettings>


/**
 * Fait office de contrôleur géant et sera utilisé par la GUI.
 */
class QfactureCore : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructeur du core. Il s'occupe pour le moment d'initialiser les
     * différents managers tels que celui qui assure la gestion des paramètres.
     */
    QfactureCore();


    /**
     * Retourne un pointeur vers le contrôleur demandé
     *
     * @param name Nom du contrôleur voulu
     *
     * @return Controller* Pointeur vers le contrôleur
     */
    Controller* getController(const QString &name) const;

    /**
     * Retourne un pointeur vers le contrôleur de base de données
     *
     * @return DBController* Le pointeur vers le contrôleur
     */
    DBController* getDBController();

    /**
     * Retourne un pointeur vers le contrôleur des profils
     *
     * @return ProfileController* Le pointeur vers le contrôleur
     */
    ProfileController* getProfileController();

    /**
     * Retourne un pointeur vers le contrôleur des clients
     *
     * @return CustomerController* Le pointeur vers le contrôleur
     */
    CustomerController* getCustomerController();

    /**
     * Retourne un pointeur vers le contrôleur des produits
     *
     * @return ProductController* Le pointeur vers le contrôleur
     */
    ProductController* getProductController();

    /**
     * Retourne le numéro de version du logiciel.
     *
     * \todo Déplacer la définition du n° ailleurs (fichier dédié ?).
     */
    QString version() const { return "1.0 alpha"; }

private:
    /**
     * Initialise les "sous-contrôleurs"
     */
    void createControllers();


    /**
     * Contiendra les différents "sous-contrôleurs"
     */
    QHash<QString, Controller*> controllers;
};

#endif // QFACTURECORE_H
