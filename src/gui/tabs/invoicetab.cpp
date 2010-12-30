#include "invoicetab.h"
#include "controllers/dbcontroller.h"

InvoiceTab::InvoiceTab(Invoice invoice, QfactureCore *core, QWidget *parent) :
        QWidget(parent)
{
    this->core = core;
    this->invoice = invoice;

    buildLayout();
}

InvoiceTab::~InvoiceTab()
{
    delete li_clients;
    delete le_client;
    delete le_selected_client;
    delete le_comment;
    delete le_facture_no;
    delete le_facture_date;
    delete le_facture_type;
    delete le_facture_montant;
    delete le_facture_reglement;
    delete btn_creer;
    delete btn_sauver;
    delete btn_print;
    delete btn_del;

    delete l_client;
    delete l_comment;
    delete form_details;
    delete l_details_button;

    delete l_header_left;
    delete l_header_right;
    delete l_header;
    delete l_body;
    delete l_layout;

    delete gbox_client;
    delete gbox_comment;
    delete gbox_details;
}

void InvoiceTab::buildLayout()
{
    l_layout = new QVBoxLayout();

    buildHeader();
    buildBody();

    setLayout(l_layout);
}

void InvoiceTab::buildHeader()
{
    l_header = new QHBoxLayout();
    l_header_left = new QVBoxLayout();
    l_header_right = new QVBoxLayout();

    buildClientBox();
    buildCommentBox();
    buildDetailsBox();

    l_header->addLayout(l_header_left);
    l_header->addLayout(l_header_right);

    l_layout->addLayout(l_header);
}

void InvoiceTab::buildBody()
{
    l_body = new QHBoxLayout();

    l_body->addWidget(new QTableWidget(10, 6));

    l_layout->addLayout(l_body);
}

void InvoiceTab::buildClientBox()
{
    l_client = new QVBoxLayout();

    gbox_client = new QGroupBox(trUtf8("Client"));
    le_client = new QLineEdit();
    le_selected_client = new QLineEdit();
    li_clients = new QListWidget();

    le_client->setPlaceholderText(trUtf8("Rechercher un client ..."));
    le_selected_client->setEnabled(false);

    l_client->addWidget(le_client);
    l_client->addWidget(li_clients);
    l_client->addWidget(le_selected_client);

    gbox_client->setLayout(l_client);

    l_header_left->addWidget(gbox_client);
}

void InvoiceTab::buildCommentBox()
{
    l_comment = new QHBoxLayout();

    gbox_comment = new QGroupBox(trUtf8("Commentaire"));
    le_comment = new QLineEdit();

    l_comment->addWidget(le_comment);

    gbox_comment->setLayout(l_comment);

    l_header_left->addWidget(gbox_comment);
}

void InvoiceTab::buildDetailsBox()
{
    // formulaire
    form_details = new QFormLayout();

    gbox_details = new QGroupBox(trUtf8("Détails de la facture"));
    le_facture_no = new QLineEdit();
    le_facture_date = new QDateEdit();
    le_facture_type = new QComboBox();
    le_facture_montant = new QLineEdit();
    le_facture_reglement = new QComboBox();

    form_details->addRow(trUtf8("Numéro de la facture"), le_facture_no);
    form_details->addRow(trUtf8("Date de facturation"), le_facture_date);
    form_details->addRow(trUtf8("Type de document"), le_facture_type);
    form_details->addRow(trUtf8("Montant total"), le_facture_montant);
    form_details->addRow(trUtf8("Règlement"), le_facture_reglement);

    gbox_details->setLayout(form_details);

    // boutons du form
    l_details_button = new QHBoxLayout();
    btn_creer = new QPushButton(trUtf8("Créer"));
    btn_sauver = new QPushButton(trUtf8("Sauver"));
    btn_print = new QPushButton(trUtf8("Imprimer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));

    l_details_button->addWidget(btn_creer);
    l_details_button->addWidget(btn_sauver);
    l_details_button->addWidget(btn_print);
    l_details_button->addWidget(btn_del);

    l_header_right->addWidget(gbox_details);
    l_header_right->addLayout(l_details_button);
    l_header_right->addStretch(); // pour que les boutons soient collés au form
}

void InvoiceTab::setEnabled(bool state)
{

}
