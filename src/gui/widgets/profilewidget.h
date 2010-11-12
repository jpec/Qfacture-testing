#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include "controllers/profilecontroller.h"

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>


/**
 * Crée un formulaire permettant la saisie d'un profile
 */
class ProfileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWidget(ProfileController *ctrl, QWidget *parent = 0);
    ~ProfileWidget();

public slots:
    /**
     * Vide le contenu du formulaire.
     */
    void clearContent();

    /**
     * Charge le dernier profil utilisateur
     */
    void loadLastProfile();

private slots:
    /**
     * Affiche dans le formulaire le profil actuellement chargé.
     */
    void displayCurrentProfile();

private:
    /**
     * Construit le layout du formulaire
     */
    void buildLayout();

    /**
     * Lie les actions aux évènements correspondants
     */
    void createActions();


    /**
     * Pointeur vers le contrôleur des profils.
     */
    ProfileController *ctrl_profile;

    /**
     * Layout permettant de créer facilement des formulaires
     */
    QFormLayout *form_layout;

    /**
     * Layout principal contenant le formulaire puis le
     * bouton valider en dessous.
     */
    QVBoxLayout *layout;

    /**
     * Champ texte pour le nom du profile
     */
    QLineEdit *p_name;

    /**
     * Champ texte pour le siret
     */
    QLineEdit *p_siret;

    /**
     * Champ texte pour l'adresse postale
     */
    QLineEdit *p_address;

    /**
     * Champ texte pour le code postal
     */
    QLineEdit *p_zip;

    /**
     * Champ texte pour la ville
     */
    QLineEdit *p_city;

    /**
     * Champ texte pour le numéro de téléphone
     */
    QLineEdit *p_phone;

    /**
     * Champ texte pour le mail
     */
    QLineEdit *p_mail;

    /**
     * Champ texte pour le site web
     */
    QLineEdit *p_website;

    /**
     * Bouton de validation du formulaire
     */
    QPushButton *btn_ok;
};

#endif // PROFILEWIDGET_H
