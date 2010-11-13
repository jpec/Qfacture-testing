#include "productmanager.h"

#include "QVariant"
#include "QSqlError"


Product ProductManager::get(int id)
{
    QSqlQuery query;

    query.prepare(
            "SELECT id, Name, Price, Comment "
            "FROM article WHERE id = :product_id"
        );

    query.bindValue(":product_id", QVariant(id));

    if(!query.exec()) {
        setError(query.lastError().databaseText(), query.lastQuery());

        return Product();
    }

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

    if(query.exec())
        return true;

    setError(query.lastError().databaseText(), query.lastQuery());

    return false;
}

bool ProductManager::insert(Product &product)
{
    QSqlQuery query;

    query.prepare(
            "INSERT INTO article (Name, Price, Comment) "
            "VALUES (:name, :price, :comment)"
    );

    bindProduct(product, query);

    if(query.exec())
    {
        product.setId(query.lastInsertId().toInt());

        return true;
    }

    setError(query.lastError().databaseText(), query.lastQuery());

    return false;
}

bool ProductManager::update(const Product &product)
{
    QSqlQuery query;

    query.prepare(
            "UPDATE article "
            "SET Name = :name, Price = :price, Comment = :comment, "
            "WHERE id = :a_id"
    );

    bindProduct(product, query);

    if(query.exec())
        return true;

    setError(query.lastError().databaseText(), query.lastQuery());

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
