#include "customermanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Customer CustomerManager::get(int id, int uid)
{
    QSqlQuery query;
    QString sql;
    Customer c;

    sql = "SELECT cID, name, address, complement, zip, city, phone, mail "
          "FROM client WHERE cID = :customer_id";

    if(uid != -1)
        sql += " AND u_ID = :uid";

    query.prepare(sql);

    query.bindValue(":customer_id", QVariant(id));
    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    if(!DBController::getInstance()->exec(query))
        return c;

    // pas de client avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un client vide
    if(query.next())
        c = makeCustomer(query);

    query.finish();

    return c;
}

QList<Customer> CustomerManager::getList(int uid, const QString &name_filter)
{
    QSqlQuery query;
    QString sql, filter;
    QList<Customer> list;

    sql = "SELECT cID, name, address, complement, zip, city, phone, mail "
          "FROM client WHERE 1 = 1";

    if(uid != -1)
        sql += " AND u_ID = :uid";

    if(!name_filter.isEmpty())
    {
        filter = "%"+name_filter+"%";

        sql += " AND name LIKE :name_filter";
    }

    query.prepare(sql);

    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    if(!name_filter.isEmpty())
        query.bindValue(":name_filter", filter);

    if(!DBController::getInstance()->exec(query))
        return list;

    while(query.next())
        list.append(makeCustomer(query));

    query.finish();

    return list;
}

bool CustomerManager::save(Customer &customer, int uid)
{
    if(uid < 1)
        return false;

    return customer.isNew() ? insert(customer, uid) : update(customer, uid);
}

bool CustomerManager::erase(int id, int uid)
{
    QSqlQuery query;
    QString sql;

    if(id <= 0)
        return false;

    sql = "DELETE FROM client WHERE cID = :c_id";

    if(uid != -1)
        sql += " AND u_ID = :uid";

    query.prepare(sql);

    query.bindValue(":c_id", QVariant(id));
    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

bool CustomerManager::insert(Customer &customer, int uid)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO client "
                "(u_ID, name, address, complement, zip, city, phone, Mail) "
            "VALUES "
                "(:uid, :name, :address, :address2, :zip, :city, :phone, :mail)"
    );

    bindCustomer(customer, query, uid);

    if(DBController::getInstance()->exec(query))
    {
        customer.setId(query.lastInsertId().toInt());

        query.finish();

        return true;
    }

    return false;
}

bool CustomerManager::update(const Customer &customer, int uid)
{
    QSqlQuery query;

    query.prepare("UPDATE client "
                  "SET name = :name, address = :address, complement = :complement, "
                      "zip = :zip, city = :city, phone = :phone, "
                      "mail = :mail "
                  "WHERE cID = :c_id AND u_ID = :uid");

    bindCustomer(customer, query, uid);

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

void CustomerManager::bindCustomer(const Customer &customer, QSqlQuery &query, int uid)
{
    query.bindValue(":c_id", customer.getId());
    query.bindValue(":name", customer.getName());
    query.bindValue(":address", customer.getAddress());
    query.bindValue(":complement", customer.getAddressComplement());
    query.bindValue(":zip", customer.getZipCode());
    query.bindValue(":city", customer.getCity());
    query.bindValue(":phone", customer.getPhone());
    query.bindValue(":mail", customer.getMail());

    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));
}

Customer CustomerManager::makeCustomer(QSqlQuery &query)
{
    Customer customer;

    customer.setId(query.value(0).toInt());
    customer.setName(query.value(1).toString());
    customer.setAddress(query.value(2).toString());
    customer.setAddressComplement(query.value(3).toString());
    customer.setZipCode(query.value(4).toString());
    customer.setCity(query.value(5).toString());
    customer.setPhone(query.value(6).toString());
    customer.setMail(query.value(7).toString());

    return customer;
}
