#include "productcontroller.h"


ProductController::ProductController() {}

ProductController* ProductController::getInstance()
{
    static ProductController instance;

    return &instance;
}

Product ProductController::get(int id, int uid)
{
    return manager.get(id, uid);
}

bool ProductController::save(Product &p, int uid)
{
    return manager.save(p, uid);
}

bool ProductController::erase(int id, int uid)
{
    return manager.erase(id, uid);
}
