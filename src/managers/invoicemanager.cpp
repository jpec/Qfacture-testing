#include "invoicemanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"

Invoice InvoiceManager::get(int id)
{
    QSqlQuery query;
    Invoice in;

    query.prepare(
           "SELECT "
                "fID, c_ID, amount, comment, Type, date, "
                "c.name "
           "FROM facture f "
           "LEFT JOIN client c ON c.cID = f.c_ID "
           "WHERE f.fID = :Invoice_id "
        );

    query.bindValue(":Invoice_id", QVariant(id));

    if(!DBController::getInstance()->exec(query))
        return in;

    // pas de facture avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste une facture vide
    if(query.next())
        in = makeInvoice(query);

    query.finish();

    return in;
}

bool InvoiceManager::save(Invoice &invoice)
{
    return invoice.isNew() ? insert(invoice) : update(invoice);
}

bool InvoiceManager::erase(int id)
{
    //QSqlQuery query;
    bool result = false;

    if(id == 0)
        return false;

//    query.prepare("DELETE FROM facture WHERE id = :a_id");
//
//    query.bindValue(":a_id", QVariant(id));
//
//    result = DBController::getInstance()->exec(query);
//
//    query.finish();
//
    return result;
}

bool InvoiceManager::insert(Invoice &Invoice)
{
    QSqlQuery query;

//    query.prepare(
//            "INSERT INTO article (Name, Price, Comment) "
//            "VALUES (:name, :price, :comment)"
//    );
//
//    bindInvoice(Invoice, query);
//
//    if(DBController::getInstance()->exec(query))
//    {
//        Invoice.setId(query.lastInsertId().toInt());
//
//        query.finish();
//
//        return true;
//    }

    return false;
}

bool InvoiceManager::update(const Invoice &Invoice)
{
    QSqlQuery query;

//    query.prepare(
//            "UPDATE article "
//            "SET Name = :name, Price = :price, Comment = :comment "
//            "WHERE id = :a_id"
//    );
//
//    bindInvoice(Invoice, query);
//
//    if(DBController::getInstance()->exec(query))
//    {
//        query.finish();
//
//        return true;
//    }

    return false;
}

void InvoiceManager::bindInvoice(const Invoice &Invoice, QSqlQuery &query)
{
//    query.bindValue(":a_id", Invoice.getId());
//    query.bindValue(":name", Invoice.getName());
//    query.bindValue(":price", Invoice.getPrice());
//    query.bindValue(":comment", Invoice.getDescription());
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
