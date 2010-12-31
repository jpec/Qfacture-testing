#include "customermanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Customer CustomerManager::get(int id)
{
    QSqlQuery query;
    Customer c;

    query.prepare(
            "SELECT cID, name, address, complement, zip, city, phone, mail "
            "FROM client WHERE cID = :customer_id"
        );

    query.bindValue(":customer_id", QVariant(id));

    if(!DBController::getInstance()->exec(query))
        return c;

    // pas de client avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un client vide
    if(query.next())
        c = makeCustomer(query);

    query.finish();

    return c;
}

bool CustomerManager::save(Customer &customer)
{
    return (customer.getId() == 0) ? insert(customer) : update(customer);
}

bool CustomerManager::erase(int id)
{
    QSqlQuery query;

    if(id == 0)
        return false;

    query.prepare("DELETE FROM client WHERE cID = :c_id");

    query.bindValue(":c_id", QVariant(id));

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

bool CustomerManager::insert(Customer &customer)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO client (name, address, complement, zip, city, phone, "
                                 "Mail) "
            "VALUES (:name, :address, :address2, :zip, :city, :phone, :mail)"
    );

    bindCustomer(customer, query);

    if(DBController::getInstance()->exec(query))
    {
        customer.setId(query.lastInsertId().toInt());

        query.finish();

        return true;
    }

    return false;
}

bool CustomerManager::update(const Customer &customer)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE client "
            "SET name = :name, address = :address, complement = :complement, "
                "zip = :zip, city = :city, phone = :phone, "
                "mail = :mail "
            "WHERE cID = :c_id"
    );

    bindCustomer(customer, query);

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

void CustomerManager::bindCustomer(const Customer &customer, QSqlQuery &query)
{
    query.bindValue(":c_id", customer.getId());
    query.bindValue(":name", customer.getName());
    query.bindValue(":address", customer.getAddress());
    query.bindValue(":complement", customer.getAddressComplement());
    query.bindValue(":zip", customer.getZipCode());
    query.bindValue(":city", customer.getCity());
    query.bindValue(":phone", customer.getPhone());
    query.bindValue(":mail", customer.getMail());
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
