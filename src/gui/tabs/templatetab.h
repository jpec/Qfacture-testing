#ifndef TEMPLATETAB_H
#define TEMPLATETAB_H

#include "qfacturecore.h"

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>

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

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;

    /**
     * Layout principal du widget
     */
    QVBoxLayout *layout;

};

#endif // TEMPLATETAB_H
