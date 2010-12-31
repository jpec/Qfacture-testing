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
}

InvoicesTab::~InvoicesTab()
{
    delete btn_new;
    delete btn_open;
    delete btn_del;
    delete search;
    delete search_filters;

    delete invoices_table;

    delete search_bar_layout;
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

    // création des groupbox
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_invoices = new QGroupBox(trUtf8("Liste des factures"), this);

    // création de la barre de recherche
    buildSearchBar(labels);

    // création des boutons d'actions
    buildActionButtons();

    // création du tableau des factures
    buildInvoicesTableLayout(columns, labels);

    // ajout de la barre de recherche et du tableau de factures  dans invoices_layout
    invoices_layout->addLayout(search_bar_layout);
    invoices_layout->addWidget(invoices_table->getWidget());

    // définition des layouts des groupbox
    gbox_invoices->setLayout(invoices_layout);
    gbox_actions->setLayout(actions_layout);

    // ajout des groupbox au layout principal
    layout->addWidget(gbox_invoices);
    layout->addWidget(gbox_actions);
}

void InvoicesTab::buildInvoicesTableLayout(QStringList columns, QStringList labels)
{
    this->invoices_table = new SQLTable("facture");
    invoices_table->setColumns(columns, labels);
    invoices_table->setFilter("Date", displayDate);
    invoices_table->join("client", QStringList() << "Name");
}

void InvoicesTab::buildSearchBar(QStringList filters)
{
    // création des widgets
    this->search_bar_layout = new QHBoxLayout();
    this->search = new QLineEdit();
    this->search_filters = new QComboBox();

    // définition des filtres de recherche disponibles
    search_filters->addItems(filters);

    // ajout de la QComboBox et du QLineEdit au layout
    search_bar_layout->addWidget(search_filters);
    search_bar_layout->addWidget(search);
}

void InvoicesTab::buildActionButtons()
{
    // layout contenant les boutons
    this->actions_layout = new QHBoxLayout();

    // création des widgets
    this->btn_new = new QPushButton(trUtf8("Nouvelle facture"));
    this->btn_open = new QPushButton(trUtf8("Ouvrir"));
    this->btn_del = new QPushButton(trUtf8("Supprimer la facture"));

    // définition des raccourcis clavier pour les boutons
    btn_new->setShortcut(QKeySequence::New);
    btn_open->setShortcut(QKeySequence::Open);
    btn_del->setShortcut(QKeySequence::Delete);

    // désactivation des boutons et widgets inutiles (pour le moment)
    btn_open->setEnabled(false);
    btn_del->setEnabled(false);

    // ajout des boutons au layout
    actions_layout->addWidget(btn_new);
    actions_layout->addWidget(btn_open);
    actions_layout->addWidget(btn_del);
}

void InvoicesTab::createActions()
{
    // remplissage du tableau dès que la connexion à la DB est établies
    this->connect(core, SIGNAL(DBConnected()), invoices_table, SLOT(feedTable()));

    // création d'une facture lors du clic sur le bouton
    this->connect(btn_new, SIGNAL(clicked()), this, SLOT(onNewClicked()));

    // charge une facture lors du clic sur le bouton "ouvrir"
    this->connect(btn_open, SIGNAL(clicked()), this,
                  SLOT(loadSelectedInvoice()));

    // suppression de la facture sélectionnée lors du clic sur le bouton
    this->connect(btn_del, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // (dés)active les boutons "ouvrir" et "supprimer" en fonction des lignes
    // sélectionnées (ou pas) dans le tableau
    this->connect(invoices_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
                  SLOT(onSelectionChanged()));

    // charge une facture lors du double-clic sur la ligne du tableau la représentant
    this->connect(invoices_table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
                  this, SLOT(loadInvoice(QTableWidgetItem*)));

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

void InvoicesTab::onNewClicked()
{
    loadInvoice(0);
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

    QMessageBox::information(this, "Info", trUtf8("ID cliqué : %1").arg(invoices_table->getSelectedItem()->data(Qt::UserRole).toString()));
}

void InvoicesTab::loadSelectedInvoice()
{
    loadInvoice(invoices_table->getSelectedItem()->data(Qt::UserRole).toInt());
}

void InvoicesTab::loadInvoice(int id)
{
    Invoice invoice = core->getInvoice(id);
    QString tab_name = invoice.getId() == 0 ? trUtf8("Nouvelle facture")
                                            : trUtf8("Facture %1").arg(invoice.getRef());

    emit newTabRequest(tab_name, new InvoiceTab(invoice, core, this));
}

void InvoicesTab::loadInvoice(QTableWidgetItem *item)
{
    loadInvoice(item->data(Qt::UserRole).toInt());
}

void InvoicesTab::setEnabled(bool state)
{
    gbox_actions->setEnabled(state);
    gbox_invoices->setEnabled(state);
}

