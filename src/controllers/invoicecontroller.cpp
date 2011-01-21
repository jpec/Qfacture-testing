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

bool InvoiceController::erase(Invoice &i, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.erase(i.getId(), uid);
}

bool InvoiceController::erase(int i, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.erase(i, uid);
}

QList<ReglementType> InvoiceController::getReglements(int uid)
{
    if(uid < 1)
        return QList<ReglementType>();

    return manager.getReglements(uid);
}

QList<DocumentType> InvoiceController::getTypes(int uid)
{
    if(uid < 1)
        return QList<DocumentType>();

    return manager.getTypes(uid);
}

bool InvoiceController::save(Invoice &i, int uid)
{
    // la facture doit appartenir à quelqu'un
    if(uid < 1)
        return false;

    return manager.save(i, uid);
}

