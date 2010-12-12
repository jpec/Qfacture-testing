#include "invoicecontroller.h"

InvoiceController::InvoiceController() {}

InvoiceController* InvoiceController::getInstance()
{
    static InvoiceController instance;

    return &instance;
}

Invoice InvoiceController::get(int id)
{
    return manager.get(id);
}

bool InvoiceController::save(Invoice &i)
{
    return manager.save(i);
}

bool InvoiceController::erase(int id)
{
    return manager.erase(id);
}
