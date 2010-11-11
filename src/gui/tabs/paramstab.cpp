#include "paramstab.h"
#include "gui/widgets/profilewidget.h"
#include "gui/widgets/dbwidget.h"


ParamsTab::ParamsTab(QWidget *parent) : QWidget(parent)
{
    this->buildLayout();
}

ParamsTab::~ParamsTab()
{
    delete layout;
    delete gbox_db_layout;
    delete gbox_profile_layout;

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

    // ajout des widgets aux layouts secondaires
    gbox_profile_layout->addWidget(new ProfileWidget(gbox_profile));
    gbox_db_layout->addWidget(new DBWidget(gbox_db));

    // ajout des layouts aux QGroupBox
    gbox_profile->setLayout(gbox_profile_layout);
    gbox_db->setLayout(gbox_db_layout);

    // ajout des QGroupBox au layout principal
    layout->addWidget(gbox_profile);
    layout->addWidget(gbox_db);
}
