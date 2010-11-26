#include "dbwidget.h"
#include "managers/settingsmanager.h"

#include <QMessageBox>


DBWidget::DBWidget(QfactureCore *ctrl, QWidget *parent) : QWidget(parent)
{
    this->ctrl = ctrl;

    this->buildWidgets();
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


void DBWidget::buildWidgets()
{
    // création des widgets
    btn_ok = new QPushButton(trUtf8("Connexion"));
    db_host = new QLineEdit();
    db_port = new QSpinBox();
    db_login = new QLineEdit();
    db_pass = new QLineEdit();
    db_base = new QLineEdit();
    db_type = new QComboBox();

    // config des widgets
    db_port->setMaximum(65535);
    db_type->addItems(ctrl->getAvailableDrivers());
    db_pass->setEchoMode(QLineEdit::Password);
}

void DBWidget::buildLayout()
{
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
}

void DBWidget::createActions()
{
    // appelle la méthode de connexion à la DB lors du clic sur le bouton
    this->connect(btn_ok, SIGNAL(clicked()), this, SLOT(handleDBConnection()));

    this->connect(db_type, SIGNAL(currentIndexChanged(QString)), this,
                  SLOT(onCurrentDBTypeChanged(QString)));
}

void DBWidget::onCurrentDBTypeChanged(const QString &type)
{
    bool sqlite = "QSQLITE" == type;

    db_host->setEnabled(!sqlite);
    db_port->setEnabled(!sqlite);
    db_login->setEnabled(!sqlite);
    db_pass->setEnabled(!sqlite);
}

/**
 * Si on est déjà connecté à la DB, on lance la déconnexion, sinon on lance la
 * connexion
 */
void DBWidget::handleDBConnection()
{
    if(ctrl->isDBConnected())
        ctrl->disconnectDB();
    else
        ctrl->connectDB(db_host->text(), db_port->text().toInt(), db_login->text(),
                        db_pass->text(), db_base->text(), db_type->currentText());
}

void DBWidget::setEnabled(bool enabled)
{
    btn_ok->setText(!enabled ? trUtf8("Déconnexion") : trUtf8("Connexion"));

    db_type->setEnabled(enabled);
    db_host->setEnabled(enabled);
    db_port->setEnabled(enabled);
    db_login->setEnabled(enabled);
    db_pass->setEnabled(enabled);
    db_base->setEnabled(enabled);
}

void DBWidget::saveSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    settings.set("DB", "host", db_host->text());
    settings.set("DB", "port", db_port->text().toInt());
    settings.set("DB", "login", db_login->text());
    settings.set("DB", "pass", db_pass->text());
    settings.set("DB", "base", db_base->text());
    settings.set("DB", "type", db_type->currentIndex());
}

void DBWidget::restoreSettings()
{
    SettingsManager &settings = SettingsManager::getInstance();

    db_host->setText(settings.get("DB", "host", "localhost").toString());
    db_port->setValue(settings.get("DB", "port", 3306).toInt());
    db_login->setText(settings.get("DB", "login", "qfacture").toString());
    db_pass->setText(settings.get("DB", "pass", "").toString());
    db_base->setText(settings.get("DB", "base", "qfacture_db").toString());

    db_type->setCurrentIndex(settings.get("DB", "type", 0).toInt());

    // alors que normalement la ligne précédente devrait déclencher ça automatiquement ...
    onCurrentDBTypeChanged(db_type->currentText());
}
