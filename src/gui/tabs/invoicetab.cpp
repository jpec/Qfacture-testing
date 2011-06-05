#include "invoicetab.h"
#include "controllers/dbcontroller.h"
#include "gui/mainwindow.h"

#include <QMessageBox>


InvoiceTab::InvoiceTab(Invoice invoice, QfactureCore *core, QWidget *parent) :
        QWidget(parent)
{
    this->core = core;
    this->invoice = invoice;

    buildLayout();
    createActions();

    onInvoiceStateChanged();

    loadCustomersList();
    loadDocumentTypes();
    loadReglementTypes();

    if(!invoice.isNew())
        displayInvoiceData();
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
    delete btn_sauver;
    delete btn_print;
    delete btn_del;
    delete btn_close;
    delete t_available_products;
    delete t_selected_products;

    delete l_client;
    delete l_comment;
    delete form_details;
    delete l_details_button;
    delete l_products;

    delete l_header_left;
    delete l_header_right;
    delete l_header;
    delete l_body;
    delete l_layout;

    delete gbox_products;
    delete gbox_client;
    delete gbox_comment;
    delete gbox_details;
}

Invoice InvoiceTab::getInvoice() const
{
    return invoice;
}

void InvoiceTab::setIndex(int index)
{
    this->tab_index = index;
}

void InvoiceTab::createActions()
{
    // activation de l'onglet dès que la connexion à la DB est établie
    connect(core, SIGNAL(DBConnected()), this, SLOT(onDBStateChanged()));

    // activation de l'onglet dès que la connexion à la DB est établie
    connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBStateChanged()));

    connect(btn_sauver, SIGNAL(clicked()), this, SLOT(onInvoiceSaveClicked()));

    connect(btn_del, SIGNAL(clicked()), this, SLOT(onInvoiceDeleteClicked()));

    connect(btn_close, SIGNAL(clicked()), this, SLOT(onInvoiceCloseClicked()));

    // ajout d'un produit lors du double clic sur ce dernier
    connect(t_available_products, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
            this, SLOT(onAvailableProductDoubleClicked(QTableWidgetItem*)));

    connect(this, SIGNAL(productsChanged()), this, SLOT(updateInvoiceAmount()));

    connect(le_facture_type, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onDocumentTypeChanged(int)));

    connect(le_facture_reglement, SIGNAL(currentIndexChanged(int)), this,
            SLOT(onReglementTypeChanged(int)));

    // édition d'un produit sélectionné
    connect(t_selected_products, SIGNAL(cellChanged(int,int)), this,
            SLOT(onSelectedProductEdited(int, int)));

    // suppression d'un produit sélectionné
    connect(t_selected_products, SIGNAL(cellDoubleClicked(int,int)), this,
            SLOT(onSelectedProductDoubleClicked(int,int)));

    // changement du client lors du double-clic sur son nom dans la list
    connect(li_clients, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this,
            SLOT(onCustomerDoubleClicked(QListWidgetItem*)));

    // rechargement de la liste des clients lorsque l'utilisateur tappe du texte
    // dans la textbox des filtres
    connect(le_client, SIGNAL(textChanged(QString)), this,
            SLOT(loadCustomersList()));
}

void InvoiceTab::onDBStateChanged()
{
    setEnabled(core->isDBConnected());
}

void InvoiceTab::onInvoiceStateChanged()
{
    btn_print->setEnabled(!invoice.isNew());
    btn_del->setEnabled(!invoice.isNew());
}

void InvoiceTab::onDocumentTypeChanged(int type)
{
    QList<DocumentType> list = core->getDocumentsTypes();

    for(int i=0; i < list.size(); ++i)
    {
        if(list.at(i).getId() == le_facture_type->itemData(type).toInt())
        {
            invoice.setType(list.at(i));

            break;
        }
    }
}

void InvoiceTab::onReglementTypeChanged(int type)
{
    QList<ReglementType> list = core->getReglements();

    for(int i=0; i < list.size(); ++i)
    {
        if(list.at(i).getId() == le_facture_reglement->itemData(type).toInt())
        {
            invoice.setReglement(list.at(i));

            break;
        }
    }
}

