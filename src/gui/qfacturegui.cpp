#include "qfacturegui.h"
#include "ui_qfacturegui.h"
#include "qfacturecore.h"

#include <QMessageBox>
#include <QPixmap>


QfactureGui::QfactureGui(QfactureCore *core, QWidget *parent) : QMainWindow(parent), ui(new Ui::QfactureGui)
{
    ui->setupUi(this);
    this->core = core;
    
    this->setupActions();
    
    restoreSettings();
}

QfactureGui::~QfactureGui()
{
    delete ui;
}

void QfactureGui::onQuit()
{
	this->saveSettings();
	this->core->disconnectDB();
    
	qApp->quit();
}

void QfactureGui::setupActions()
{
    // fermeture de l'application lors du clic sur le menu concerné
    this->connect(ui->action_quit, SIGNAL(triggered()), this, SLOT(onQuit()));
    
    // appelle la méthode de connexion à la DB lors du clic sur le bouton
    this->connect(ui->app_connect, SIGNAL(clicked()), this, SLOT(handleDBConnection()));
    
    // lie l'évènement "DBConnected" à l'action correspondante
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnected()));
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnectionStateChanged()));

    // lie l'évènement "DBDisconnected" à l'action correspondante
    this->connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBConnectionStateChanged()));
    
    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this, SLOT(onDBConnectionError(QString)));
    
    // lie l'évènement "DBError" à l'action correspondante
    this->connect(core, SIGNAL(DBError(QString)), this, SLOT(onDBError(QString)));
    
    // enregistre le profile actuellement chargé à la demande de l'utilisateur
    this->connect(ui->uSave, SIGNAL(clicked()), this, SLOT(saveLoadedProfile()));
}

/**
 * Si on est déjà connecté à la DB, on lance la déconnexion, sinon on lance la
 * connexion
 */ 
void QfactureGui::handleDBConnection()
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
void QfactureGui::onDBConnectionStateChanged()
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

void QfactureGui::onDBConnected()
{
    //QMessageBox::warning(this, "Qfacture", trUtf8("OK !"), QMessageBox::Ok);
    
    this->loadLastProfile();
}

void QfactureGui::onDBConnectionError(const QString &error)
{
    QMessageBox::warning(this, "Qfacture", trUtf8("Une erreur est survenue lors de la connexion : %1").arg(error),
                         QMessageBox::Ok);
}

void QfactureGui::onDBError(const QString &error)
{
    QMessageBox::warning(this, "Qfacture", trUtf8("Une erreur SQL est survenue : %1").arg(error),
                         QMessageBox::Ok);
}

void QfactureGui::saveSettings()
{
	// infos sur la fenêtre (taille et position)
	core->setSetting("Window", "size", size());
	core->setSetting("Window", "pos", pos());
	
	// infos de connexion à la DB
	core->setSetting("DB", "host", ui->app_server->text());
	core->setSetting("DB", "port", ui->app_port->text().toInt());
	core->setSetting("DB", "user", ui->app_user->text());
	core->setSetting("DB", "passwd", ui->app_pass->text());
	core->setSetting("DB", "db_name", ui->app_db->text());
    
    // infos sur le profile actuellement géré
    if(this->profile.getId() != 0)
        core->setSetting("Profile", "id", this->profile.getId());
}

void QfactureGui::restoreSettings()
{
	// infos sur la fenêtre (taille et position)
	resize(core->getSetting("Window", "size", QSize(400, 400)).toSize());
	move(core->getSetting("Window", "pos", QPoint(200, 200)).toPoint());
	
	// infos de connexion à la DB
	ui->app_server->setText(core->getSetting("DB", "host", "localhost").toString());
	ui->app_port->setText(core->getSetting("DB", "port", 3306).toString());
	ui->app_user->setText(core->getSetting("DB", "user", "qfacture").toString());
	ui->app_pass->setText(core->getSetting("DB", "passwd", "").toString());
	ui->app_db->setText(core->getSetting("DB", "db_name", "qfacture_db").toString());
}

void QfactureGui::loadLastProfile()
{
    QPixmap pic;
    
    this->profile = core->getProfile(core->getSetting("Profile", "id", QVariant(1)).toInt());
    
    if(this->profile.getId() == 0)
    {
        this->alert(trUtf8("Impossible de charger le profile utilisateur."));
        
        return;
    }
    
    /* Alimentation des widgets */
    ui->uName->setText(QString::fromStdString(this->profile.getName()));
    ui->uSiret->setText(QString::fromStdString(this->profile.getSiret()));
    ui->uAdress->setText(QString::fromStdString(this->profile.getAddress()));
    ui->uZip->setText(QString::fromStdString(this->profile.getZipCode()));
    ui->uCity->setText(QString::fromStdString(this->profile.getCity()));
    ui->uPhone->setText(QString::fromStdString(this->profile.getPhone()));
    ui->uMail->setText(QString::fromStdString(this->profile.getMail()));
    ui->uHome->setText(QString::fromStdString(this->profile.getWebsite()));
        
    /* Alimentation du widget logo */
    pic.loadFromData(this->profile.getLogo());
    ui->uLogo->setPixmap(pic);
}

/**
 * On ne fait que de la mise à jour de profile, donc si l'ID du profile courant
 * vaut 0 on ne sauvegarde pas.
 */ 
void QfactureGui::saveLoadedProfile()
{
    if(this->profile.getId() == 0)
        return;
    
    this->core->saveProfile(this->profile);
}

void QfactureGui::alert(const QString &message)
{
    QMessageBox::critical(this, trUtf8("Erreur !"), message);
}
