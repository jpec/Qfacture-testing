#include "profilewidget.h"

#include <QPixmap>
#include <QMessageBox>


ProfileWidget::ProfileWidget(ProfileController *ctrl, QWidget *parent) : QWidget(parent)
{
    this->ctrl_profile = ctrl;

    this->buildLayout();
    this->createActions();
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
    p_phone->setInputMask("99 99 99 99 99");

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

void ProfileWidget::createActions()
{
    // affiche le profil dès qu'il est chargé
    this->connect(ctrl_profile, SIGNAL(lastProfileLoaded()), this, SLOT(displayCurrentProfile()));

    // sauvegarde le profil chargé lors du clic sur le bouton enregistrer
    this->connect(btn_ok, SIGNAL(clicked()), this, SLOT(save()));
}

void ProfileWidget::clearContent()
{
    p_name->clear();
    p_siret->clear();
    p_address->clear();
    p_zip->clear();
    p_city->clear();
    p_phone->clear();
    p_mail->clear();
    p_website->clear();
}

void ProfileWidget::loadLastProfile()
{
    if(this->ctrl_profile->loadLastProfile())
        return;

    QMessageBox::critical(this, trUtf8("Erreur !"), trUtf8("Impossible de charger le profil utilisateur."));
}

void ProfileWidget::displayCurrentProfile()
{
    QPixmap pic;

    /* Alimentation des widgets */
    p_name->setText(this->ctrl_profile->getCurrent().getName());
    p_siret->setText(this->ctrl_profile->getCurrent().getSiret());
    p_address->setText(this->ctrl_profile->getCurrent().getAddress());
    p_zip->setText(this->ctrl_profile->getCurrent().getZipCode());
    p_city->setText(this->ctrl_profile->getCurrent().getCity());
    p_phone->setText(this->ctrl_profile->getCurrent().getPhone());
    p_mail->setText(this->ctrl_profile->getCurrent().getMail());
    p_website->setText(this->ctrl_profile->getCurrent().getWebsite());

    /* Alimentation du widget logo */
    pic.loadFromData(this->ctrl_profile->getCurrent().getLogo());
    //p_logo->setPixmap(pic);
}

void ProfileWidget::save()
{
    this->ctrl_profile->getCurrent().setName(p_name->text());
    this->ctrl_profile->getCurrent().setSiret(p_siret->text());
    this->ctrl_profile->getCurrent().setAddress(p_address->text());
    this->ctrl_profile->getCurrent().setZipCode(p_zip->text());
    this->ctrl_profile->getCurrent().setCity(p_city->text());
    this->ctrl_profile->getCurrent().setPhone(p_phone->text());
    this->ctrl_profile->getCurrent().setMail(p_mail->text());
    this->ctrl_profile->getCurrent().setWebsite(p_website->text());

    if(ctrl_profile->saveCurrent())
        QMessageBox::information(this, trUtf8("Profil enregistré"), trUtf8("Le profil a été enregistré."));
    else
        QMessageBox::critical(this, trUtf8("Erreur !"), trUtf8("Impossible d'enregistrer le profil utilisateur."));
}
