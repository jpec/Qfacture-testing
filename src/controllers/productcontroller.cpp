#include "productcontroller.h"


ProductController::ProductController() {}

ProductController* ProductController::getInstance()
{
    static ProductController instance;

    return &instance;
}

Product ProductController::get(int id)
{
    return manager.get(id);
}

bool ProductController::save(Product &p)
{
    return manager.save(p);
}

bool ProductController::erase(int id)
{
    return manager.erase(id);
}
