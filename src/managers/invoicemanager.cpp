#include "invoicemanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Invoice InvoiceManager::get(int id, int uid)
{
    QSqlQuery query;
    QString sql;
    Invoice in;

    sql = "SELECT "
              "fID, c_ID, amount, comment, date, "
              "c.name, trID, tr.name, tdID, td.name "
          "FROM facture f "
          "LEFT JOIN client c ON c.cID = f.c_ID "
          "LEFT JOIN types_reglements tr ON tr.trID = f.tr_ID "
          "LEFT JOIN types_documents td ON td.tdID = f.td_ID "
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

QHash<int, QString> InvoiceManager::getReglements(int uid)
{
    QSqlQuery query;
    QHash<int, QString> list;

    query.prepare("SELECT trID, name FROM types_reglements WHERE u_ID = :uid");

    query.bindValue(":uid", QVariant(uid));

    if(!DBController::getInstance()->exec(query))
        return list;

    while(query.next())
        list[query.value(0).toInt()] = query.value(1).toString();

    query.finish();

    return list;
}

QHash<int, QString> InvoiceManager::getTypes(int uid)
{
    QSqlQuery query;
    QHash<int, QString> list;

    query.prepare("SELECT tdID, name FROM types_documents WHERE u_ID = :uid");

    query.bindValue(":uid", QVariant(uid));

    if(!DBController::getInstance()->exec(query))
        return list;

    while(query.next())
        list[query.value(0).toInt()] = query.value(1).toString();

    query.finish();

    return list;
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
    ReglementType r;
    DocumentType d;

    invoice.setId(query.value(0).toInt());
    invoice.setAmount(query.value(2).toFloat());
    invoice.setDescription(query.value(3).toString());
    //invoice.setRef(query.value(4).toString());
    invoice.setDate(QDate::fromString(query.value(4).toString(), Qt::ISODate));

    r.setId(query.value(6).toInt());
    r.setName(query.value(7).toString());
    invoice.setReglement(r);

    d.setId(query.value(8).toInt());
    d.setName(query.value(9).toString());
    invoice.setType(d);

    c.setId(query.value(1).toInt());
    c.setName(query.value(5).toString());
    invoice.setCustomer(c);

    return invoice;
}
