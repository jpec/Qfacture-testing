#include "productwidget.h"

#include <QMessageBox>


ProductWidget::ProductWidget(QfactureCore *ctrl, QWidget *parent) :
    QWidget(parent)
{
    this->ctrl = ctrl;

    this->buildLayout();
}

ProductWidget::~ProductWidget()
{
    delete layout;

    delete p_name;
    delete p_price;
    delete p_description;
}


void ProductWidget::buildLayout()
{
    // création des champs
    p_name = new QLineEdit(this);
    p_price = new QDoubleSpinBox(this);
    p_description = new QLineEdit(this);

    // définition des spécifications des widgets
    p_price->setRange(0, 999999.99);
    p_price->setSuffix(trUtf8(" €"));

    // création des layouts
    layout = new QFormLayout(this);

    // construction du formulaire
    layout->addRow(trUtf8("Nom"), p_name);
    layout->addRow(trUtf8("Prix"), p_price);
    layout->addRow(trUtf8("Description"), p_description);

    // mise en place des layouts
    layout->setLabelAlignment(Qt::AlignLeft);

    setLayout(layout);
}

void ProductWidget::loadProduct(int id)
{
    this->product = ctrl->getProduct(id);

    if(product.isNew()) {
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible de charger le produit."));

        return;
    }

    p_name->setText(product.getName());
    p_price->setValue(product.getPrice());
    p_description->setText(product.getDescription());

    emit productLoaded();
}

void ProductWidget::clearContent()
{
    product = Product();

    p_name->clear();
    p_price->setValue(0);
    p_description->clear();
}

void ProductWidget::setFocus()
{
    p_name->setFocus();
}

void ProductWidget::save()
{
    product.setName(p_name->text());
    product.setPrice(p_price->value());
    product.setDescription(p_description->text());

    if(!ctrl->save(product))
        QMessageBox::critical(this, trUtf8("Erreur !"),
                              trUtf8("Impossible d'enregistrer le produit."));
    else {
        emit productSaved();

        QMessageBox::information(this, trUtf8("Produit enregistré"),
                                 trUtf8("Le produit a été enregistré."));
    }
}

void ProductWidget::erase()
{
    QMessageBox msgBox;

    msgBox.setText(trUtf8("Voulez-vous vraiment supprimer ce produit ?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    int ret = msgBox.exec();

    if(ret == QMessageBox::No)
        return;

    if(product.getId() != 0) {
        if(ctrl->eraseProduct(product.getId())) {
            emit productDeleted(product.getId());

            QMessageBox::information(this, trUtf8("Produit supprimé"),
                                     trUtf8("Le profil a été supprimé."));
        }
        else
            QMessageBox::critical(this, trUtf8("Erreur !"),
                                  trUtf8("Impossible de supprimer le produit."));
    }

    clearContent();
}
