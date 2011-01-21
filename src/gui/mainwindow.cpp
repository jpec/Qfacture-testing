#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "managers/settingsmanager.h"

#include <QMessageBox>


MainWindow::MainWindow(QfactureCore *core, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setMovable(true);

    // nécéssite d'ajouter dans les menus la possibilité de rouvrir les onglets
    // importants (paramètres, clients, produits, factures, etc.).
    // il serait bien de mémoriser la liste des onglets ouverts à la fermeture
    // de l'appli et de rouvrir ces mêmes onglets
    // ui->tabWidget->setTabsClosable(true);

    this->core = core;

    this->setupTabs();
    this->createActions();

    this->restoreSettings();
}

MainWindow::~MainWindow()
{
    delete params_tab;
    delete customers_tab;
    delete products_tab;
    delete invoices_tab;
    //delete invoice_tab;

    delete ui;
}


void MainWindow::createActions()
{
    // fermeture de l'application lors du clic sur le menu concerné
    this->connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(onQuit()));

    // affiche la boite de dialogue "à propos" lors du clic sur le menu concerné
    this->connect(ui->action_propos, SIGNAL(triggered()), this, SLOT(about()));

    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this,
                  SLOT(onDBConnectionError(QString)));

    // affiche un message dans la statusbar à la connexion à la DB
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnected()));

    // affiche un message dans la statusbar à la déconnexion à la DB
    this->connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBDisconnected()));

    // lie l'évènement "DBError" à l'action correspondante
    this->connect(core, SIGNAL(DBError(QString)), this, SLOT(onDBError(QString)));

    // écoute les demandes de création de nouveaux onglets émises par l'onglet
    // de gestion des factures
    this->connect(invoices_tab, SIGNAL(newTabRequest(QString, InvoiceTab*)), this,
                  SLOT(onNewTabRequest(QString, InvoiceTab*)));

    this->connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this,
                  SLOT(onTabCloseRequested(int)));
}

void MainWindow::setupTabs()
{
    //ui->tabWidget->setTabsClosable(true);

    // paramètres
    params_tab = new ParamsTab(core, this);
    ui->tabWidget->addTab(params_tab, trUtf8("Paramètres"));

    // clients
    customers_tab = new CustomersTab(core, this);
    customers_tab->setEnabled(false);
    ui->tabWidget->addTab(customers_tab, trUtf8("Clients"));

    // prestations
    products_tab = new ProductsTab(core, this);
    products_tab->setEnabled(false);
    ui->tabWidget->addTab(products_tab, trUtf8("Prestations"));

    // liste des factures
    invoices_tab = new InvoicesTab(core, this);
    invoices_tab->setEnabled(false);
    ui->tabWidget->addTab(invoices_tab, trUtf8("Factures"));
}

void MainWindow::onQuit()
{
    this->saveSettings();

    core->disconnectDB();

    qApp->quit();
}

void MainWindow::onDBConnectionError(const QString &error)
{
    alert(trUtf8("Une erreur est survenue lors de la connexion : %1").arg(error));
}

void MainWindow::onDBError(const QString &error)
{
    alert(trUtf8("Une erreur SQL est survenue : %1").arg(error));
}

void MainWindow::onDBConnected()
{
    ui->statusbar->showMessage(trUtf8("Base de données connectée."), 3000);

    customers_tab->setEnabled();
    products_tab->setEnabled();
    invoices_tab->setEnabled();
}

void MainWindow::onDBDisconnected()
{
    ui->statusbar->showMessage(trUtf8("Base de données déconnectée."), 3000);

    customers_tab->setEnabled(false);
    products_tab->setEnabled(false);
    invoices_tab->setEnabled(false);
}

void MainWindow::saveSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    // infos sur la fenêtre (taille et position)
    settings.set("Window", "size", size());
    settings.set("Window", "pos", pos());
    settings.set("Window", "maximized", isMaximized());
}

void MainWindow::restoreSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    // infos sur la fenêtre (taille et position)
    resize(settings.get("Window", "size", QSize(400, 400)).toSize());
    move(settings.get("Window", "pos", QPoint(200, 200)).toPoint());

    if(settings.get("Window", "maximized", false).toBool())
        showMaximized();
}

void MainWindow::alert(const QString &message)
{
    QMessageBox::critical(this, trUtf8("Erreur !"), message);
}

void MainWindow::about()
{
    QMessageBox::about(this, trUtf8("Qfacture v%1")
                       .arg(core->version()),
                       trUtf8("Le logiciel libre de facturation pour les "
                              "Auto-Entrepreneurs!\n"
                              "--\n"
                              "Copyright : Julien PECQUEUR\n"
                              "Licence : GPL\n"
                              "Auteur : Julien PECQUEUR <jpec@julienpecqueur.com>\n"
                              "Co-auteur : Kévin Gomez <contact@kevingomez.fr>\n"
                              "\n")
                       );
}

void MainWindow::onNewTabRequest(const QString& name, InvoiceTab* content)
{
    int index = ui->tabWidget->addTab(content, name);

    ui->tabWidget->setCurrentIndex(index);

    connect(content, SIGNAL(invoiceSaved()), invoices_tab, SIGNAL(invoiceAdded()));
    connect(content, SIGNAL(invoiceDeleted()), invoices_tab, SIGNAL(invoiceDeleted()));
}

void MainWindow::onTabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
