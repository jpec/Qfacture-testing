#ifndef QFACTURECORE_H
#define QFACTURECORE_H


#include <QHash>
#include <QObject>
#include <QSettings>


/**
 * Fait office de contrôleur géant (qui ne fait rien pour le moment) et sera
 * utilisé par la GUI.
 */
class QfactureCore : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructeur du core : pas très utile pour le moment ...
     */
    QfactureCore();

    /**
     * Retourne le numéro de version du logiciel.
     *
     * \todo Déplacer la définition du n° ailleurs (fichier dédié ?).
     */
    QString version() const { return "1.0 testing"; }
};

#endif // QFACTURECORE_H
