#include "qfacturegui.h"
#include "ui_qfacturegui.h"
#include "qfacturecore.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QFile>


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
    
    // charge le dernier profil chargé lors de la connexion à la DB
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(loadLastProfile()));

    // informe le programme que l'état de la connexion à la DB a changé
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnectionStateChanged()));
    this->connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBConnectionStateChanged()));
    
    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this, SLOT(onDBConnectionError(QString)));
    
    // lie l'évènement "DBError" à l'action correspondante
    this->connect(core, SIGNAL(DBError(QString)), this, SLOT(onDBError(QString)));
    
    // appelle la méthode chargée du changement de logo du profil courant
    this->connect(ui->uChangeLogo, SIGNAL(clicked()), this, SLOT(changeProfileLogo()));

    // affiche le profil dès qu'il est chargé
    this->connect(core, SIGNAL(lastProfileLoaded()), this, SLOT(displayCurrentProfile()));

    // enregistre le profil actuellement chargé à la demande de l'utilisateur
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

void QfactureGui::onDBConnectionError(const QString &error)
{
    alert(trUtf8("Une erreur est survenue lors de la connexion : %1").arg(error));
}

void QfactureGui::onDBError(const QString &error)
{
    alert(trUtf8("Une erreur SQL est survenue : %1").arg(error));
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
    if(this->core->getCurrentProfile().getId() != 0)
        core->setSetting("Profile", "id", this->core->getCurrentProfile().getId());
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
    if(this->core->loadLastProfile())
        return;

    this->alert(trUtf8("Impossible de charger le profile utilisateur."));
}

void QfactureGui::displayCurrentProfile()
{
    QPixmap pic;

    /* Alimentation des widgets */
    ui->uName->setText(this->core->getCurrentProfile().getName());
    ui->uSiret->setText(this->core->getCurrentProfile().getSiret());
    ui->uAdress->setText(this->core->getCurrentProfile().getAddress());
    ui->uZip->setText(this->core->getCurrentProfile().getZipCode());
    ui->uCity->setText(this->core->getCurrentProfile().getCity());
    ui->uPhone->setText(this->core->getCurrentProfile().getPhone());
    ui->uMail->setText(this->core->getCurrentProfile().getMail());
    ui->uHome->setText(this->core->getCurrentProfile().getWebsite());

    /* Alimentation du widget logo */
    pic.loadFromData(this->core->getCurrentProfile().getLogo());
    ui->uLogo->setPixmap(pic);
}

/**
 * On ne fait que de la mise à jour de profile, donc si l'ID du profile courant
 * vaut 0 on ne sauvegarde pas.
 */
void QfactureGui::saveLoadedProfile()
{
    if(this->core->getCurrentProfile().getId() == 0)
        return;

    this->core->getCurrentProfile().setName(ui->uName->text());
    this->core->getCurrentProfile().setSiret(ui->uSiret->text());
    this->core->getCurrentProfile().setAddress(ui->uAdress->text());
    this->core->getCurrentProfile().setZipCode(ui->uZip->text());
    this->core->getCurrentProfile().setCity(ui->uCity->text());
    this->core->getCurrentProfile().setPhone(ui->uPhone->text());
    this->core->getCurrentProfile().setMail(ui->uMail->text());
    this->core->getCurrentProfile().setWebsite(ui->uHome->text());

    if(this->core->saveProfile(this->core->getCurrentProfile()))
        ui->statusbar->showMessage(trUtf8("Profil enregistré."), 3000);
    else
        alert(trUtf8("Erreur à la sauvegarde du profil."));
}

void QfactureGui::changeProfileLogo()
{
    QString image;
    QPixmap img_pixmap;
    QFile img_file;

    /* Sélection du logo */
    image = QFileDialog::getOpenFileName(this, trUtf8("Qfacture - Importer un logo..."),
                                             "", trUtf8("Image Files (*.png *.jpg *.bmp)"));

    // pas d'image sélectionnée
    if(image.isNull())
        return;

    ui->uLogo->text().clear();

    /* Chargement de l'image */
    img_file.setFileName(image);
    if(!img_file.open(QIODevice::ReadOnly)) {
        alert(trUtf8("Impossible d'ouvrir le fichier contenant le logo !"));
        return;
    }

    /* Mise à jour du profil */
    this->core->getCurrentProfile().setLogo(img_file.readAll());

    /* Affichage de l'image */
    img_pixmap.load(image);
    ui->uLogo->setPixmap(img_pixmap);

    /* Fermeture du fichier */
    img_file.close();
}

void QfactureGui::alert(const QString &message)
{
    QMessageBox::critical(this, trUtf8("Erreur !"), message);
}
