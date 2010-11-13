#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include "controllers/customercontroller.h"

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>


/**
 * Formulaire permettant la saisie d'un client
 */
class CustomerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerWidget(CustomerController *ctrl, QWidget *parent = 0);
    ~CustomerWidget();

signals:
    /**
     * Émit lorsqu'un client a été sauvegardé
     */
    void customerSaved();

    /**
     * Émit lorsqu'un client a été chargé.
     */
    void customerLoaded();

    /**
     * Émit lorsqu'un client a été enregistré
     */
    void customerDeleted(int id);

public slots:
    /**
     * Vide le contenu du formulaire.
     */
    void clearContent();

    /**
     * Sauvegarde le profil actuellement chargé.
     */
    void save();

    /**
     * supprime le profil actuellement chargé.
     */
    void erase();

    /**
     * Charge le profil d'un client.
     *
     * @param id Identifiant du client
     */
    void loadCustomer(int id);

private:
    /**
     * Construit le layout du formulaire
     */
    void buildLayout();


    /**
     * Pointeur vers le contrôleur des profils.
     */
    CustomerController *ctrl_customer;

    /**
     * Layout permettant de créer facilement des formulaires
     */
    QFormLayout *layout;

    /**
     * Champ texte pour le nom du client
     */
    QLineEdit *c_name;

    /**
     * Champ texte pour l'adresse postale
     */
    QLineEdit *c_address;

    /**
     * Champ texte pour le complément d'adresse postale
     */
    QLineEdit *c_complement;

    /**
     * Champ texte pour le code postal
     */
    QLineEdit *c_zip;

    /**
     * Champ texte pour la ville
     */
    QLineEdit *c_city;

    /**
     * Champ texte pour le numéro de téléphone
     */
    QLineEdit *c_phone;

    /**
     * Champ texte pour le mail
     */
    QLineEdit *c_mail;

    /**
     * Client actuellement affiché
     */
    Customer customer;
};

#endif // CUSTOMERWIDGET_H
