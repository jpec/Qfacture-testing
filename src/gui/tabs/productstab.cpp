#include "productstab.h"

#include <QHash>


ProductsTab::ProductsTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();

    this->loadProducts();

    onDBConnectionStateChanged();
}

ProductsTab::~ProductsTab()
{
    delete btn_new;
    delete btn_save;
    delete btn_del;

    delete products_table;
    delete w_product_edit;

    delete products_layout;
    delete edit_product_layout;
    delete actions_layout;
    delete form_layout;
    delete layout;

    delete gbox_actions;
    delete gbox_products;
    delete gbox_products_form;
}

void ProductsTab::buildLayout()
{
    QHash<QString, QString> columns;

    // définition des colonnes du tableau
    columns["Name"] = trUtf8("Nom");
    columns["Price"] = trUtf8("Prix");
    columns["Comment"] = trUtf8("Description");

    // construction des layouts
    layout = new QVBoxLayout(this);
    edit_product_layout = new QHBoxLayout();
    products_layout = new QHBoxLayout();
    form_layout = new QHBoxLayout();
    actions_layout = new QVBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_products = new QGroupBox(trUtf8("Liste des produits"), this);
    gbox_products_form = new QGroupBox(trUtf8("Client"));
    w_product_edit = new ProductWidget(core->getProductController());
    btn_new = new QPushButton(trUtf8("Nouveau"));
    btn_save = new QPushButton(trUtf8("Enregistrer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));

    // désactivation des boutons et widgets inutiles (pour le moment)
    w_product_edit->setEnabled(false);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);

    // création du tableau de produits
    products_table = new SQLTable("article");

    products_table->setColumns(columns);

    // liaisons des layouts avec les widgets
    products_layout->addWidget(products_table->getWidget());
    gbox_products->setLayout(products_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_save);
    actions_layout->addWidget(btn_del);
    gbox_actions->setLayout(actions_layout);

    edit_product_layout->addWidget(gbox_products_form);
    edit_product_layout->addWidget(gbox_actions);

    form_layout->addWidget(w_product_edit);
    gbox_products_form->setLayout(form_layout);

    layout->addWidget(gbox_products);
    layout->addLayout(edit_product_layout);

    setLayout(layout);
}

void ProductsTab::createActions()
{
    // pour (dés)activer l'onglet en fonction de l'état de la connexion à la DB
    this->connect(this->core->getDBController(), SIGNAL(DBConnected()), this,
                  SLOT(onDBConnectionStateChanged()));
    this->connect(this->core->getDBController(), SIGNAL(DBDisconnected()), this,
                  SLOT(onDBConnectionStateChanged()));

    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(this->core->getDBController(), SIGNAL(DBConnected()),
                  products_table, SLOT(feedTable()));

    // si SQLTable remonte une erreur SQL, on l'envoie à notre père
    this->connect(products_table, SIGNAL(DBError(QString)), parent(),
                  SLOT(onDBError(QString)));

    // vide le formulaire de saisie d'un produit lors du clic sur le bouton new
    this->connect(btn_new, SIGNAL(clicked()), w_product_edit,
                  SLOT(clearContent()));

    // lors du clic sur le bouton de création d'un new produit
    this->connect(btn_new, SIGNAL(clicked()), this, SLOT(onNewClicked()));
    // ou lors du chargement d'un produit
    this->connect(w_product_edit, SIGNAL(productLoaded()), this,
                  SLOT(onNewClicked()));

    // lors du clic sur le bouton de sauvegarde d'un new produit
    this->connect(btn_save, SIGNAL(clicked()), w_product_edit, SLOT(save()));

    // supprime le produit chargé, ou annule la création d'un nouveau produit
    this->connect(btn_del, SIGNAL(clicked()), w_product_edit, SLOT(erase()));
    this->connect(btn_del, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // rafraichit les données du tableau à l'enregistrement ou à la suppression d'un produit
    this->connect(w_product_edit, SIGNAL(productSaved()), products_table,
                  SLOT(feedTable()));
    this->connect(w_product_edit, SIGNAL(productDeleted(int)), products_table,
                  SLOT(feedTable()));

    // on réactive les boutons qu'il faut à la sauvegarde d'un produit
    this->connect(w_product_edit, SIGNAL(productSaved()), this,
                  SLOT(onDelClicked()));
    // et on vide le formulaire
    this->connect(w_product_edit, SIGNAL(productSaved()), w_product_edit,
                  SLOT(clearContent()));

    // charge le profil d'un produit lors du clic sur ce dernier dans le tableau
    this->connect(products_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(loadProduct(QTableWidgetItem*)));
}

void ProductsTab::onNewClicked()
{
    w_product_edit->setEnabled(true);

    btn_new->setEnabled(false);
    btn_save->setEnabled(true);
    btn_del->setEnabled(true);
}

void ProductsTab::onDelClicked()
{
    w_product_edit->setEnabled(false);

    btn_new->setEnabled(true);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
}

void ProductsTab::loadProduct(QTableWidgetItem *item)
{
    w_product_edit->loadProduct(item->data(Qt::UserRole).toInt());
}

void ProductsTab::loadProducts()
{
    if(!this->core->getDBController()->isDBConnected())
        return;
}

void ProductsTab::onDBConnectionStateChanged()
{
    bool connected = this->core->getDBController()->isDBConnected();

    gbox_actions->setEnabled(connected);
    gbox_products->setEnabled(connected);
    gbox_products_form->setEnabled(connected);
}
