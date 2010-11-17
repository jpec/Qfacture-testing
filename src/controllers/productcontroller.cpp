#include "productcontroller.h"


ProductController::ProductController() {}

ProductController* ProductController::getInstance()
{
    static ProductController instance;

    return &instance;
}

Product ProductController::get(int id)
{
    Product p = manager.get(id);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return p;
}

bool ProductController::save(Product &p)
{
    bool success = manager.save(p);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return success;
}

bool ProductController::erase(int id)
{
    bool success = manager.erase(id);

    if(manager.hasError())
        emit DBError(manager.getLastErrorMessage());

    return success;
}
