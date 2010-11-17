#include "customercontroller.h"


CustomerController::CustomerController() {}

CustomerController* CustomerController::getInstance()
{
    static CustomerController instance;

    return &instance;
}


Customer CustomerController::get(int id)
{
    Customer p = manager.get(id);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return p;
}

bool CustomerController::save(Customer &p)
{
    bool success = manager.save(p);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return success;
}

bool CustomerController::erase(int id)
{
    bool success = manager.erase(id);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return success;
}
