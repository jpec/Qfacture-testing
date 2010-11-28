#include "invoicestab.h"
#include "utils/utils.h"
#include "gui/tabs/invoicetab.h"
#include "controllers/dbcontroller.h"

#include <QMessageBox>


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
    delete btn_open;
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

}

void InvoicesTab::buildLayout()
{
    // définition des colonnes du tableau
    QStringList not_wanted = QStringList() << "id" << "idClient";

    columns = core->getDBColumns("facture", not_wanted);
    labels = core->getDBLabels("facture", not_wanted);

    // construction des layouts
    layout = new QVBoxLayout(this);
    invoices_layout = new QVBoxLayout();
    actions_layout = new QHBoxLayout();
    search_form_layout = new QHBoxLayout();

    // création des widgets
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_invoices = new QGroupBox(trUtf8("Liste des factures"), this);
    btn_new = new QPushButton(trUtf8("Nouvelle facture"));
    btn_open = new QPushButton(trUtf8("Ouvrir"));
    btn_del = new QPushButton(trUtf8("Supprimer la facture"));
    search = new QLineEdit();
    search_filters = new QComboBox();

    // définition des filtres de recherche disponibles
    search_filters->addItems(labels);

    // définition des raccourcis clavier pour les boutons
    btn_new->setShortcut(QKeySequence::New);
    btn_open->setShortcut(QKeySequence::Open);
    btn_del->setShortcut(QKeySequence::Delete);

    // désactivation des boutons et widgets inutiles (pour le moment)
    btn_open->setEnabled(false);
    btn_del->setEnabled(false);

    // création du tableau des factures
    invoices_table = new SQLTable("facture");
    invoices_table->setColumns(columns, labels);
    invoices_table->setFilter("Date", displayDate);

    // liaisons des layouts avec les widgets
    search_form_layout->addWidget(search_filters);
    search_form_layout->addWidget(search);

    invoices_layout->addLayout(search_form_layout);
    invoices_layout->addWidget(invoices_table->getWidget());
    gbox_invoices->setLayout(invoices_layout);

    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_open);
    actions_layout->addWidget(btn_del);
    gbox_actions->setLayout(actions_layout);

    layout->addWidget(gbox_invoices);
    layout->addWidget(gbox_actions);

    setLayout(layout);
}

void InvoicesTab::createActions()
{
    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(loadInvoices()));

    // charge le profil d'un client lors du clic sur le bouton "ouvrir"
    this->connect(btn_open, SIGNAL(clicked()), this,
                  SLOT(loadSelectedInvoice()));

    // suppression de la facture sélectionnée lors du clic sur le bouton
    this->connect(btn_del, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // (dés)active les boutons "ouvrir" et "supprimer" en fonction des lignes
    // sélectionnées (ou pas) dans le tableau
    this->connect(invoices_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(onSelectionChanged()));

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

void InvoicesTab::onSelectionChanged()
{
    btn_open->setEnabled(true);
    btn_del->setEnabled(true);
}

void InvoicesTab::onDelClicked()
{
    QMessageBox msgBox;

    // on vérifie qu'il y a bien quelque chose de sélectionné
    if(invoices_table->getWidget()->selectedItems().length() == 0)
        return;

    msgBox.setText(trUtf8("Voulez-vous vraiment supprimer cette facture ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::No)
        return;

    QMessageBox::information(this, "Info", QString(trUtf8("ID cliqué :"))
                            +invoices_table->getSelectedItem()->data(Qt::UserRole).toString());
}

void InvoicesTab::loadSelectedInvoice()
{
    emit newTabRequest("Facture XXX", new InvoiceTab(core, this));
}

void InvoicesTab::loadInvoices()
{
    if(!core->isDBConnected())
        return;

    invoices_table->feedTable();
}

void InvoicesTab::setEnabled(bool state)
{
    gbox_actions->setEnabled(state);
    gbox_invoices->setEnabled(state);
}

