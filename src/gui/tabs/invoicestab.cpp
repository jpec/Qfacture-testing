#include "invoicestab.h"
#include "controllers/dbcontroller.h"

InvoicesTab::InvoicesTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();

    this->loadInvoices();
}

InvoicesTab::~InvoicesTab()
{
    delete btn_new;
    delete btn_save;
    delete btn_del;
    delete search;
    delete search_filters;

    delete invoices_table;

    delete search_form_layout;
    delete invoices_layout;
    delete actions_layout;
    delete layout;

    delete gbox_actions;
    delete gbox_invoices;
  //  delete gbox_customers_form;

}

void InvoicesTab::buildLayout()
{
    // définition des colonnes du tableau
    columns.append("Reference");
    labels.append(trUtf8("Référence"));
    columns.append("Date");
    labels.append(trUtf8("Date de facturation"));
    columns.append("Type");
    labels.append(trUtf8("Type"));
    columns.append("Client");
    labels.append(trUtf8("Client"));
    columns.append("Amount");
    labels.append(trUtf8("Montant"));
    columns.append("Date");
    labels.append(trUtf8("Date de paiement"));
    columns.append("Payment");
    labels.append(trUtf8("Mode de paiement"));
    columns.append("Comment");
    labels.append(trUtf8("Commentaire"));

    // construction des layouts
    layout = new QVBoxLayout(this);
    invoices_layout = new QVBoxLayout();
    actions_layout = new QVBoxLayout();
    search_form_layout = new QHBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_invoices = new QGroupBox(trUtf8("Liste des factures"), this);
    btn_new = new QPushButton(trUtf8("Nouvelle facture"));
    btn_save = new QPushButton(trUtf8("Enregistrer"));
    btn_del = new QPushButton(trUtf8("Supprimer la facture"));
    search = new QLineEdit();
    search_filters = new QComboBox();

    // définition des filtres de recherche disponibles
    search_filters->addItems(QStringList(labels));

    // définition des raccourcis clavier pour les boutons
    btn_new->setShortcut(QKeySequence(QKeySequence::New));
    btn_save->setShortcut(QKeySequence(QKeySequence::Save));
    btn_del->setShortcut(QKeySequence(QKeySequence::Delete));

    // désactivation des boutons et widgets inutiles (pour le moment)
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);

    // création du tableau des factures
    invoices_table = new SQLTable("facture");

    invoices_table->setColumns(columns, labels);

    // liaisons des layouts avec les widgets
    search_form_layout->addWidget(search_filters);
    search_form_layout->addWidget(search);

    invoices_layout->addLayout(search_form_layout);
    invoices_layout->addWidget(invoices_table->getWidget());
    gbox_invoices->setLayout(invoices_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_save);
    actions_layout->addWidget(btn_del);
    gbox_actions->setLayout(actions_layout);

    layout->addWidget(gbox_invoices);

    setLayout(layout);
}

void InvoicesTab::createActions()
{
    // pour (dés)activer l'onglet en fonction de l'état de la connexion à la DB
    this->connect(core, SIGNAL(DBConnected()), this,
                  SLOT(onDBConnectionStateChanged()));
    this->connect(core, SIGNAL(DBDisconnected()), this,
                  SLOT(onDBConnectionStateChanged()));

    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(core, SIGNAL(DBConnected()), invoices_table,
                  SLOT(feedTable()));

    // charge le profil d'un client lors du clic sur ce dernier dans le tableau
    this->connect(invoices_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(loadInvoice(QTableWidgetItem*)));

    // mise à jour des critères de recherche
    this->connect(search, SIGNAL(textChanged(QString)), this,
                  SLOT(onSearchFiltersChanged()));
    this->connect(search_filters, SIGNAL(currentIndexChanged(int)), this,
                  SLOT(onSearchFiltersChanged()));
}

void InvoicesTab::onSearchFiltersChanged()
{
    invoices_table->setLikeFilter(columns[search_filters->currentIndex()],
                                   QVariant(search->text()));
}

void InvoicesTab::onNewClicked()
{
    btn_new->setEnabled(false);
    btn_save->setEnabled(true);
    btn_del->setEnabled(true);
}

void InvoicesTab::onDelClicked()
{
    btn_new->setEnabled(true);
    btn_save->setEnabled(false);
    btn_del->setEnabled(false);
}

void InvoicesTab::loadInvoice(QTableWidgetItem *item)
{
    //w_customer_edit->loadCustomer(item->data(Qt::UserRole).toInt());
}

void InvoicesTab::loadInvoices()
{
    if(!core->isDBConnected())
        return;
}

void InvoicesTab::onDBConnectionStateChanged()
{
    bool connected = core->isDBConnected();

    gbox_actions->setEnabled(connected);
    gbox_invoices->setEnabled(connected);
}

