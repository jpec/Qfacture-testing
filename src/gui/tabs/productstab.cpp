#include "productstab.h"


ProductsTab::ProductsTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();

    this->loadProducts();
}

ProductsTab::~ProductsTab()
{
    delete btn_new;
    delete btn_save;
    delete btn_del;
    delete btn_cancel;
    delete search;
    delete search_filters;

    delete products_table;
    delete w_product_edit;

    delete search_form_layout;
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
    // définition des colonnes du tableau
    columns.append("Name");
    labels.append(trUtf8("Nom"));
    columns.append("Price");
    labels.append(trUtf8("Prix"));
    columns.append("Comment");
    labels.append(trUtf8("Description"));

    // construction des layouts
    layout = new QVBoxLayout(this);
    edit_product_layout = new QHBoxLayout();
    products_layout = new QVBoxLayout();
    form_layout = new QHBoxLayout();
    actions_layout = new QVBoxLayout();
    search_form_layout = new QHBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_products = new QGroupBox(trUtf8("Liste des produits"), this);
    gbox_products_form = new QGroupBox(trUtf8("Client"));
    w_product_edit = new ProductWidget(this->core);
    btn_new = new QPushButton(trUtf8("Nouveau"));
    btn_save = new QPushButton(trUtf8("Enregistrer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));
    btn_cancel = new QPushButton(trUtf8("Annuler"));
    search = new QLineEdit();
    search_filters = new QComboBox();

    // définition des filtres de recherche disponibles
    search_filters->addItems(QStringList(labels));

    // définition des raccourcis clavier pour les boutons
    btn_new->setShortcut(QKeySequence(QKeySequence::New));
    btn_save->setShortcut(QKeySequence(QKeySequence::Save));
    btn_cancel->setShortcut(QKeySequence(QKeySequence::Undo));
    btn_del->setShortcut(QKeySequence(QKeySequence::Delete));

    // désactivation des boutons et widgets inutiles (pour le moment)
    w_product_edit->setEnabled(false);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
    btn_cancel->setEnabled(false);

    // création du tableau de produits
    products_table = new SQLTable("article");

    products_table->setColumns(columns, labels);

    // liaisons des layouts avec les widgets
    search_form_layout->addWidget(search_filters);
    search_form_layout->addWidget(search);

    products_layout->addLayout(search_form_layout);
    products_layout->addWidget(products_table->getWidget());
    gbox_products->setLayout(products_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_save);
    actions_layout->addWidget(btn_del);
    actions_layout->addWidget(btn_cancel);
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
    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(this->core, SIGNAL(DBConnected()), products_table,
                  SLOT(feedTable()));

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

    // annule une saisie
    this->connect(btn_cancel, SIGNAL(clicked()), w_product_edit, SLOT(clearContent()));
    this->connect(btn_cancel, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // mise à jour des critères de recherche
    this->connect(search, SIGNAL(textChanged(QString)), this,
                  SLOT(onSearchFiltersChanged()));
    this->connect(search_filters, SIGNAL(currentIndexChanged(int)), this,
                  SLOT(onSearchFiltersChanged()));
}

void ProductsTab::onSearchFiltersChanged()
{
    products_table->setLikeFilter(columns[search_filters->currentIndex()],
                                  QVariant(search->text()));
}

void ProductsTab::onNewClicked()
{
    w_product_edit->setEnabled(true);
    w_product_edit->setFocus();

    btn_new->setEnabled(false);
    btn_save->setEnabled(true);
    btn_del->setEnabled(true);
    btn_cancel->setEnabled(true);
}

void ProductsTab::onDelClicked()
{
    w_product_edit->setEnabled(false);

    btn_new->setEnabled(true);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
    btn_cancel->setEnabled(false);
}

void ProductsTab::loadProduct(QTableWidgetItem *item)
{
    w_product_edit->loadProduct(item->data(Qt::UserRole).toInt());
}

void ProductsTab::loadProducts()
{
    if(!this->core->isDBConnected())
        return;
}

void ProductsTab::setEnabled(bool state)
{
    gbox_actions->setEnabled(state);
    gbox_products->setEnabled(state);
    gbox_products_form->setEnabled(state);
}
