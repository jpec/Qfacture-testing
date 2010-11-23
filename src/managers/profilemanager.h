#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "models/profile.h"

#include <QSqlQuery>


/**
 * Classe permettant la gestion des profils d'utilisateurs
 */
class ProfileManager
{
public:
    /**
     * Récupère le profil d'un utilisateur
     *
     * @param id L'identifiant du profil à utiliser
     *
     * @throws DBErrorException Si la requête à la DB échoue
     *
     * @return Profile Le profil chargé.
     */
    Profile get(int id);

    /**
     * Enregistre ou met à jour le profil d'un utilisateur.
     *
     * \note En cas d'un nouveau profil, l'id est renseigné lors de l'enregistrement
     *
     * @param p Le profil à enregistrer
     *
     * @return bool Succès de l'enregistrement
     */
    bool save(Profile &profile);

private:
    /**
     * Crée un profil à partir des résultats d'une requête
     *
     * \note On suppose que tous les champs d'un profil sont
     *       retournés par la requête
     *
     * @param query La requête qui vient d'être exécutée
     *
     * @return Profile Le profil créé
     */
    Profile makeProfile(QSqlQuery &query);

    /**
     * Réalise l'enregistrement d'un nouveau profil
     *
     * \note l'id est renseigné ici.
     *
     * @param profile Le profil à enregistrer
     *
     * @return bool Succès de l'insertion
     */
    bool insert(Profile &profile);

    /**
     * Réalise la mise à jour d'un profil
     *
     * @param profile Le profil à mettre à jour
     *
     * @return bool Succès de la mise à jour
     */
    bool update(const Profile &profile);

    /**
     * Effectue un bindValue() sur la query avec les champs du
     * profil.
     *
     * @param profile Profile à binder
     * @param query Query à laquelle lier le profil
     */
    void bindProfile(const Profile &profile, QSqlQuery &query);
};

#endif // PROFILEMANAGER_H
