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

signals:
    /**
     * Signal émis lorsque le widget courant souhaite ouvrir un nouvel onglet
     * dans l'appli
     */
    void newTabRequest(const QString& name, QWidget* content);

    void invoiceDeleted();
    void invoiceAdded();

public slots:
    /**
     * (Dés)active l'onglet
     *
     * @param state État d'activation de l'onglet
     */
    void setEnabled(bool state=true);

private slots:
    /**
     * Ouvre un onglet pour créer une facture
     */
    void onNewClicked();

    /**
     * (Dés)active les boutons qui vont bien lors du clic sur le bouton "supprimer
     * facture"
     */
    void onDelClicked();

    /**
     * Appelé lorsque l'utilisateur clique sur le bouton d'ouverture d'une facture.
     * S'occupe de charger les données de la facture sélectionnée dans le tableau
     * pour l'afficher dans un nouvel onglet
     */
    void loadSelectedInvoice();

    /**
     * Appelé lorsque les critères de recherche ont changé
     */
    void onSearchFiltersChanged();

    /**
     * Appelé lorsque la facture sélectionnée change.
     */
    void onSelectionChanged();

    /**
     * Charge la facture représentée par l'item du tableau
     *
     * @param item Ligne du tableau représentant la facture
     */
    void loadInvoice(QTableWidgetItem *item);

private:
    /**
     * Construit la GUI de l'onglet
     */
    void buildLayout();

    /**
     * Construit le tableau contenant la liste des factures
     *
     * @param columns Nom des colonnes du tableau
     * @param labels Libellés des colonnes
     */
    void buildInvoicesTableLayout(QStringList columns, QStringList labels);

    /**
     * Construit la barre de recherche
     *
     * @param filters Filtres disponibles pour la recherche
     */
    void buildSearchBar(QStringList filters);

    /**
     * Construit la barre d'action contenant les boutons
     */
    void buildActionButtons();

    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void createActions();

    /**
     * Charge une facture dans un nouvel onglet
     *
     * @param id Id de la facture
     */
    void loadInvoice(int id);


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
    QHBoxLayout *search_bar_layout;

    /**
     * Layout contenant les boutons nouveau, sauvegarder et supprimer
     */
    QHBoxLayout *actions_layout;

    /**
     * Groupbox servant de conteneur pour la liste des actions
     */
    QGroupBox *gbox_actions;

    /**
     * Bouton "Nouvelle facture"
     */
    QPushButton *btn_new;

    /**
     * Bouton "Ouvrir facture"
     */
    QPushButton *btn_open;

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
