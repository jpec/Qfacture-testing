#include "invoicemanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Invoice InvoiceManager::get(int id, int uid)
{
    QSqlQuery query;
    QString sql;
    Invoice in;

    sql = "SELECT "
              "fID, c_ID, amount, comment, Type, date, "
              "c.name "
          "FROM facture f "
          "LEFT JOIN client c ON c.cID = f.c_ID "
          "WHERE f.fID = :f_id";

    if(uid != -1)
        sql += " AND f.u_ID = :uid";

    query.prepare(sql);

    query.bindValue(":Invoice_id", QVariant(id));
    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    // pas de facture avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste une facture vide
    if(!DBController::getInstance()->exec(query))
        return in;

    if(query.next())
        in = makeInvoice(query);

    query.finish();

    return in;
}

bool InvoiceManager::save(Invoice &invoice, int uid)
{
    if(uid < 1)
        return false;

    return invoice.isNew() ? insert(invoice, uid) : update(invoice, uid);
}

bool InvoiceManager::erase(int id, int uid)
{
    // not implemented
    return false;
}

bool InvoiceManager::insert(Invoice &Invoice, int uid)
{
    // not implemented
    return false;
}

bool InvoiceManager::update(const Invoice &Invoice, int uid)
{
    // not implemented
    return false;
}

void InvoiceManager::bindInvoice(const Invoice &invoice, QSqlQuery &query, int uid)
{
    query.bindValue(":f_id", invoice.getId());
//    query.bindValue(":name", invoice.getName());
//    query.bindValue(":price", invoice.getPrice());
//    query.bindValue(":comment", invoice.getDescription());

    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));
}

Invoice InvoiceManager::makeInvoice(QSqlQuery &query)
{
    Invoice invoice;
    Customer c;

    invoice.setId(query.value(0).toInt());
    invoice.setAmount(query.value(2).toFloat());
    invoice.setDescription(query.value(3).toString());
    invoice.setRef(query.value(4).toString());
    invoice.setDate(QDate::fromString(query.value(5).toString(), Qt::ISODate));

    c.setId(query.value(1).toInt());
    c.setName(query.value(6).toString());
    invoice.setCustomer(c);

    return invoice;
}
