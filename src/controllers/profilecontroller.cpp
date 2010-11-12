#include "profilecontroller.h"
#include "managers/settingsmanager.h"

#include <QVariant>


ProfileController::ProfileController(QObject *parent) : Controller(parent)
{
}

ProfileController::~ProfileController()
{
    SettingsManager &settings = SettingsManager::getInstance();

    if(this->profile.getId() != 0)
        settings.set("Profile", "id", this->profile.getId());
}

Profile ProfileController::getProfile(int id)
{
    Profile p = profile_manager.get(id);

    if(profile_manager.hasError())
        emit DBError(profile_manager.getLastErrorMessage());

    return p;
}

bool ProfileController::saveProfile(Profile &p)
{
    bool success = profile_manager.save(p);

    if(profile_manager.hasError())
        emit DBError(profile_manager.getLastErrorMessage());

    return success;
}

bool ProfileController::loadLastProfile()
{
    SettingsManager &settings = SettingsManager::getInstance();

    this->profile = getProfile(settings.get("Profile", "id", QVariant(1)).toInt());

    if(this->profile.getId() == 0)
        return false;

    emit lastProfileLoaded();

    return true;
}

Profile& ProfileController::getCurrentProfile()
{
    return profile;
}
