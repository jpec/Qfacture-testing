#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "managers/manager.h"
#include "models/profile.h"


/**
 * Classe permettant la gestion des profiles d'utilisateurs
 */
class ProfileManager : public Manager
{
public:
    ProfileManager(QSqlDatabase &db);
    
    /**
     * Récupère le profile d'un utilisateur
     *
     * @param id L'identifiant du profile à utiliser
     *
     * @return Profile Le profile chargé.
     */
    Profile get(int id);
};

#endif // PROFILEMANAGER_H
