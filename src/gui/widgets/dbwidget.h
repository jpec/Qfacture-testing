#ifndef DBWIDGET_H
#define DBWIDGET_H

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
    explicit DBWidget(QWidget *parent = 0);
    ~DBWidget();

    /**
     * Permet de définir les types de base de données
     * autorisés
     *
     * @param types Liste des types autorisés
     */
    void setDBAllowedTypes(const QStringList &types);

private:
    /**
     * Construit le layout du formulaire
     */
    void buildLayout();


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
