#ifndef ParamsTab_H
#define ParamsTab_H

#include "qfacturecore.h"
#include "gui/widgets/profilewidget.h"
#include "gui/widgets/dbwidget.h"

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>


/**
 * Onglet paramètres
 */
class ParamsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParamsTab(QfactureCore *core, QWidget *parent = 0);
    ~ParamsTab();

private slots:
    /**
     * Appelé lorsque l'état de connexion à la DB change. Elle
     * s'occupe de (dés)activer certains widgets
     */
    void onDBConnectionStateChanged();

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

    ProfileWidget *w_profile;
    DBWidget *w_db;

    QHBoxLayout *layout;
    QHBoxLayout *gbox_profile_layout;
    QHBoxLayout *gbox_db_layout;

    QGroupBox *gbox_profile;
    QGroupBox *gbox_db;
};

#endif // ParamsTab_H
