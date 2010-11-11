#include "dbwidget.h"
#include "qfacturecore.h"

#include <QMessageBox>


DBWidget::DBWidget(DBController *db_ctrl, QWidget *parent) : QWidget(parent)
{
    this->db_ctrl = db_ctrl;

    this->buildLayout();
    this->createActions();

    this->restoreSettings();
}

DBWidget::~DBWidget()
{
    this->saveSettings();

    delete form_layout;
    delete layout;

    delete db_type;
    delete db_host;
    delete db_port;
    delete db_login;
    delete db_pass;
    delete db_base;

    delete btn_ok;
}


void DBWidget::buildLayout()
{
    // création des widgets
    btn_ok = new QPushButton(trUtf8("Connexion"), this);
    db_host = new QLineEdit(this);
    db_port = new QSpinBox(this);
    db_login = new QLineEdit(this);
    db_pass = new QLineEdit(this);
    db_base = new QLineEdit(this);
    db_type = new QComboBox(this);

    // config des widgets
    db_port->setMaximum(65535);
    db_type->addItems(db_ctrl->getAvailableDrivers());

    // création des layouts
    layout = new QVBoxLayout(this);
    form_layout = new QFormLayout();

    // construction du formulaire
    form_layout->addRow(trUtf8("Type"), db_type);
    form_layout->addRow(trUtf8("Hôte"), db_host);
    form_layout->addRow(trUtf8("Port"), db_port);
    form_layout->addRow(trUtf8("Utilisateur"), db_login);
    form_layout->addRow(trUtf8("Mot de passe"), db_pass);
    form_layout->addRow(trUtf8("Base"), db_base);

    // mise en place des layouts
    form_layout->setLabelAlignment(Qt::AlignLeft);

    layout->addLayout(form_layout);
    layout->addWidget(btn_ok);
    layout->addStretch(); // pour forcer le bouton à être collé au formulaire

    setLayout(layout);
}

void DBWidget::createActions()
{
    // appelle la méthode de connexion à la DB lors du clic sur le bouton
    this->connect(btn_ok, SIGNAL(clicked()), this, SLOT(handleDBConnection()));
}

/**
 * Si on est déjà connecté à la DB, on lance la déconnexion, sinon on lance la
 * connexion
 */
void DBWidget::handleDBConnection()
{
    if(db_ctrl->isDBConnected())
        db_ctrl->disconnectDB();
    else
        db_ctrl->connectDB(db_host->text(), db_port->text().toInt(), db_login->text(),
                           db_pass->text(), db_base->text(), db_type->currentText());
}

void DBWidget::setEnabled(bool enabled)
{
    btn_ok->setText(!enabled ? trUtf8("Déconnexion") : trUtf8("Connexion"));
    db_host->setEnabled(enabled);
    db_port->setEnabled(enabled);
    db_login->setEnabled(enabled);
    db_pass->setEnabled(enabled);
    db_base->setEnabled(enabled);
}

void DBWidget::saveSettings()
{
    db_ctrl->getCore()->setSetting("DB", "host", db_host->text());
    db_ctrl->getCore()->setSetting("DB", "port", db_port->text().toInt());
    db_ctrl->getCore()->setSetting("DB", "login", db_login->text());
    db_ctrl->getCore()->setSetting("DB", "pass", db_pass->text());
    db_ctrl->getCore()->setSetting("DB", "base", db_base->text());
    db_ctrl->getCore()->setSetting("DB", "type", db_type->currentIndex());
}

void DBWidget::restoreSettings()
{
    db_host->setText(db_ctrl->getCore()->getSetting("DB", "host", "localhost").toString());
    db_port->setValue(db_ctrl->getCore()->getSetting("DB", "port", 3306).toInt());
    db_login->setText(db_ctrl->getCore()->getSetting("DB", "login", "qfacture").toString());
    db_pass->setText(db_ctrl->getCore()->getSetting("DB", "pass", "").toString());
    db_base->setText(db_ctrl->getCore()->getSetting("DB", "base", "qfacture_db").toString());

    db_type->setCurrentIndex(db_ctrl->getCore()->getSetting("DB", "type", 0).toInt());
}
