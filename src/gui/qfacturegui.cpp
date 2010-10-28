#include "qfacturegui.h"
#include "ui_qfacturegui.h"
#include "qfacturecore.h"

#include <QMessageBox>


QfactureGui::QfactureGui(QfactureCore *core, QWidget *parent) : QMainWindow(parent), ui(new Ui::QfactureGui)
{
    ui->setupUi(this);
    this->core = core;
    
    this->setupActions();
}

QfactureGui::~QfactureGui()
{
    delete ui;
}

void QfactureGui::setupActions()
{
    // appelle la méthode de connexion à la DB lors du clic sur le bouton
    this->connect(ui->app_connect, SIGNAL(clicked()), this, SLOT(handleDBConnection()));
    
    // lie l'évènement "DBConnected" à l'action correspondante
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnected()));
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnectionStateChanged()));

    // lie l'évènement "DBDisconnected" à l'action correspondante
    this->connect(core, SIGNAL(DBDisconnected()), this, SLOT(onDBConnectionStateChanged()));    
    
    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this, SLOT(onDBConnectionError(QString)));
}

/**
 * Si on est déjà connecté à la DB, on lance la déconnexion, sinon on lance la
 * connexion
 */ 
void QfactureGui::handleDBConnection()
{
    if(core->isDBConnected())
        core->deconnectDB();
    else
        core->connectDB(ui->app_server->text(), ui->app_port->text().toInt(), ui->app_user->text(),
                        ui->app_pass->text(), ui->app_db->text());
}

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
    QMessageBox::warning(this, "Qfacture", trUtf8("OK !"), QMessageBox::Ok);
}

void QfactureGui::onDBConnectionError(const QString &error)
{
    QMessageBox::warning(this, "Qfacture", trUtf8("Une erreur est survenue lors de la connexion : %1").arg(error),
                         QMessageBox::Ok);
}
