#include "productmanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Product ProductManager::get(int id, int uid)
{
    QSqlQuery query;
    QString sql;
    Product p;

    sql = "SELECT aID, name, price, comment "
          "FROM article WHERE aID = :product_id ";

    if(uid != -1)
        sql += " AND u_ID = :uid";

    query.prepare(sql);

    query.bindValue(":product_id", QVariant(id));
    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    // pas de produit avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un produit vide
    if(!DBController::getInstance()->exec(query))
        return p;

    if(query.next())
        p = makeProduct(query);

    query.finish();

    return p;
}

bool ProductManager::save(Product &product, int uid)
{
    if(uid < 1)
        return false;

    return product.isNew() ? insert(product, uid) : update(product, uid);
}

bool ProductManager::erase(int id, int uid)
{
    QSqlQuery query;
    QString sql;

    if(id <= 0)
        return false;

    sql = "DELETE FROM article WHERE aID = :a_id ";

    if(uid != -1)
         sql += "AND u_ID = :uid";

    query.prepare(sql);

    query.bindValue(":a_id", QVariant(id));
    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

bool ProductManager::insert(Product &product, int uid)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO article (u_ID, name, price, comment) "
            "VALUES (:uid, :name, :price, :comment)"
    );

    bindProduct(product, query, uid);

    if(DBController::getInstance()->exec(query))
    {
        product.setId(query.lastInsertId().toInt());

        query.finish();

        return true;
    }

    return false;
}

bool ProductManager::update(const Product &product, int uid)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE article "
            "SET name = :name, price = :price, comment = :comment "
            "WHERE aID = :a_id AND u_ID = :uid"
    );

    bindProduct(product, query, uid);

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

void ProductManager::bindProduct(const Product &product, QSqlQuery &query, int uid)
{
    query.bindValue(":a_id", product.getId());
    query.bindValue(":name", product.getName());
    query.bindValue(":price", product.getPrice());
    query.bindValue(":comment", product.getDescription());

    if(uid != -1)
        query.bindValue(":uid", QVariant(uid));
}

Product ProductManager::makeProduct(QSqlQuery &query)
{
    Product product;

    product.setId(query.value(0).toInt());
    product.setName(query.value(1).toString());
    product.setPrice(query.value(2).toFloat());
    product.setDescription(query.value(3).toString());

    return product;
}
