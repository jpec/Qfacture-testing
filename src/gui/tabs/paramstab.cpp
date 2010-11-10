#include "paramstab.h"
#include "ui_paramstab.h"

#include <QMessageBox>


ParamsTab::ParamsTab(QfactureCore *core, QWidget *parent) : QWidget(parent), ui(new Ui::ParamsTab)
{
    ui->setupUi(this);
    this->core = core;
    
    this->setupActions();
    
    this->restoreSettings();
}

ParamsTab::~ParamsTab()
{
    this->saveSettings();
    
    delete ui;
}


void ParamsTab::setupActions()
{
    // appelle la méthode de connexion à la DB lors du clic sur le bouton
    this->connect(ui->app_connect, SIGNAL(clicked()), this, SLOT(handleDBConnection()));
    
    // informe le programme que l'état de la connexion à la DB a changé
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnectionStateChanged()));
    this->connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBConnectionStateChanged()));
    
    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this, SLOT(onDBConnectionError(QString)));
    
    // lie l'évènement "DBError" à l'action correspondante
    this->connect(core, SIGNAL(DBError(QString)), this, SLOT(onDBError(QString)));
}

void ParamsTab::saveSettings()
{
	// infos de connexion à la DB
	core->setSetting("DB", "host", ui->app_server->text());
	core->setSetting("DB", "port", ui->app_port->text().toInt());
	core->setSetting("DB", "user", ui->app_user->text());
	core->setSetting("DB", "passwd", ui->app_pass->text());
	core->setSetting("DB", "db_name", ui->app_db->text());
}

void ParamsTab::restoreSettings()
{
	// infos de connexion à la DB
	ui->app_server->setText(core->getSetting("DB", "host", "localhost").toString());
	ui->app_port->setText(core->getSetting("DB", "port", 3306).toString());
	ui->app_user->setText(core->getSetting("DB", "user", "qfacture").toString());
	ui->app_pass->setText(core->getSetting("DB", "passwd", "").toString());
	ui->app_db->setText(core->getSetting("DB", "db_name", "qfacture_db").toString());
}

/**
 * Si on est déjà connecté à la DB, on lance la déconnexion, sinon on lance la
 * connexion
 */ 
void ParamsTab::handleDBConnection()
{
    if(core->isDBConnected())
        core->disconnectDB();
    else
        core->connectDB(ui->app_server->text(), ui->app_port->text().toInt(), ui->app_user->text(),
                        ui->app_pass->text(), ui->app_db->text());
}

/**
 * S'occupe de mettre à jour l'affichage du bouton et l'état d'activation des
 * champs
 */ 
void ParamsTab::onDBConnectionStateChanged()
{
    bool connexion_state = core->isDBConnected();
    
    // mise à jour des widgets en fonction de l'état de la connexion
    ui->app_connect->setText(connexion_state ? trUtf8("Déconnexion") : trUtf8("Connexion"));
    ui->uSave->setEnabled(connexion_state);
    ui->uGroupBox->setEnabled(connexion_state);
    ui->app_server->setEnabled(!connexion_state);
    ui->app_port->setEnabled(!connexion_state);
    ui->app_user->setEnabled(!connexion_state);
    ui->app_pass->setEnabled(!connexion_state);
    ui->app_db->setEnabled(!connexion_state);
}

void ParamsTab::onDBConnectionError(const QString &error)
{
    QMessageBox::critical(this, trUtf8("Erreur !"), trUtf8("Une erreur est survenue lors de la connexion : %1").arg(error));
}

void ParamsTab::onDBError(const QString &error)
{
    QMessageBox::critical(this, trUtf8("Erreur !"), trUtf8("Une erreur SQL est survenue : %1").arg(error));
}
