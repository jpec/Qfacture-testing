#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/tabs/paramstab.h"

#include <QMessageBox>


#include <QTableWidget>


MainWindow::MainWindow(QfactureCore *core, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->core = core;
    
    this->setupTabs();
    this->setupActions();
    
    this->restoreSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupTabs()
{
    // paramètres
    ui->tabWidget->addTab(new ParamsTab(core, this), trUtf8("Paramètres"));
    
    // clients
    ui->tabWidget->addTab(new QTableWidget(ui->tabWidget), trUtf8("Clients"));
}

void MainWindow::setupActions()
{
    // fermeture de l'application lors du clic sur le menu concerné
    this->connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(onQuit()));
    
    // affiche la boite de dialogue "à propos" lors du clic sur le menu concerné
    this->connect(ui->action_propos, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::onQuit()
{
	this->saveSettings();
	this->core->disconnectDB();
    
	qApp->quit();
}

void MainWindow::saveSettings()
{
	// infos sur la fenêtre (taille et position)
	core->setSetting("Window", "size", size());
	core->setSetting("Window", "pos", pos());
}

void MainWindow::restoreSettings()
{
	// infos sur la fenêtre (taille et position)
	resize(core->getSetting("Window", "size", QSize(400, 400)).toSize());
	move(core->getSetting("Window", "pos", QPoint(200, 200)).toPoint());
}

void MainWindow::about()
{
    QMessageBox::about(this, trUtf8("Qfacture v%1")
                       .arg(core->version()),
                       trUtf8("Le logiciel libre de facturation pour les Auto-Entrepreneurs!\n"
                              "--\n"
                              "Copyright 2010 : Julien PECQUEUR\n"
                              "Licence : GPL\n"
                              "Auteur : Julien PECQUEUR <jpec@julienpecqueur.com>\n"
                              "--\n"
                              "Contributeur(s) :\n"
                              " * Kévin Gomez <contact@kevingomez.fr>\n"
                              "\n")
                       );
}
