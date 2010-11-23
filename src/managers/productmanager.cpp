#include "productmanager.h"
#include "controllers/dbcontroller.h"

#include "QVariant"


Product ProductManager::get(int id)
{
    QSqlQuery query;

    query.prepare(
            "SELECT id, Name, Price, Comment "
            "FROM article WHERE id = :product_id"
        );

    query.bindValue(":product_id", QVariant(id));

    if(!DBController::getInstance()->exec(query))
        return Product();

    // pas de produit avec l'ID demandé, on ne remonte pas d'erreur
    // mais juste un produit vide
    if(!query.next())
        return Product();

    return makeProduct(query);
}

bool ProductManager::save(Product &product)
{
    return (product.getId() == 0) ? insert(product) : update(product);
}

bool ProductManager::erase(int id)
{
    QSqlQuery query;

    if(id == 0)
        return false;

    query.prepare("DELETE FROM article WHERE id = :a_id");

    query.bindValue(":a_id", QVariant(id));

    return DBController::getInstance()->exec(query);
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

    return DBController::getInstance()->exec(query);
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
