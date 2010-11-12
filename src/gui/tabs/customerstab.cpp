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
    delete customers_table;

    delete customers_layout;
    delete edit_customer_layout;
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

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_customers = new QGroupBox(trUtf8("Liste des clients"), this);
    gbox_customers_form = new QGroupBox(trUtf8("Client"));

    // création du tableau de clients
    customers_table = new SQLTable("client");

    customers_table->setColumns(columns);

    // liaisons des layouts avec les widgets
    customers_layout->addWidget(customers_table->getWidget());
    gbox_customers->setLayout(customers_layout);

    edit_customer_layout->addWidget(gbox_customers_form);
    edit_customer_layout->addStretch();
    edit_customer_layout->addWidget(gbox_actions);

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
