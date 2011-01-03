#include "profilewidget.h"

#include <QFile>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>


ProfileWidget::ProfileWidget(QfactureCore *ctrl, QWidget *parent) : QWidget(parent)
{
    this->ctrl = ctrl;

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
    delete p_complement;
    delete p_zip;
    delete p_city;
    delete p_phone;
    delete p_mail;
    delete p_website;
    delete p_logo;

    delete btn_logo;
    delete btn_ok;
}


void ProfileWidget::buildLayout()
{
    // création des champs
    p_name = new QLineEdit();
    p_siret = new QLineEdit();
    p_address = new QLineEdit();
    p_complement = new QLineEdit();
    p_zip = new QLineEdit();
    p_city = new QLineEdit();
    p_phone = new QLineEdit();
    p_mail = new QLineEdit();
    p_website = new QLineEdit();
    p_logo = new QLabel(trUtf8("Aucun logo sélectionné."));

    btn_logo = new QPushButton(trUtf8("Changer de logo"));
    btn_ok = new QPushButton(trUtf8("Enregistrer"));

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
    form_layout->addRow(trUtf8("Complément"), p_complement);
    form_layout->addRow(trUtf8("Code postal"), p_zip);
    form_layout->addRow(trUtf8("Ville"), p_city);
    form_layout->addRow(trUtf8("Téléphone"), p_phone);
    form_layout->addRow(trUtf8("Email"), p_mail);
    form_layout->addRow(trUtf8("Site internet"), p_website);

    // mise en place des layouts
    form_layout->setLabelAlignment(Qt::AlignLeft);

    layout->addLayout(form_layout);
    layout->addWidget(btn_logo);
    layout->addWidget(btn_ok);

    layout->addStretch();

    layout->addWidget(p_logo);

    layout->addStretch();

    setLayout(layout);
}

void ProfileWidget::createActions()
{
    // affiche le profil dès qu'il est chargé
    this->connect(ctrl, SIGNAL(lastProfileLoaded()), this,
                  SLOT(displayCurrentProfile()));

    // propose de choisir un logo lors du cloc sur le bouton
    this->connect(btn_logo, SIGNAL(clicked()), this, SLOT(changeLogo()));

    // sauvegarde le profil chargé lors du clic sur le bouton enregistrer
    this->connect(btn_ok, SIGNAL(clicked()), this, SLOT(save()));
}

void ProfileWidget::clearContent()
{
    p_name->clear();
    p_siret->clear();
    p_address->clear();
    p_complement->clear();
    p_zip->clear();
    p_city->clear();
    p_phone->clear();
    p_mail->clear();
    p_website->clear();
    p_logo->clear();
}

void ProfileWidget::loadLastProfile()
{
    if(this->ctrl->loadLastProfile())
        return;

    QMessageBox::critical(this, trUtf8("Erreur !"),
                          trUtf8("Impossible de charger le profil utilisateur."));
}

void ProfileWidget::displayCurrentProfile()
{
    QPixmap pic;

    /* Alimentation des widgets */
    p_name->setText(this->ctrl->getCurrentProfile().getName());
    p_siret->setText(this->ctrl->getCurrentProfile().getSiret());
    p_address->setText(this->ctrl->getCurrentProfile().getAddress());
    p_complement->setText(this->ctrl->getCurrentProfile().getAddressComplement());
    p_zip->setText(this->ctrl->getCurrentProfile().getZipCode());
    p_city->setText(this->ctrl->getCurrentProfile().getCity());
    p_phone->setText(this->ctrl->getCurrentProfile().getPhone());
    p_mail->setText(this->ctrl->getCurrentProfile().getMail());
    p_website->setText(this->ctrl->getCurrentProfile().getWebsite());

    /* Alimentation du widget logo */
    pic.loadFromData(this->ctrl->getCurrentProfile().getLogo());
    p_logo->setPixmap(pic);
}

void ProfileWidget::changeLogo()
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

    p_logo->clear();

    /* Chargement de l'image */
    img_file.setFileName(image);
    if(!img_file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible d'ouvrir le fichier contenant le logo !"));
        return;
    }

    /* Mise à jour du profil */
    this->ctrl->getCurrentProfile().setLogo(img_file.readAll());

    /* Affichage de l'image */
    img_pixmap.load(image);
    p_logo->setPixmap(img_pixmap);

    /* Fermeture du fichier */
    img_file.close();
}

void ProfileWidget::save()
{
    this->ctrl->getCurrentProfile().setName(p_name->text());
    this->ctrl->getCurrentProfile().setSiret(p_siret->text());
    this->ctrl->getCurrentProfile().setAddress(p_address->text());
    this->ctrl->getCurrentProfile().setAddressComplement(p_complement->text());
    this->ctrl->getCurrentProfile().setZipCode(p_zip->text());
    this->ctrl->getCurrentProfile().setCity(p_city->text());
    this->ctrl->getCurrentProfile().setPhone(p_phone->text());
    this->ctrl->getCurrentProfile().setMail(p_mail->text());
    this->ctrl->getCurrentProfile().setWebsite(p_website->text());

    if(ctrl->saveCurrentProfile())
        QMessageBox::information(this, trUtf8("Profil enregistré"),
                                 trUtf8("Le profil a été enregistré."));
    else
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible d'enregistrer le profil utilisateur."));
}
