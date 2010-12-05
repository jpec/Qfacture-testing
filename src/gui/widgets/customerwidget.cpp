#include "customerwidget.h"

#include <QMessageBox>


CustomerWidget::CustomerWidget(QfactureCore *ctrl, QWidget *parent) :
    QWidget(parent)
{
    this->ctrl = ctrl;

    this->buildLayout();
}

CustomerWidget::~CustomerWidget()
{
    delete layout;

    delete c_name;
    delete c_address;
    delete c_complement;
    delete c_zip;
    delete c_city;
    delete c_phone;
    delete c_mail;
}


void CustomerWidget::buildLayout()
{
    // création des champs
    c_name = new QLineEdit(this);
    c_address = new QLineEdit(this);
    c_complement = new QLineEdit(this);
    c_zip = new QLineEdit(this);
    c_city = new QLineEdit(this);
    c_phone = new QLineEdit(this);
    c_mail = new QLineEdit(this);

    // création des layouts
    layout = new QFormLayout(this);

    // définition des particularités de certains champs
    c_phone->setInputMask("99 99 99 99 99");

    // construction du formulaire
    layout->addRow(trUtf8("Nom"), c_name);
    layout->addRow(trUtf8("Adresse"), c_address);
    layout->addRow(trUtf8("Complément"), c_complement);
    layout->addRow(trUtf8("Code postal"), c_zip);
    layout->addRow(trUtf8("Ville"), c_city);
    layout->addRow(trUtf8("Téléphone"), c_phone);
    layout->addRow(trUtf8("Email"), c_mail);

    // mise en place des layouts
    layout->setLabelAlignment(Qt::AlignLeft);

    setLayout(layout);
}

void CustomerWidget::loadCustomer(int id)
{
    this->customer = ctrl->getCustomer(id);

    if(customer.getId() == 0) {
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible de charger le client."));

        return;
    }

    c_name->setText(customer.getName());
    c_address->setText(customer.getAddress());
    c_complement->setText(customer.getAddressComplement());
    c_zip->setText(customer.getZipCode());
    c_city->setText(customer.getCity());
    c_phone->setText(customer.getPhone());
    c_mail->setText(customer.getMail());

    emit customerLoaded();
}

void CustomerWidget::clearContent()
{
    customer = Customer();

    c_name->clear();
    c_address->clear();
    c_complement->clear();
    c_zip->clear();
    c_city->clear();
    c_phone->clear();
    c_mail->clear();
}

void CustomerWidget::setFocus()
{
    c_name->setFocus();
}

void CustomerWidget::save()
{
    customer.setName(c_name->text());
    customer.setAddress(c_address->text());
    customer.setAddressComplement(c_complement->text());
    customer.setZipCode(c_zip->text());
    customer.setCity(c_city->text());
    customer.setPhone(c_phone->text());
    customer.setMail(c_mail->text());

    if(!ctrl->save(customer))
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible d'enregistrer le client."));
    else {
        emit customerSaved();

        QMessageBox::information(this, trUtf8("Client enregistré"),
                                 trUtf8("Le profil a été enregistré."));
    }
}

void CustomerWidget::erase()
{
    QMessageBox msgBox;

    msgBox.setText(trUtf8("Voulez-vous vraiment supprimer ce client ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if(ret == QMessageBox::No)
        return;

    if(customer.getId() != 0) {
        if(ctrl->eraseCustomer(customer.getId())) {
            emit customerDeleted(customer.getId());

            QMessageBox::information(this, trUtf8("Client supprime"),
                                     trUtf8("Le profil a été supprimé."));
        }
        else
            QMessageBox::critical(this, trUtf8("Erreur !"),
                                  trUtf8("Impossible de supprimer le client."));
    }

    clearContent();
}
