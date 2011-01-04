#include "productcontroller.h"


ProductController::ProductController() {}

ProductController* ProductController::getInstance()
{
    static ProductController instance;

    return &instance;
}

Product ProductController::get(int id, int uid)
{
    // le produit doit appartenir à quelqu'un
    if(uid < 1)
        return Product();

    return manager.get(id, uid);
}

bool ProductController::save(Product &p, int uid)
{
    // le produit doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.save(p, uid);
}

bool ProductController::erase(int id, int uid)
{
    // le produit doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.erase(id, uid);
}
