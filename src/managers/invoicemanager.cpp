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
          "WHERE f.fID = :Invoice_id";

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

QList<ReglementType> InvoiceManager::getReglements(int uid)
{
    QSqlQuery query;
    ReglementType r;
    QList<ReglementType> list;

    query.prepare("SELECT trID, name FROM types_reglements WHERE u_ID = :uid");

    query.bindValue(":uid", QVariant(uid));

    if(!DBController::getInstance()->exec(query))
        return list;

    while(query.next())
    {
        r = ReglementType();
        r.setId(query.value(0).toInt());
        r.setName(query.value(1).toString());

        list.append(r);
    }

    query.finish();

    return list;
}

QList<DocumentType> InvoiceManager::getTypes(int uid)
{
    QSqlQuery query;
    DocumentType d;
    QList<DocumentType> list;

    query.prepare("SELECT tdID, name FROM types_documents WHERE u_ID = :uid");

    query.bindValue(":uid", QVariant(uid));

    if(!DBController::getInstance()->exec(query))
        return list;

    while(query.next())
    {
        d = DocumentType();
        d.setId(query.value(0).toInt());
        d.setName(query.value(1).toString());

        list.append(d);
    }

    query.finish();

    return list;
}

bool InvoiceManager::save(Invoice &invoice, int uid)
{
    if(uid < 1)
        return false;

    // pas de ligne
    if(invoice.getLinesCount() == 0)
        return false;

    // le client n'existe pas dans la BDD
    if(invoice.getCustomer().isNew())
        return false;

    // pas de type de document
    if(invoice.getType().isNew())
        return false;

    // pas de type de reglement
    if(invoice.getReglement().isNew())
        return false;

    return invoice.isNew() ? insert(invoice, uid) : update(invoice, uid);
}

bool InvoiceManager::erase(int id, int uid)
{
    // not implemented
    return false;
}

bool InvoiceManager::insert(Invoice &invoice, int uid)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO facture (u_ID, c_ID, tr_ID, td_ID, amount, comment, Date) "
            "VALUES (:uid, :c_id, :tr_id, :td_id, :amount, :comment, :date)"
    );

    bindInvoice(invoice, query, uid);

    if(DBController::getInstance()->exec(query))
    {
        invoice.setId(query.lastInsertId().toInt());

        query.finish();

        insertLines(invoice);

        return true;
    }

    return false;
}

void InvoiceManager::insertLines(Invoice &invoice)
{
    QSqlQuery query;
    InvoiceLine line;

    query.prepare(
            "INSERT INTO factures_lignes (f_ID, base_article, name, designation, quantity, price, off) "
            "VALUES (:f_id, :base_article, :name, :designation, :qte, :price, :off)"
    );

    for(int i=0; i < invoice.getLinesCount(); ++i)
    {
        line = invoice.getLine(i);

        bindInvoiceLine(invoice.getId(), line, query);

        DBController::getInstance()->exec(query);

        line.setId(query.lastInsertId().toInt());
    }

    query.finish();
}

bool InvoiceManager::update(const Invoice &Invoice, int uid)
{
    // not implemented
    return false;
}

void InvoiceManager::bindInvoice(const Invoice &invoice, QSqlQuery &query, int uid)
{
    query.bindValue(":f_id", invoice.getId());
    query.bindValue(":c_id", invoice.getCustomer().getId());
    query.bindValue(":tr_id", invoice.getReglement().getId());
    query.bindValue(":td_id", invoice.getType().getId());
    query.bindValue(":amount", invoice.getAmount());
    query.bindValue(":comment", invoice.getDescription());
    query.bindValue(":date", invoice.getDate());

    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));
}

void InvoiceManager::bindInvoiceLine(int invoice, const InvoiceLine &line, QSqlQuery &query)
{
    query.bindValue(":f_id", invoice);
    query.bindValue(":base_article", line.getBaseProductId());
    query.bindValue(":name", line.getName());
    query.bindValue(":designation", line.getDescription());
    query.bindValue(":qte", line.getQte());
    query.bindValue(":price", line.getPrice());
    query.bindValue(":off", line.getOffPercentage());
}

Invoice InvoiceManager::makeInvoice(QSqlQuery &query)
{
    QSqlQuery lines_query;
    InvoiceLine line;
    Invoice invoice;
    Customer c;
    ReglementType r;
    DocumentType d;

    invoice.setId(query.value(0).toInt());
    invoice.setDescription(query.value(3).toString());
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

    // récupération des lignes
    lines_query.prepare("SELECT "
                            "lID, name, designation, quantity, price, off, base_article "
                        "FROM factures_lignes f "
                        "WHERE f_ID = :f_id");

    lines_query.bindValue(":f_id", query.value(0));

    if(!DBController::getInstance()->exec(lines_query))
        return invoice;

    while(lines_query.next())
    {
        line = InvoiceLine();

        line.setId(lines_query.value(0).toInt());
        line.setName(lines_query.value(1).toString());
        line.setDescription(lines_query.value(2).toString());
        line.setQte(lines_query.value(3).toInt());
        line.setPrice(lines_query.value(4).toFloat());
        line.setOffPercentage(lines_query.value(5).toFloat());
        line.setBaseProductId(lines_query.value(6).toInt());

        invoice.addLine(line);
    }

    lines_query.finish();

    return invoice;
}
