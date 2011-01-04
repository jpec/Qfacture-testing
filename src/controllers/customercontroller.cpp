#include "customercontroller.h"


CustomerController::CustomerController() {}

CustomerController* CustomerController::getInstance()
{
    static CustomerController instance;

    return &instance;
}


Customer CustomerController::get(int id, int uid)
{
    // le client doit appartenir à quelqu'un
    if(uid < 1)
        return Customer();

    return manager.get(id, uid);
}

bool CustomerController::save(Customer &p, int uid)
{
    // le client doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.save(p, uid);
}

bool CustomerController::erase(int id, int uid)
{
    // le client doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.erase(id, uid);
}
