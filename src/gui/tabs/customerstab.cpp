#include "customerstab.h"

#include <QHash>


CustomersTab::CustomersTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();

    this->loadCustomers();

    onDBConnectionStateChanged();
}

CustomersTab::~CustomersTab()
{
    delete btn_new;
    delete btn_save;
    delete btn_del;

    delete customers_table;
    delete w_customer_edit;

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
    QHash<QString, QString> columns;

    // définition des colonnes du tableau
    columns["Name"] = trUtf8("Nom");
    columns["Adress"] = trUtf8("Adresse");
    columns["Adress2"] = trUtf8("Complément");
    columns["Zip"] = trUtf8("Code postal");
    columns["City"] = trUtf8("Ville");
    columns["Phone"] = trUtf8("Téléphone");
    columns["Mail"] = trUtf8("Mail");

    // construction des layouts
    layout = new QVBoxLayout(this);
    edit_customer_layout = new QHBoxLayout();
    customers_layout = new QHBoxLayout();
    form_layout = new QHBoxLayout();
    actions_layout = new QVBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_customers = new QGroupBox(trUtf8("Liste des clients"), this);
    gbox_customers_form = new QGroupBox(trUtf8("Client"));
    w_customer_edit = new CustomerWidget(core->getCustomerController());
    btn_new = new QPushButton(trUtf8("Nouveau"));
    btn_save = new QPushButton(trUtf8("Enregistrer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));

    // désactivation des boutons et widgets inutiles (pour le moment)
    w_customer_edit->setEnabled(false);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);

    // création du tableau de clients
    customers_table = new SQLTable("client");

    customers_table->setColumns(columns);

    // liaisons des layouts avec les widgets
    customers_layout->addWidget(customers_table->getWidget());
    gbox_customers->setLayout(customers_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_save);
    actions_layout->addWidget(btn_del);
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
    // pour (dés)activer l'onglet en fonction de l'état de la connexion à la DB
    this->connect(this->core->getDBController(), SIGNAL(DBConnected()), this,
                  SLOT(onDBConnectionStateChanged()));
    this->connect(this->core->getDBController(), SIGNAL(DBDisconnected()), this,
                  SLOT(onDBConnectionStateChanged()));

    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(this->core->getDBController(), SIGNAL(DBConnected()),
                  customers_table, SLOT(feedTable()));

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

    // rafraichit les données du tableau à l'enregistrement ou à la suppression d'un client
    this->connect(w_customer_edit, SIGNAL(customerSaved()), customers_table,
                  SLOT(feedTable()));
    this->connect(w_customer_edit, SIGNAL(customerDeleted(int)), customers_table,
                  SLOT(feedTable()));

    // on réactive les boutons qu'il faut à la sauvegarde d'un client
    this->connect(w_customer_edit, SIGNAL(customerSaved()), this,
                  SLOT(onDelClicked()));
    // et on vide le formulaire
    this->connect(w_customer_edit, SIGNAL(customerSaved()), w_customer_edit,
                  SLOT(clearContent()));

    // charge le profil d'un client lors du clic sur ce dernier dans le tableau
    this->connect(customers_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(loadCustomer(QTableWidgetItem*)));
}

void CustomersTab::onNewClicked()
{
    w_customer_edit->setEnabled(true);

    btn_new->setEnabled(false);
    btn_save->setEnabled(true);
    btn_del->setEnabled(true);
}

void CustomersTab::onDelClicked()
{
    w_customer_edit->setEnabled(false);

    btn_new->setEnabled(true);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
}

void CustomersTab::loadCustomer(QTableWidgetItem *item)
{
    w_customer_edit->loadCustomer(item->data(Qt::UserRole).toInt());
}

void CustomersTab::loadCustomers()
{
    if(!this->core->getDBController()->isDBConnected())
        return;
}

void CustomersTab::onDBConnectionStateChanged()
{
    bool connected = this->core->getDBController()->isDBConnected();

    gbox_actions->setEnabled(connected);
    gbox_customers->setEnabled(connected);
    gbox_customers_form->setEnabled(connected);
}
