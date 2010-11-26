#ifndef INVOICESTAB_H
#define INVOICESTAB_H

#include "qfacturecore.h"
#include "gui/widgets/sqltable.h"

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>

class InvoicesTab : public QWidget
{
    Q_OBJECT
public:
    explicit InvoicesTab(QfactureCore *core, QWidget *parent = 0);
    ~InvoicesTab();

public slots:
    /**
     * (Dés)active l'onglet
     *
     * @param state État d'activation de l'onglet
     */
    void setEnabled(bool state=true);

    /**
     * Recharge la liste des factures dans le tableau à partir de la
     * DB
     */
    void loadInvoices();

private slots:
    /**
     * (Dés)active les boutons qui vont bien lors du clic sur le bouton "nouvelle
     * facture"
     */
    void onNewClicked();

    /**
     * (Dés)active les boutons qui vont bien lors du clic sur le bouton "supprimer
     * facture"
     */
    void onDelClicked();

    /**
     * Appelé lorsque l'utilisateur clique sur le tableau. S'occupe de charger
     * les données de la facture dans le nouvel onglet
     *
     * @param item La ligne du tableau représentant la facture
     */
    void loadInvoice(QTableWidgetItem *item);

    /**
     * Appelé lorsque les critères de recherche ont changé
     */
    void onSearchFiltersChanged();

private:
    /**
     * Construit la GUI de l'onglet
     */
    void buildLayout();

    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void createActions();

    /**
     * Layout principal du widget
     */
    QVBoxLayout *layout;

    /**
     * Layout contenant le tableau des clients
     */
    QVBoxLayout *invoices_layout;

    /**
     * Groupbox servant de conteneur pour la liste des factures
     */
    QGroupBox *gbox_invoices;

    /**
     * Layout contenant le formulaire de recherche
     */
    QHBoxLayout *search_form_layout;

    /**
     * Layout contenant les boutons nouveau, sauvegarder et supprimer
     */
    QVBoxLayout *actions_layout;

    /**
     * Groupbox servant de conteneur pour la liste des actions
     */
    QGroupBox *gbox_actions;

    /**
     * Bouton "Nouvelle facture"
     */
    QPushButton *btn_new;

    /**
     * Bouton "Enregistrer facture"
     */
    QPushButton *btn_save;

    /**
     * Bouton "Supprimer facture"
     */
    QPushButton *btn_del;

    /**
     * Barre de recherche
     */
    QLineEdit *search;

    /**
     * Liste des filtres de recherches reconnus
     */
    QComboBox *search_filters;

    /**
     * Liste des colonnes de la table factures
     *
     * \todo n'a rien à faire ici
     */
    QList<QString> columns;

    /**
     * Liste des libellés des colonnes
     */
    QList<QString> labels;

    /**
     * Tableau des factures
     */
    SQLTable *invoices_table;

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;
};

#endif // INVOICESTAB_H
