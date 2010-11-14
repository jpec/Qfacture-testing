#ifndef PRODUCTSTAB_H
#define PRODUCTSTAB_H

#include "qfacturecore.h"
#include "gui/widgets/sqltable.h"
#include "gui/widgets/productwidget.h"

#include <QList>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>


class ProductsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ProductsTab(QfactureCore *core, QWidget *parent = 0);
    ~ProductsTab();

public slots:
    /**
     * Appelé lorsque l'état de connexion à la DB change. Elle
     * s'occupe de (dés)activer certains widgets
     */
    void onDBConnectionStateChanged();

    /**
     * Recharge la liste des produits dans le tableau à partir de la
     * DB
     */
    void loadProducts();

private slots:
    /**
     * (Dés)active les boutons qui vont bien lors du clic sur le bouton "nouveau
     * produit"
     */
    void onNewClicked();

    /**
     * (Dés)active les boutons qui vont bien lors du clic sur le bouton "supprimer
     * produit"
     */
    void onDelClicked();

    /**
     * Appelé lorsque l'utilisateur clique sur le tableau. S'occupe de charger
     * les données du produit dans le formulaire d'édition
     *
     * @param item La ligne du tableau représentant le produit
     */
    void loadProduct(QTableWidgetItem *item);

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
     * Layout contenant le form d'édition d'un produit + les boutons
     * actions
     */
    QHBoxLayout *edit_product_layout;

    /**
     * Layout contenant le tableau des produits
     */
    QVBoxLayout *products_layout;

    /**
     * Layout contenant le formulaire de recherche
     */
    QHBoxLayout *search_form_layout;

    /**
     * Groupbox servant de conteneur pour la liste des produits
     */
    QGroupBox *gbox_products;

    /**
     * Layout contenant le formulaire d'édition d'un produit
     */
    QHBoxLayout *form_layout;

    /**
     * Layout contenant les boutons nouveau, sauvegarder et supprimer
     */
    QVBoxLayout *actions_layout;

    /**
     * Groupbox servant de conteneur pour le formulaire de création
     * d'un produit
     */
    QGroupBox *gbox_products_form;

    /**
     * Groupbox servant de conteneur pour la liste des actions
     */
    QGroupBox *gbox_actions;

    /**
     * Bouton "Nouveau produit"
     */
    QPushButton *btn_new;

    /**
     * Bouton "enregistrer produit"
     */
    QPushButton *btn_save;

    /**
     * Bouton "supprimer produit"
     */
    QPushButton *btn_del;

    /**
     * Bouton "annuler"
     */
    QPushButton *btn_cancel;

    /**
     * Barre de recherche
     */
    QLineEdit *search;

    /**
     * Liste des filtres de recherches reconnus
     */
    QComboBox *search_filters;

    /**
     * Liste des colonnes de la table client
     *
     * \todo n'a rien à faire ici
     */
    QList<QString> columns;

    /**
     * Liste des libellés des colonnes
     */
    QList<QString> labels;

    /**
     * Tableau des produits
     */
    SQLTable *products_table;

    /**
     * Formulaire permettant l'édition d'un produit
     */
    ProductWidget *w_product_edit;

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;
};

#endif // PRODUCTSTAB_H
