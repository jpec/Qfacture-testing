#include "profilewidget.h"

ProfileWidget::ProfileWidget(QWidget *parent) : QWidget(parent)
{
    this->buildLayout();
}

ProfileWidget::~ProfileWidget()
{
    delete form_layout;
    delete layout;

    delete p_name;
    delete p_siret;
    delete p_address;
    delete p_zip;
    delete p_city;
    delete p_phone;
    delete p_mail;
    delete p_website;

    delete btn_ok;
}


void ProfileWidget::buildLayout()
{
    // création des champs
    p_name = new QLineEdit(this);
    p_siret = new QLineEdit(this);
    p_address = new QLineEdit(this);
    p_zip = new QLineEdit(this);
    p_city = new QLineEdit(this);
    p_phone = new QLineEdit(this);
    p_mail = new QLineEdit(this);
    p_website = new QLineEdit(this);

    btn_ok = new QPushButton(trUtf8("Enregistrer"), this);

    // création des layouts
    layout = new QVBoxLayout(this);
    form_layout = new QFormLayout();

    // définition des particularités de certains champs
    p_siret->setInputMask("999 999 999 99999");

    // construction du formulaire
    form_layout->addRow(trUtf8("Raison sociale"), p_name);
    form_layout->addRow(trUtf8("SIRET"), p_siret);
    form_layout->addRow(trUtf8("Adresse"), p_address);
    form_layout->addRow(trUtf8("Code postal"), p_zip);
    form_layout->addRow(trUtf8("Ville"), p_city);
    form_layout->addRow(trUtf8("Téléphone"), p_phone);
    form_layout->addRow(trUtf8("Email"), p_mail);
    form_layout->addRow(trUtf8("Site internet"), p_website);

    // mise en place des layouts
    form_layout->setLabelAlignment(Qt::AlignLeft);

    layout->addLayout(form_layout);
    layout->addWidget(btn_ok);
    layout->addStretch(); // pour forcer le bouton à être collé au formulaire

    setLayout(layout);
}