void InvoiceTab::onInvoiceDeleteClicked()
{
    QMessageBox msgBox;

    msgBox.setText(trUtf8("Voulez-vous vraiment supprimer cette facture ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::No)
        return;

    if(!core->erase(invoice))
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible de supprimer la facture."));
    else {
        emit invoiceDeleted();
        // suppression de l'onglet
        emit tabCloseRequested(this->tab_index);
        QMessageBox::information(this, trUtf8("Facture supprimée"),
                                 trUtf8("La facture a été supprimée."));
    }
}

void InvoiceTab::onInvoiceCloseClicked()
{
    QMessageBox msgBox;

    msgBox.setText(trUtf8("Voulez-vous vraiment fermer cette facture ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::No)
        return;

    emit tabCloseRequested(this->tab_index);
}

void InvoiceTab::onInvoiceSaveClicked()
{
    invoice.setDescription(le_comment->text());
    invoice.setDate(le_facture_date->date());

    if(!core->save(invoice))
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible d'enregistrer la facture."));
    else {
        onInvoiceStateChanged();

        QMessageBox::information(this, trUtf8("Facture enregistrée"),
                                 trUtf8("La facture a été enregistrée."));

        emit invoiceSaved();
    }
}

void InvoiceTab::onCustomerDoubleClicked(QListWidgetItem *item)
{
    Customer c = core->getCustomer(item->data(Qt::UserRole).toInt());

    if(c.isNew())
        QMessageBox::critical(this, trUtf8("Erreur"),
                              "Impossible de récupérer les données client");

    this->invoice.setCustomer(c);
    le_selected_client->setText(c.getName());
}

void InvoiceTab::onAvailableProductDoubleClicked(QTableWidgetItem *item)
{
    Product p = core->getProduct(item->data(Qt::UserRole).toInt());

    if(p.isNew())
    {
        QMessageBox::critical(this, trUtf8("Erreur !"), trUtf8("Produit inconnu"));

        return;
    }

    addProductToSelectedList(p);
}

void InvoiceTab::updateInvoiceAmount()
{
    le_facture_montant->setText(QVariant(invoice.getAmount()).toString()
                                + trUtf8(" €"));
}

void InvoiceTab::addProductToSelectedList(const Product &p)
{
    InvoiceLine line = InvoiceLine::fromProduct(p);

    for(int i=0; i < invoice.getLinesCount(); ++i)
    {
        // si le produit est déjà dans le tableau, on incrémente juste la quantité
        if(t_selected_products->item(i, COL_NAME)->data(Qt::UserRole).toInt() == line.getBaseProductId())
        {
            invoice.getLine(i).setQte(invoice.getLine(i).getQte() + 1);

            t_selected_products->item(i, COL_QTE)->setText(QVariant(invoice.getLine(i).getQte()).toString());

            return;
        }
    }

    invoice.addLine(line);

    addProductToSelectedList(line);
}

void InvoiceTab::addProductToSelectedList(InvoiceLine line)
{
    int row_id = t_selected_products->rowCount();

    t_selected_products->setRowCount(row_id + 1);

    t_selected_products->setItem(row_id, COL_NAME, new QTableWidgetItem(line.getName()));
    t_selected_products->setItem(row_id, COL_DESCRIPTION, new QTableWidgetItem(line.getDescription()));
    t_selected_products->setItem(row_id, COL_PRICE, new QTableWidgetItem(QVariant(line.getPrice()).toString()));
    t_selected_products->setItem(row_id, COL_QTE, new QTableWidgetItem(QVariant(line.getQte()).toString()));
    t_selected_products->setItem(row_id, COL_OFF, new QTableWidgetItem(QVariant(line.getOffPercentage()).toString()));

    // ces colonne sont traitées différement : pas d'édition possible
    QTableWidgetItem *amount_item = new QTableWidgetItem(QVariant(line.getAmount()).toString());
    amount_item->setFlags(amount_item->flags() & (~Qt::ItemIsEditable));
    t_selected_products->setItem(row_id, COL_AMOUNT, amount_item);

    QTableWidgetItem *delete_item = new QTableWidgetItem(QIcon::fromTheme("edit-delete"),
                                                         trUtf8("Supprimer"));
    delete_item->setFlags(delete_item->flags() & (~Qt::ItemIsEditable));
    t_selected_products->setItem(row_id, COL_ACTION, delete_item);

    t_selected_products->item(row_id, COL_NAME)->setData(Qt::UserRole,
                                                         line.getBaseProductId());

    emit productsChanged();
}

void InvoiceTab::onSelectedProductEdited(int row, int col)
{
    InvoiceLine& line = invoice.getLine(row);

    // à l'édition du nom
    if(col == COL_NAME)
    {
        line.setName(t_selected_products->item(row, COL_NAME)->text());

        t_selected_products->item(row, COL_NAME)->setText(line.getName());
    }
    // à l'édition de la description
    else if(col == COL_DESCRIPTION)
    {
        line.setDescription(t_selected_products->item(row, COL_DESCRIPTION)->text());

        t_selected_products->item(row, COL_DESCRIPTION)->setText(line.getDescription());
    }
    // à l'édition du prix
    else if(col == COL_PRICE)
    {
        line.setPrice(t_selected_products->item(row, COL_PRICE)->text().toFloat());

        t_selected_products->item(row, COL_PRICE)->setText(QVariant(line.getPrice()).toString());
    }
    // à l'édition de la quantité
    else if(col == COL_QTE && t_selected_products->item(row, COL_QTE))
    {
        line.setQte(t_selected_products->item(row, COL_QTE)->text().toInt());

        t_selected_products->item(row, COL_QTE)->setText(QVariant(line.getQte()).toString());
    }
    // à l'édition de la remise
    else if(col == COL_OFF)
    {
        line.setOffPercentage(t_selected_products->item(row, COL_OFF)->text().toFloat());

        t_selected_products->item(row, COL_OFF)->setText(QVariant(line.getOffPercentage()).toString());
    }

    // on doit recalculer le prix
    if(col == COL_PRICE || col == COL_QTE || col == COL_OFF)
    {
        if(!t_selected_products->item(row, COL_QTE) || !t_selected_products->item(row, COL_AMOUNT))
            return;

        t_selected_products->item(row, COL_AMOUNT)->setText(QVariant(line.getAmount()).toString());

        emit productsChanged();
    }
}

void InvoiceTab::onSelectedProductDoubleClicked(int row, int col)
{
    if(col == COL_ACTION)
    {
        t_selected_products->removeRow(row);
        invoice.removeLine(row);

        emit productsChanged();
    }
}

void InvoiceTab::displayInvoiceData()
{
    le_facture_no->setText(QVariant(invoice.getId()).toString());
    le_facture_date->setDate(invoice.getDate());
    le_comment->setText(invoice.getDescription());
    le_selected_client->setText(invoice.getCustomer().getName());

    for(int i=0; i < invoice.getLinesCount(); ++i)
        addProductToSelectedList(invoice.getLine(i));
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
    l_body = new QVBoxLayout();

    buildProductsBox();

    l_layout->addLayout(l_body);
}

void InvoiceTab::buildProductsBox()
{
    QStringList columns_labels;
    columns_labels << trUtf8("Nom") << trUtf8("Désignation")
                   << trUtf8("Prix unitaire") << trUtf8("Quantité")
                   << trUtf8("Remise (%)") << trUtf8("Total")
                   << trUtf8("Action");

    createAvailableProductsList();

    l_products = new QVBoxLayout();
    gbox_products = new QGroupBox(trUtf8("Liste des prestations"));
    t_selected_products = new QTableWidget(0, 7);

    t_selected_products->setSelectionMode(QAbstractItemView::SingleSelection);
    t_selected_products->setHorizontalHeaderLabels(columns_labels);

    l_products->addWidget(t_available_products->getWidget());
    l_products->addWidget(t_selected_products);

    gbox_products->setLayout(l_products);

    l_body->addWidget(gbox_products);
}

void InvoiceTab::createAvailableProductsList()
{
    // définition des colonnes du tableau
    QStringList not_wanted = QStringList() << "aID";
    QStringList columns = core->getDBColumns("article", not_wanted);
    QStringList labels = core->getDBLabels("article", not_wanted);

    // création du tableau de produits
    t_available_products = new SQLTable("article", core->getCurrentProfile().getId());
    t_available_products->setColumns(columns, labels);
}

void InvoiceTab::loadCustomersList()
{
    li_clients->clear();

    QList<Customer> c_list = core->getCustomersList(le_client->text());

    for(int i = 0; i < c_list.size(); ++i)
    {
        li_clients->addItem(c_list.at(i).getName());
        li_clients->item(i)->setData(Qt::UserRole, c_list.at(i).getId());
    }
}
void InvoiceTab::loadReglementTypes()
{
    bool set = false;
    QList<ReglementType> list = core->getReglements();

    le_facture_reglement->clear();

    for (int i = 0; i < list.size(); ++i) {
        le_facture_reglement->addItem(list.at(i).getName());
        le_facture_reglement->setItemData(i, list.at(i).getId(), Qt::UserRole);

        if(!invoice.isNew() && list.at(i).getId() == invoice.getReglement().getId())
        {
            le_facture_reglement->setCurrentIndex(i);
            set = true;
        }
    }

    if(!set)
    {
        le_facture_reglement->setCurrentIndex(-1);
        le_facture_reglement->setCurrentIndex(0);
    }
}

void InvoiceTab::loadDocumentTypes()
{
    bool set = false;
    QList<DocumentType> list = core->getDocumentsTypes();

    le_facture_reglement->clear();

    for (int i = 0; i < list.size(); ++i) {
        le_facture_type->addItem(list.at(i).getName());
        le_facture_type->setItemData(i, list.at(i).getId());

        if(!invoice.isNew() && list.at(i).getId() == invoice.getReglement().getId())
        {
            le_facture_type->setCurrentIndex(i);
            set = true;
        }
    }

    if(!set)
    {
        le_facture_type->setCurrentIndex(-1);
        le_facture_type->setCurrentIndex(0);
    }
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

    le_comment->setPlaceholderText(trUtf8("Description de la facture ..."));

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

    le_facture_no->setEnabled(false);
    le_facture_montant->setEnabled(false);
    le_facture_date->setDisplayFormat("dd/MM/yyyy");
    le_facture_date->setDate(QDate::currentDate());

    form_details->addRow(trUtf8("Numéro de la facture"), le_facture_no);
    form_details->addRow(trUtf8("Date de facturation"), le_facture_date);
    form_details->addRow(trUtf8("Type de document"), le_facture_type);
    form_details->addRow(trUtf8("Montant total"), le_facture_montant);
    form_details->addRow(trUtf8("Règlement"), le_facture_reglement);

    gbox_details->setLayout(form_details);

    // boutons du form
    l_details_button = new QHBoxLayout();
    btn_sauver = new QPushButton(trUtf8("Sauver"));
    btn_print = new QPushButton(trUtf8("Imprimer"));
    btn_del = new QPushButton(trUtf8("Supprimer"));
    btn_close = new QPushButton(trUtf8("Fermer"));

    l_details_button->addWidget(btn_sauver);
    l_details_button->addWidget(btn_print);
    l_details_button->addWidget(btn_del);
    l_details_button->addWidget(btn_close);

    l_header_right->addWidget(gbox_details);
    l_header_right->addLayout(l_details_button);
    l_header_right->addStretch(); // pour que les boutons soient collés au form
}

void InvoiceTab::setEnabled(bool state)
{
    gbox_client->setEnabled(state);
    gbox_comment->setEnabled(state);
    gbox_details->setEnabled(state);
    gbox_products->setEnabled(state);

    btn_sauver->setEnabled(state);
    btn_print->setEnabled(state);
    btn_del->setEnabled(state);
    btn_close->setEnabled(state);
}
