#ifndef INVOICETAB_H
#define INVOICETAB_H

#include "qfacturecore.h"
#include "models/invoice.h"
#include "gui/widgets/sqltable.h"

#include <QListWidget>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QKeyEvent>
#include <QCompleter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QTableWidget>


class InvoiceTab : public QWidget
{
    Q_OBJECT
public:
    explicit InvoiceTab(Invoice invoice, QfactureCore *core, QWidget *parent = 0);
    ~InvoiceTab();

    Invoice getInvoice() const;
    void setIndex(int index);

public slots:
    /**
     * (Dés)active l'onglet
     *
     * @param state État d'activation de l'onglet
     */
    void setEnabled(bool state=true);

signals:
    void productsChanged();

    void invoiceDeleted();
    void invoiceSaved();
    void tabCloseRequested(int);

private slots:
    void onDBStateChanged();
    void onInvoiceStateChanged();
    void onAvailableProductDoubleClicked(QTableWidgetItem *item);
    void onCustomerDoubleClicked(QListWidgetItem *item);
    void onSelectedProductEdited(int row, int col);
    void onSelectedProductDoubleClicked(int row, int col);
    void onInvoiceSaveClicked();
    void onInvoiceDeleteClicked();
    void onInvoiceCloseClicked();
    void onReglementTypeChanged(int type);
    void onDocumentTypeChanged(int type);
    void updateInvoiceAmount();

    /**
     * Charge la liste des clients
     */
    void loadCustomersList();

private:
    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void createActions();

    /**
     * Affiche les données de la facture dans l'onglet
     */
    void displayInvoiceData();

    /**
     * Crée la liste des produits disponibles
     */
    void createAvailableProductsList();

    void loadReglementTypes();

    void loadDocumentTypes();

    void addProductToSelectedList(const Product &p);
    void addProductToSelectedList(InvoiceLine line);

    /**
     * Construit la GUI de l'onglet
     */
    void buildLayout();

    /**
     * Construit la partie haute de la GUI de l'onglet
     */
    void buildHeader();

    /**
     * Construit le corps de la GUI de l'onglet
     */
    void buildBody();

    void buildClientBox();
    void buildCommentBox();
    void buildDetailsBox();
    void buildProductsBox();


    QVBoxLayout *l_layout;
    QHBoxLayout *l_header;
    QVBoxLayout *l_header_left;
    QVBoxLayout *l_header_right;
    QVBoxLayout *l_body;

    QVBoxLayout *l_client;
    QLineEdit *le_client;
    QLineEdit *le_selected_client;
    QListWidget *li_clients;
    QGroupBox *gbox_client;

    QHBoxLayout *l_comment;
    QLineEdit *le_comment;
    QGroupBox *gbox_comment;

    QFormLayout *form_details;
    QHBoxLayout *l_details_button;
    QGroupBox *gbox_details;
    QLineEdit *le_facture_no;
    QDateEdit *le_facture_date;
    QComboBox *le_facture_type;
    QLineEdit *le_facture_montant;
    QComboBox *le_facture_reglement;
    QPushButton *btn_sauver;
    QPushButton *btn_print;
    QPushButton *btn_del;
    QPushButton *btn_close;

    QVBoxLayout *l_products;
    QGroupBox *gbox_products;
    SQLTable *t_available_products;
    QTableWidget *t_selected_products;

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;

    /**
     * Facture représentée dans l'onglet
     */
    Invoice invoice;

    /**
     * Index de l'onglet
     */
    int tab_index;

    static const int COL_NAME           = 0;
    static const int COL_DESCRIPTION    = 1;
    static const int COL_PRICE          = 2;
    static const int COL_QTE            = 3;
    static const int COL_OFF            = 4;
    static const int COL_AMOUNT         = 5;
    static const int COL_ACTION         = 6;
};

#endif // INVOICETAB_H
