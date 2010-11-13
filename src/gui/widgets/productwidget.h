#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include "controllers/productcontroller.h"

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QDoubleSpinBox>


/**
 * Formulaire permettant la saisie d'un produit
 */
class ProductWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductWidget(ProductController *ctrl, QWidget *parent = 0);
    ~ProductWidget();

signals:
    /**
     * Émit lorsqu'un produit a été sauvegardé
     */
    void productSaved();

    /**
     * Émit lorsqu'un produit a été chargé.
     */
    void productLoaded();

    /**
     * Émit lorsqu'un produit a été enregistré
     */
    void productDeleted(int id);

public slots:
    /**
     * Vide le contenu du formulaire.
     */
    void clearContent();

    /**
     * Sauvegarde le profil actuellement chargé.
     */
    void save();

    /**
     * supprime le profil actuellement chargé.
     */
    void erase();

    /**
     * Charge le profil d'un produit.
     *
     * @param id Identifiant du produit
     */
    void loadProduct(int id);

private:
    /**
     * Construit le layout du formulaire
     */
    void buildLayout();


    /**
     * Pointeur vers le contrôleur des profils.
     */
    ProductController *ctrl_product;

    /**
     * Layout permettant de créer facilement des formulaires
     */
    QFormLayout *layout;

    /**
     * Champ texte pour le nom du produit
     */
    QLineEdit *p_name;

    /**
     * Champ pour le prix
     */
    QDoubleSpinBox *p_price;

    /**
     * Champ texte pour la description
     */
    QLineEdit *p_description;

    /**
     * Produit actuellement affiché
     */
    Product product;
};

#endif // PRODUCTWIDGET_H
