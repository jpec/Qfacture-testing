#ifndef PROFILECONTROLLER_H
#define PROFILECONTROLLER_H

#include "controller.h"
#include "models/profile.h"
#include "managers/profilemanager.h"


/**
 * Contrôleur permettant de gérer les profils
 */
class ProfileController : public Controller
{
    Q_OBJECT

public:
    explicit ProfileController(QObject *parent = 0);
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

public slots:
    /**
     * Enregistre le profil actuellement chargé (s'il y en a un)
     *
     * @see save
     */
    bool saveCurrent();

signals:
    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     *
     * @param error Le message d'erreur retourné
     */
    void DBError(const QString &error);

    /**
     * Émit après la connexion à la DB, lorsque le profil de
     * l'utilisateur a été chargé.
     */
    void lastProfileLoaded();

private:

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