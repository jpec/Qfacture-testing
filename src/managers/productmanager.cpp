#include "productmanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Product ProductManager::get(int id)
{
    QSqlQuery query;
    Product p;

    query.prepare(
            "SELECT id, Name, Price, Comment "
            "FROM article WHERE id = :product_id"
        );

    query.bindValue(":product_id", QVariant(id));

    if(!DBController::getInstance()->exec(query))
        return p;

    // pas de produit avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un produit vide
    if(query.next())
        p = makeProduct(query);

    query.finish();

    return p;
}

bool ProductManager::save(Product &product)
{
    return (product.getId() == 0) ? insert(product) : update(product);
}

bool ProductManager::erase(int id)
{
    QSqlQuery query;
    bool result;

    if(id == 0)
        return false;

    query.prepare("DELETE FROM article WHERE id = :a_id");

    query.bindValue(":a_id", QVariant(id));

    result = DBController::getInstance()->exec(query);

    query.finish();

    return result;
}

bool ProductManager::insert(Product &product)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO article (Name, Price, Comment) "
            "VALUES (:name, :price, :comment)"
    );

    bindProduct(product, query);

    if(DBController::getInstance()->exec(query))
    {
        product.setId(query.lastInsertId().toInt());

        query.finish();

        return true;
    }

    return false;
}

bool ProductManager::update(const Product &product)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE article "
            "SET Name = :name, Price = :price, Comment = :comment "
            "WHERE id = :a_id"
    );

    bindProduct(product, query);

    if(DBController::getInstance()->exec(query))
    {
        query.finish();

        return true;
    }

    return false;
}

void ProductManager::bindProduct(const Product &product, QSqlQuery &query)
{
    query.bindValue(":a_id", product.getId());
    query.bindValue(":name", product.getName());
    query.bindValue(":price", product.getPrice());
    query.bindValue(":comment", product.getDescription());
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
