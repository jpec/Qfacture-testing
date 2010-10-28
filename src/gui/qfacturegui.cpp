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
    this->connect(ui->app_connect, SIGNAL(clicked()), this, SLOT(DBConnect()));
    
    // lie l'évènement "DBConnected" à l'action correspondante
    this->connect(core, SIGNAL(DBConnected()), this, SLOT(onDBConnected()));
    
    // lie l'évènement "DBConnectionError" à l'action correspondante
    this->connect(core, SIGNAL(DBConnectionError(QString)), this, SLOT(onDBConnectionError(QString)));
}

void QfactureGui::DBConnect()
{
    core->connectDB(ui->app_server->text(), ui->app_port->text().toInt(), ui->app_user->text(),
                    ui->app_pass->text(), ui->app_db->text());
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
