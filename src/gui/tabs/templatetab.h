#ifndef TEMPLATETAB_H
#define TEMPLATETAB_H

#include "qfacturecore.h"

#include <QTextEdit>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>


class TemplateTab : public QWidget
{
    Q_OBJECT
public:
    explicit TemplateTab(QfactureCore *core, QWidget *parent = 0);
    ~TemplateTab();


public slots:
    /**
     * (Dés)active l'onglet
     *
     * @param state État d'activation de l'onglet
     */
    void setEnabled(bool state=true);   

private slots:

    void onNewClicked();

    void onOpenClicked();

    void onDelClicked();

private:
    /**
     * Construit la GUI de l'onglet
     */
    void buildLayout();

    /**
     * Cette méthode, appelée par le constructeur, s'occupe de connecter les
     * principaux évènements.
     */
    void createActions();

    void buildActionButtons();

    void buildTemplateEdition();

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;

    /**
     * Layout principal du widget
     */
    QVBoxLayout *layout;

    /**
     * Layout contenant le template
     */
    QVBoxLayout *template_layout;

    /**
     * Layout contenant les boutons nouveau, sauvegarder et supprimer
     */
    QHBoxLayout *actions_layout;

    /**
     * Groupbox servant de conteneur pour la liste des actions
     */
    QGroupBox *gbox_actions;

    /**
     * Groupbox servant de conteneur pour le template
     */
    QGroupBox *gbox_template;

    /**
     * Bouton "Nouvelle facture"
     */
    QPushButton *btn_new;

    /**
     * Bouton "Ouvrir facture"
     */
    QPushButton *btn_open;

    /**
     * Bouton "Supprimer facture"
     */
    QPushButton *btn_del;

    QTextEdit *ed_template;
    QComboBox *cb_template;

};

#endif // TEMPLATETAB_H
