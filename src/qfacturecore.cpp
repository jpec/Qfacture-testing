#include "qfacturecore.h"

#include <QSqlError>
#include <QSqlQuery>


QfactureCore::QfactureCore()
{
    this->createControllers();
}


void QfactureCore::createControllers()
{
    controllers["db"] = new DBController();
    controllers["profiles"] = new ProfileController();
}

Controller* QfactureCore::getController(const QString &name) const
{
    return controllers[name];
}

DBController* QfactureCore::getDBController()
{
    return (DBController *) getController("db");
}

ProfileController* QfactureCore::getProfileController()
{
    return (ProfileController *) getController("profiles");
}
