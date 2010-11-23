#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H

#include "qfacturecore.h"

#include <QLabel>
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
    explicit ProfileWidget(QfactureCore *ctrl, QWidget *parent = 0);
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

    /**
     * Réalise le changement du logo du profil courant.
     * Ouvre une boite de dialogue permettant de choisir le logo,
     * met à jour le profil et affiche le logo choisi.
     */
    void changeLogo();

    /**
     * Sauvegarde le profil actuellement chargé.
     */
    void save();

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
     * Pointeur vers le contrôleur de l'application.
     */
    QfactureCore *ctrl;

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
     * Conteneur permettant d'afficher le logo
     */
    QLabel *p_logo;

    /**
     * Bouton de validation du formulaire
     */
    QPushButton *btn_logo;

    /**
     * Bouton de validation du formulaire
     */
    QPushButton *btn_ok;
};

#endif // PROFILEWIDGET_H
