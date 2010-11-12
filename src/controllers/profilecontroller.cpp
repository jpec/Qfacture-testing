#include "profilecontroller.h"
#include "managers/settingsmanager.h"

#include <QVariant>


ProfileController::ProfileController(QObject *parent) : Controller(parent)
{
}

ProfileController::~ProfileController()
{
    SettingsManager &settings = SettingsManager::getInstance();

    if(this->getCurrent().getId() != 0)
        settings.set("Profile", "id", this->getCurrent().getId());
}

Profile ProfileController::get(int id)
{
    Profile p = profile_manager.get(id);

    if(profile_manager.hasError())
        emit DBError(profile_manager.getLastErrorMessage());

    return p;
}

bool ProfileController::save(Profile &p)
{
    bool success = profile_manager.save(p);

    if(profile_manager.hasError())
        emit DBError(profile_manager.getLastErrorMessage());

    return success;
}

bool ProfileController::saveCurrent()
{
    if(this->getCurrent().getId() == 0)
        return false;

    return this->save(this->getCurrent());
}

bool ProfileController::loadLastProfile()
{
    SettingsManager &settings = SettingsManager::getInstance();

    this->profile = this->get(settings.get("Profile", "id", QVariant(1)).toInt());

    if(this->getCurrent().getId() == 0)
        return false;

    emit lastProfileLoaded();

    return true;
}

Profile& ProfileController::getCurrent()
{
    return this->profile;
}
