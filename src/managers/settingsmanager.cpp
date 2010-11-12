#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    settings = new QSettings("Qfacture", "Qfacture");
}

SettingsManager::~SettingsManager()
{
    delete settings;
}

SettingsManager& SettingsManager::getInstance()
{
    static SettingsManager instance;

    return instance;
}

void SettingsManager::set(const QString &group, const QString &key, const QVariant &value)
{
    this->settings->beginGroup(group);
    this->settings->setValue(key, value);
    this->settings->endGroup();
}

QVariant SettingsManager::get(const QString &group, const QString &key, const QVariant &default_value) const
{
    QVariant val;

    this->settings->beginGroup(group);
    val = this->settings->value(key, default_value);
    this->settings->endGroup();

    return val;
}
