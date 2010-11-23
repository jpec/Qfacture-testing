#include "profilecontroller.h"
#include "managers/settingsmanager.h"

#include <QVariant>


ProfileController::ProfileController() {}

ProfileController* ProfileController::getInstance()
{
    static ProfileController instance;

    return &instance;
}

ProfileController::~ProfileController()
{
    SettingsManager &settings = SettingsManager::getInstance();

    if(this->getCurrent().getId() != 0)
        settings.set("Profile", "id", this->getCurrent().getId());
}

Profile ProfileController::get(int id)
{
    return profile_manager.get(id);
}

bool ProfileController::save(Profile &p)
{
    return profile_manager.save(p);
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

    return true;
}

Profile& ProfileController::getCurrent()
{
    return this->profile;
}
