#ifndef BASEMANAGER_H
#define BASEMANAGER_H

#include <QString>


class BaseManager
{
public:
    /**
     * Dit si une erreur est survenue
     *
     * @return bool
     */
    bool hasError() const;

    /**
     * Retourne le message d'erreur de la dernière erreur
     * survenue.
     *
     * @return QString le message d'erreur.
     */
    QString getLastErrorMessage() const;

    /**
     * Retourne le code SQL de la requête ayant causé la dernière
     * erreur.
     *
     * @return QString Le code SQL
     */
    QString getLastErrorQuery() const;

protected:
    /**
     * Définit lors d'une erreur le message d'erreur et le
     * code SQL de la requête l'ayant causé.
     *
     * @param message Le message d'erreur retourné.
     * @param sql Le code SQL ayant de la requête à problème.
     */
    void setError(const QString &message, const QString &sql);

private:
    /**
     * Texte du dernier message d'erreur survenu
     */
    QString error_msg;

    /**
     * Code SQL de la requête ayant causé la dernière erreur.
     */
    QString error_query;
};

#endif // BASEMANAGER_H
