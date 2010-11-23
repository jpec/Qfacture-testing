#include "customercontroller.h"


CustomerController::CustomerController() {}

CustomerController* CustomerController::getInstance()
{
    static CustomerController instance;

    return &instance;
}


Customer CustomerController::get(int id)
{
    return manager.get(id);
}

bool CustomerController::save(Customer &p)
{
    return manager.save(p);
}

bool CustomerController::erase(int id)
{
    return manager.erase(id);
}
