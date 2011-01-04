#include "invoicecontroller.h"

InvoiceController::InvoiceController() {}

InvoiceController* InvoiceController::getInstance()
{
    static InvoiceController instance;

    return &instance;
}

Invoice InvoiceController::get(int id, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return Invoice();

    return manager.get(id, uid);
}

bool InvoiceController::save(Invoice &i, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.save(i, uid);
}

bool InvoiceController::erase(int id, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.erase(id, uid);
}
