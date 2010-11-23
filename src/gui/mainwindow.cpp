#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/tabs/paramstab.h"
#include "gui/tabs/customerstab.h"
#include "gui/tabs/productstab.h"
#include "managers/settingsmanager.h"

#include <QMessageBox>


MainWindow::MainWindow(QfactureCore *core, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->core = core;

    this->setupTabs();
    this->createActions();

    this->restoreSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createActions()
{
    // fermeture de l'application lors du clic sur le menu concerné
    this->connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(onQuit()));

    // affiche la boite de dialogue "à propos" lors du clic sur le menu concerné
    this->connect(ui->action_propos, SIGNAL(triggered()), this, SLOT(about()));

    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(DBController::getInstance(), SIGNAL(DBConnectionError(QString)),
                  this, SLOT(onDBConnectionError(QString)));

    // affiche un message dans la statusbar à la connexion à la DB
    this->connect(DBController::getInstance(), SIGNAL(DBConnected()), this,
                  SLOT(onDBConnected()));

    // affiche un message dans la statusbar à la déconnexion à la DB
    this->connect(DBController::getInstance(), SIGNAL(DBDisconnected()), this,
                  SLOT(onDBDisconnected()));

    // lie l'évènement "DBError" à l'action correspondante
    this->connect(ProductController::getInstance(), SIGNAL(DBError(QString)), this,
                  SLOT(onDBError(QString)));

    // lie l'évènement "DBError" à l'action correspondante
    this->connect(CustomerController::getInstance(), SIGNAL(DBError(QString)), this,
                  SLOT(onDBError(QString)));
}

void MainWindow::setupTabs()
{
    // paramètres
    ui->tabWidget->addTab(new ParamsTab(core, this), trUtf8("Paramètres"));

    // clients
    ui->tabWidget->addTab(new CustomersTab(core, this), trUtf8("Clients"));

    // prestations
    ui->tabWidget->addTab(new ProductsTab(core, this), trUtf8("Prestations"));
}

void MainWindow::onQuit()
{
    this->saveSettings();

    DBController::getInstance()->disconnectDB();

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
}

void MainWindow::onDBDisconnected()
{
    ui->statusbar->showMessage(trUtf8("Base de données déconnectée."), 3000);
}

void MainWindow::saveSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    // infos sur la fenêtre (taille et position)
    settings.set("Window", "size", size());
    settings.set("Window", "pos", pos());
}

void MainWindow::restoreSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    // infos sur la fenêtre (taille et position)
    resize(settings.get("Window", "size", QSize(400, 400)).toSize());
    move(settings.get("Window", "pos", QPoint(200, 200)).toPoint());
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
                              "Copyrigh : Julien PECQUEUR\n"
                              "Licence : GPL\n"
                              "Auteur : Julien PECQUEUR <jpec@julienpecqueur.com>\n"
                              "Co-auteur : Kévin Gomez <contact@kevingomez.fr>\n"
                              "\n")
                       );
}
