#ifndef DOCUMENTTYPE_H
#define DOCUMENTTYPE_H

#include "models/customer.h"


class DocumentType : public ModelBase
{
public:
    DocumentType();

    /**
     * Définit l'identifiant de ce type.
     *
     * \warning Ce n'est possible que s'il n'a pas déjà été défini.
     *
     * @param id L'identifiant à associer au type de document.
     */
    void setId(int id);

    /**
     * Retourne l'identiant de ce type.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    int getId() const;

    /**
     * Définit le nom de ce type de document.
     *
     * @param name Le nouveau nom
     */
    void setName(const QString &name);

    /**
     * Retourne le nom de ce type de document.
     *
     * @return QString Le nom.
     */
    QString getName() const;

private:
    /**
     * Identifiant du type
     */
    int id;

    /**
     * Nom du type
     */
    QString name;
};

#endif // DOCUMENTTYPE_H
