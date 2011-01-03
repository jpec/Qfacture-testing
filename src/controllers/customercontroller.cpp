#include "customercontroller.h"


CustomerController::CustomerController() {}

CustomerController* CustomerController::getInstance()
{
    static CustomerController instance;

    return &instance;
}


Customer CustomerController::get(int id, int uid)
{
    return manager.get(id, uid);
}

bool CustomerController::save(Customer &p, int uid)
{
    return manager.save(p, uid);
}

bool CustomerController::erase(int id, int uid)
{
    return manager.erase(id, uid);
}
