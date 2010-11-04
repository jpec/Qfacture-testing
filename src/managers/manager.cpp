#include "managers/manager.h"

Manager::Manager(QSqlDatabase &db)
{
    this->db = db;
}
