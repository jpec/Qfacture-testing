#include "invoicemanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"

Invoice InvoiceManager::get(int id)
{
    QSqlQuery query;
    Invoice p;

//    query.prepare(
//           "SELECT id, Name, Price, Comment "
//            "FROM article WHERE id = :Invoice_id"
//        );
//
//    query.bindValue(":Invoice_id", QVariant(id));
//
//    if(!DBController::getInstance()->exec(query))
//        return p;
//
//    // pas de produit avec l'ID demandé, on ne remonte pas d'erreur
//    // mais juste un produit vide
//    if(query.next())
//        p = makeInvoice(query);

    query.finish();

    return p;
}

bool InvoiceManager::save(Invoice &Invoice)
{
    return (Invoice.getId() == 0) ? insert(Invoice) : update(Invoice);
}

bool InvoiceManager::erase(int id)
{
    QSqlQuery query;
    bool result;

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
//    return result;
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
    Invoice Invoice;

//    Invoice.setId(query.value(0).toInt());
//    Invoice.setName(query.value(1).toString());
//    Invoice.setPrice(query.value(2).toFloat());
//    Invoice.setDescription(query.value(3).toString());

    return Invoice;
}
