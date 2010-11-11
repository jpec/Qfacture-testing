#include "paramstab.h"

ParamsTab::ParamsTab(QfactureCore *core, QWidget *parent) : QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();
}

ParamsTab::~ParamsTab()
{
    delete layout;
    delete gbox_db_layout;
    delete gbox_profile_layout;

    delete w_db;
    delete w_profile;

    delete gbox_db;
    delete gbox_profile;
}


void ParamsTab::buildLayout()
{
    // construction des layouts
    layout = new QHBoxLayout(this);
    gbox_profile_layout = new QHBoxLayout();
    gbox_db_layout = new QHBoxLayout();

    // construction des widgets
    gbox_db = new QGroupBox(trUtf8("Base de données"), this);
    gbox_profile = new QGroupBox(trUtf8("Profil"), this);

    w_db = new DBWidget(core->getDBController(), gbox_db);
    w_profile = new ProfileWidget(gbox_profile);

    w_profile->setEnabled(false);

    // ajout des widgets aux layouts secondaires
    gbox_profile_layout->addWidget(w_profile);
    gbox_db_layout->addWidget(w_db);

    // ajout des layouts aux QGroupBox
    gbox_profile->setLayout(gbox_profile_layout);
    gbox_db->setLayout(gbox_db_layout);

    // ajout des QGroupBox au layout principal
    layout->addWidget(gbox_profile);
    layout->addWidget(gbox_db);
}

void ParamsTab::createActions()
{
    // informe le programme que l'état de la connexion à la DB a changé
    this->connect(core->getDBController(), SIGNAL(DBConnected()), this, SLOT(onDBConnectionStateChanged()));
    this->connect(core->getDBController(), SIGNAL(DBDisconnected()), this, SLOT(onDBConnectionStateChanged()));
}

void ParamsTab::onDBConnectionStateChanged()
{
    bool connexion_state = core->getDBController()->isDBConnected();

    w_profile->setEnabled(connexion_state);
    w_db->setEnabled(!connexion_state);
}
