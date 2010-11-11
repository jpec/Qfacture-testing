#include "qfacturecore.h"

#include <QSqlError>
#include <QSqlQuery>


QfactureCore::QfactureCore()
{
    this->settings = new QSettings("Qfacture", "Qfacture", this);
    this->createControllers();
}

QfactureCore::~QfactureCore()
{
    delete settings;
}


void QfactureCore::createControllers()
{
    controllers["db"] = new DBController(this);
}

Controller* QfactureCore::getController(const QString &name) const
{
    return controllers[name];
}

DBController* QfactureCore::getDBController()
{
    return (DBController *) getController("db");
}

void QfactureCore::setSetting(const QString &group, const QString &key, const QVariant &value)
{
    this->settings->beginGroup(group);
    this->settings->setValue(key, value);
    this->settings->endGroup();
}

QVariant QfactureCore::getSetting(const QString &group, const QString &key, const QVariant &default_value) const
{
    QVariant val;

    this->settings->beginGroup(group);
    val = this->settings->value(key, default_value);
    this->settings->endGroup();

    return val;
}
