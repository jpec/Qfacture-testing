#include "templatetab.h"
#include "controllers/dbcontroller.h"

#include <QMessageBox>

TemplateTab::TemplateTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();
}

TemplateTab::~TemplateTab()
{
    delete layout;

}


void TemplateTab::buildLayout()
{

    // construction des layouts
    layout = new QVBoxLayout(this);
    template_layout = new QVBoxLayout();

    // création des groupbox
    gbox_actions = new QGroupBox(trUtf8("Actions"));
    gbox_template = new QGroupBox(trUtf8("Edition du template de facture"), this);

    // création des boutons d'actions
    buildActionButtons();

    // création du layout d'édition
    buildTemplateEdition();

    // définition des layouts des groupbox
    gbox_template->setLayout(template_layout);
    gbox_actions->setLayout(actions_layout);

    // ajout des groupbox au layout principal
    layout->addWidget(gbox_template);
    layout->addWidget(gbox_actions);
}

void TemplateTab::buildActionButtons()
{
    // layout contenant les boutons
    this->actions_layout = new QHBoxLayout();

    // création des widgets
    this->btn_new = new QPushButton(trUtf8("Nouveau template"));
    this->btn_open = new QPushButton(trUtf8("Ouvrir template"));
    this->btn_del = new QPushButton(trUtf8("Supprimer template"));

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

void TemplateTab::buildTemplateEdition()
{
    // création des widgets
    this->cb_template = new QComboBox();
    this->ed_template = new QTextEdit();

    // ajout des widgets au layout
    template_layout->addWidget(cb_template);
    template_layout->addWidget(ed_template);
}

void TemplateTab::createActions()
{
    // remplissage du tableau dès que la connexion à la DB est établies
    //this->connect(core, SIGNAL(DBConnected()), invoices_table, SLOT(feedTable()));

    // création d'une facture lors du clic sur le bouton
    this->connect(btn_new, SIGNAL(clicked()), this, SLOT(onNewClicked()));

    // charge une facture lors du clic sur le bouton "ouvrir"
    this->connect(btn_open, SIGNAL(clicked()), this, SLOT(onOpenClicked()));

    // suppression de la facture sélectionnée lors du clic sur le bouton
    this->connect(btn_del, SIGNAL(clicked()), this, SLOT(onDelClicked()));

    // (dés)active les boutons "ouvrir" et "supprimer" en fonction des lignes
    // sélectionnées (ou pas) dans le tableau
    //this->connect(invoices_table, SIGNAL(itemSelected(QTableWidgetItem*)), this,
    //              SLOT(onSelectionChanged()));


    // on recharge la liste des facture dès qu'on en a ajouté/supprimé/modifié une
    //connect(this, SIGNAL(invoiceDeleted()), invoices_table, SLOT(feedTable()));
    //connect(this, SIGNAL(invoiceAdded()), invoices_table, SLOT(feedTable()));
}

void TemplateTab::onNewClicked()
{
    //loadInvoice(0);
}

void TemplateTab::onOpenClicked()
{
    //loadInvoice(0);
}

void TemplateTab::onDelClicked()
{
    QMessageBox msgBox;

    // on vérifie qu'il y a bien quelque chose de sélectionné
    //if(invoices_table->getWidget()->selectedItems().length() == 0)
    //    return;

    msgBox.setText(trUtf8("Voulez-vous vraiment supprimer ce template ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::No)
        return;

    //if(!core->eraseInvoice(invoices_table->getSelectedItem()->data(Qt::UserRole).toInt()))
    //{
    //    QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Impossible de supprimer la facture"));
    //    return;
    //}

    QMessageBox::information(this, trUtf8("Template supprimé"), trUtf8("Template supprimé"));

    //emit invoiceDeleted();
}

void TemplateTab::setEnabled(bool state)
{
    gbox_actions->setEnabled(state);
    //gbox_invoices->setEnabled(state);
}
