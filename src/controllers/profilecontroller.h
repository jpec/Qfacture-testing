#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include "managers/profilemanager.h"


/**
 * Contrôleur permettant de gérer les profils
 */
class ProfileController
{
    friend class QfactureCore;

private:
    /**
     * Retourne une instance unique du contrôleur
     *
     * @return ProfileController* L'instance du contrôleur
     */
    static ProfileController* getInstance();

    ~ProfileController();

    /**
     * Charge le dernier profil utilisé
     */
    bool loadLastProfile();

    /**
     * Retourne le profil de l'auto-entrepreneur actuellement chargé.
     *
     * @return Profile& Le profil.
     */
    Profile& getCurrent();

    /**
     * Enregistre ou met à jour le profile d'un utilisateur.
     *
     * \note En cas d'un nouveau profile, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le profile à enregistrer
     */
    bool save(Profile &p);

    /**
     * Récupère le profile d'un utilisateur
     *
     * @param id L'identifiant du profile à utiliser
     *
     * @return Profile Le profile chargé.
     */
    Profile get(int id);

    /**
     * Enregistre le profil actuellement chargé (s'il y en a un)
     *
     * @see save
     */
    bool saveCurrent();


    /**
     * Pour avoir un singleton
     */
    ProfileController();
    ProfileController(const ProfileController&);
    ProfileController& operator =(const ProfileController&);

    /**
     * Instance du gestionnaire de profiles
     */
    ProfileManager profile_manager;

    /**
     * Profil de l'auto-entrepreneur actuellement chargé.
     */
    Profile profile;
};

#endif // PROFILECONTROLLER_H
