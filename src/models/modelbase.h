#ifndef MODELBASE_H
#define MODELBASE_H

class ModelBase
{
public:
    /**
     * Indique si l'objet est nouveau
     */
    bool isNew() const;

    /**
     * Retourne l'identiant de l'objet.
     *
     * @return int L'identifiant, ou 0 s'il n'est pas définit.
     */
    virtual int getId() const = 0;
};

#endif // MODELBASE_H
