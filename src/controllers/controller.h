#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>


/**
 * Classe servant de base à tous le contrôleurs
 */
class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = 0);
};

#endif // CONTROLLER_H
