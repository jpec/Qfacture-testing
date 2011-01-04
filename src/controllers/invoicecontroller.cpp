#include "invoicecontroller.h"

InvoiceController::InvoiceController() {}

InvoiceController* InvoiceController::getInstance()
{
    static InvoiceController instance;

    return &instance;
}

Invoice InvoiceController::get(int id, int uid)
{
    return manager.get(id, uid);
}

bool InvoiceController::save(Invoice &i, int uid)
{
    return manager.save(i, uid);
}

bool InvoiceController::erase(int id, int uid)
{
    return manager.erase(id, uid);
}
