#ifndef DBWIDGET_H
#define DBWIDGET_H

#include "controllers/dbcontroller.h"

#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>


class DBWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DBWidget(DBController *db_ctrl, QWidget *parent = 0);
    ~DBWidget();

    /**
     * Permet de désactiver le formulaire tout en gérant le bouton
     * de (dé)connexion
     */
    void setEnabled(bool enabled);

private slots:
    /**
     * Déclenche la (dé)connexion à la DB en fonction des informations
     * contenues dans les champs.
     */
    void handleDBConnection();

    /**
     * Appelée lorsque le type de DB est changé. Permet de cacher
     * certains champs lorsque SQLite est choisi.
     */
    void onCurrentDBTypeChanged(const QString &type);

private:
    /**
     * Construit le layout du formulaire
     */
    void buildLayout();

    /**
     * Crée les widgets du formulaire
     */
    void buildWidgets();

    /**
     * Initialise les connexion aux évènements
     */
    void createActions();

    /**
     * Sauvegarde les paramètres de connexion à la DB
     */
    void saveSettings();

    /**
     * Restaure les paramètres de connexion à la DB
     */
    void restoreSettings();


    /**
     * Pointeur vers le contrôleur de la base de données
     */
    DBController *db_ctrl;

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
     * Hôte de la base de données
     */
    QLineEdit *db_host;

    /**
     * Port de la base de données
     */
    QSpinBox *db_port;

    /**
     * Identifiant de connexion de la base de données
     */
    QLineEdit *db_login;

    /**
     * Mot de passe de la base de données
     */
    QLineEdit *db_pass;

    /**
     * Nom de la base de données
     */
    QLineEdit *db_base;

    /**
     * Type de la base de données
     */
    QComboBox *db_type;

    /**
     * Bouton de validation du formulaire
     */
    QPushButton *btn_ok;
};

#endif // DBWIDGET_H
