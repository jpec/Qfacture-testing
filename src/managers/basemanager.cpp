#include "basemanager.h"


bool BaseManager::hasError() const
{
    return !error_msg.isEmpty();
}

QString BaseManager::getLastErrorMessage() const
{
    return error_msg;
}

QString BaseManager::getLastErrorQuery() const
{
    return error_query;
}

void BaseManager::setError(const QString &message, const QString &sql)
{
    error_msg = message;
    error_query = sql;
}
