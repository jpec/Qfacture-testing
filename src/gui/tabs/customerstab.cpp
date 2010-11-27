#include "customerstab.h"
#include "controllers/dbcontroller.h"


CustomersTab::CustomersTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();

    this->loadCustomers();
}

CustomersTab::~CustomersTab()
{
    delete btn_new;
    delete btn_save;
    delete btn_del;
    delete btn_cancel;
    delete search;
    delete search_filters;

    delete customers_table;
    delete w_customer_edit;

    delete search_form_layout;
    delete customers_layout;
    delete edit_customer_layout;
    delete actions_layout;
    delete form_layout;
    delete layout;

    delete gbox_actions;
    delete gbox_customers;
    delete gbox_customers_form;

}

void CustomersTab::buildLayout()
{
    // définition des colonnes du tableau
    QStringList not_wanted = QStringList() << "id";

    columns = core->getDBColumns("client", not_wanted);
    labels = core->getDBLabels("client", not_wanted);

    // construction des layouts
    layout = new QVBoxLayout(this);
    edit_customer_layout = new QHBoxLayout();
    customers_layout = new QVBoxLayout();
    form_layout = new QHBoxLayout();
    actions_layout = new QVBoxLayout();
    search_form_layout = new QHBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_customers = new QGroupBox(trUtf8("Liste des clients"), this);
    gbox_customers_form = new QGroupBox(trUtf8("Client"));
    w_customer_edit = new CustomerWidget(core);
    btn_new = new QPushButton(trUtf8("Nouveau"));
    btn_save = new QPushButton(trUtf8("Enregistrer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));
    btn_cancel = new QPushButton(trUtf8("Annuler"));
    search = new QLineEdit();
    search_filters = new QComboBox();

    // définition des filtres de recherche disponibles
    search_filters->addItems(labels);

    // définition des raccourcis clavier pour les boutons
    btn_new->setShortcut(QKeySequence::New);
    btn_save->setShortcut(QKeySequence::Save);
    btn_cancel->setShortcut(QKeySequence::Undo);
    btn_del->setShortcut(QKeySequence::Delete);

    // désactivation des boutons et widgets inutiles (pour le moment)
    w_customer_edit->setEnabled(false);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
    btn_cancel->setEnabled(false);

    // création du tableau de clients
    customers_table = new SQLTable("client");

    customers_table->setColumns(columns, labels);

    // liaisons des layouts avec les widgets
    search_form_layout->addWidget(search_filters);
    search_form_layout->addWidget(search);

    customers_layout->addLayout(search_form_layout);
    customers_layout->addWidget(customers_table->getWidget());
    gbox_customers->setLayout(customers_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_save);
    actions_layout->addWidget(btn_del);
    actions_layout->addWidget(btn_cancel);
    gbox_actions->setLayout(actions_layout);

    edit_customer_layout->addWidget(gbox_customers_form);
    edit_customer_layout->addWidget(gbox_actions);

    form_layout->addWidget(w_customer_edit);
    gbox_customers_form->setLayout(form_layout);

    layout->addWidget(gbox_customers);
    layout->addLayout(edit_customer_layout);

    setLayout(layout);
}

void CustomersTab::createActions()
{
    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(loadCustomers()));

    // si SQLTable remonte une erreur SQL, on l'envoie à notre père
    this->connect(customers_table, SIGNAL(DBError(QString)), parent(),
                  SLOT(onDBError(QString)));

    // vide le formulaire de saisie d'un client lors du clic sur le bouton new
    this->connect(btn_new, SIGNAL(clicked()), w_customer_edit,
                  SLOT(clearContent()));

    // lors du clic sur le bouton de création d'un new client
    this->connect(btn_new, SIGNAL(clicked()), this, SLOT(onNewClicked()));
    // ou lors du chargement d'un client
    this->connect(w_customer_edit, SIGNAL(customerLoaded()), this,
                  SLOT(onNewClicked()));

    // lors du clic sur le bouton de sauvegarde d'un new client
    this->connect(btn_save, SIGNAL(clicked()), w_customer_edit, SLOT(save()));

    // supprime le client chargé, ou annule la création d'un nouveau client
    this->connect(btn_del, SIGNAL(clicked()), w_customer_edit, SLOT(erase()));
    this->connect(btn_del, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // rafraichit les données du tableau à l'enregistrement ou à la suppression
    // d'un client
    this->connect(w_customer_edit, SIGNAL(customerSaved()), this,
                  SLOT(loadCustomers()));
    this->connect(w_customer_edit, SIGNAL(customerDeleted(int)), this,
                  SLOT(loadCustomers()));

    // on réactive les boutons qu'il faut à la sauvegarde d'un client
    this->connect(w_customer_edit, SIGNAL(customerSaved()), this,
                  SLOT(onDelClicked()));
    // et on vide le formulaire
    this->connect(w_customer_edit, SIGNAL(customerSaved()), w_customer_edit,
                  SLOT(clearContent()));

    // charge le profil d'un client lors du clic sur ce dernier dans le tableau
    this->connect(customers_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(loadCustomer(QTableWidgetItem*)));

    // annule une saisie
    this->connect(btn_cancel, SIGNAL(clicked()), w_customer_edit,
                  SLOT(clearContent()));
    this->connect(btn_cancel, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // mise à jour des critères de recherche
    this->connect(search, SIGNAL(textChanged(QString)), this,
                  SLOT(onSearchFiltersChanged()));
    this->connect(search_filters, SIGNAL(currentIndexChanged(int)), this,
                  SLOT(onSearchFiltersChanged()));
}

void CustomersTab::onSearchFiltersChanged()
{
    customers_table->setLikeFilter(columns[search_filters->currentIndex()],
                                   QVariant(search->text()));
}

void CustomersTab::onNewClicked()
{
    w_customer_edit->setEnabled(true);
    w_customer_edit->setFocus();

    btn_new->setEnabled(false);
    btn_save->setEnabled(true);
    btn_del->setEnabled(true);
    btn_cancel->setEnabled(true);
}

void CustomersTab::onDelClicked()
{
    w_customer_edit->setEnabled(false);

    btn_new->setEnabled(true);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
    btn_cancel->setEnabled(false);
}

void CustomersTab::loadCustomer(QTableWidgetItem *item)
{
    w_customer_edit->loadCustomer(item->data(Qt::UserRole).toInt());
}

void CustomersTab::loadCustomers()
{
    if(!this->core->isDBConnected())
        return;

    customers_table->feedTable();
}

void CustomersTab::setEnabled(bool state)
{
    gbox_actions->setEnabled(state);
    gbox_customers->setEnabled(state);
    gbox_customers_form->setEnabled(state);
}
