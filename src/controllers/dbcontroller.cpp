#include "dbcontroller.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>


DBController::DBController()
{
    // table client
    tables_pk["client"] = "cID";
    tables_definitions["client"]["cID"] = trUtf8("Identifiant");
    tables_definitions["client"]["name"] = trUtf8("Nom");
    tables_definitions["client"]["address"] = trUtf8("Adresse");
    tables_definitions["client"]["complement"] = trUtf8("Complément");
    tables_definitions["client"]["zip"] = trUtf8("Code postal");
    tables_definitions["client"]["city"] = trUtf8("Ville");
    tables_definitions["client"]["phone"] = trUtf8("Téléphone");
    tables_definitions["client"]["mail"] = trUtf8("Mail");

    // table article
    tables_pk["article"] = "aID";
    tables_definitions["article"]["aID"] = trUtf8("Identifiant");
    tables_definitions["article"]["name"] = trUtf8("Nom");
    tables_definitions["article"]["price"] = trUtf8("Prix");
    tables_definitions["article"]["comment"] = trUtf8("Description");

    // table facture
    tables_pk["facture"] = "fID";
    tables_definitions["facture"]["fID"] = trUtf8("Identifiant");
    tables_definitions["facture"]["c_ID"] = trUtf8("Identifiant du client");
    tables_definitions["facture"]["amount"] = trUtf8("Montant");
    tables_definitions["facture"]["comment"] = trUtf8("Commentaire");
    tables_definitions["facture"]["date"] = trUtf8("Date");

    /** Clauses de jointures **/

    // table facture
    join_clauses["facture"]["client"] = "facture.c_ID = client.cID";
}

DBController* DBController::getInstance()
{
    static DBController instance;

    return &instance;
}


QStringList DBController::getColumns(const QString& table,
                                     const QStringList& except) const
{
    QList<QString> cols = tables_definitions[table].keys();
    QString col;

    foreach(col, except)
    {
        if(cols.contains(col))
        {
            cols.removeOne(col);
        }
    }

    return QStringList(cols);
}

QString DBController::getJoinClause(const QString &from, const QString &with) const
{
    if(join_clauses.keys().contains(from))
        return join_clauses[from][with];
    else
        return join_clauses[with][from];
}

QStringList DBController::getLabels(const QString& table,
                                    const QStringList& except) const
{
    QStringList labels;
    QHashIterator<QString, QString> iterator(tables_definitions[table]);

    while (iterator.hasNext()) {
        iterator.next();

        if(!except.contains(iterator.key()))
            labels.append(iterator.value());
    }

    return labels;
}

QString DBController::getLabel(const QString &table, const QString &column) const
{
    return tables_definitions[table][column];
}

QString DBController::getPK(const QString &table) const
{
    return tables_pk[table];
}

bool DBController::exec(QSqlQuery &query)
{
    if(!query.exec()) {
        emit DBError(query.lastError().databaseText());

        query.finish();

        return false;
    }

    return true;
}

QStringList DBController::getAvailableDrivers() const
{
    return this->db.drivers();
}

void DBController::connectDB(const QString &server, int port, const QString &login,
                             const QString &pass, const QString &db_name, const QString &db_type)
{
    if(this->isDBConnected())
        return;

    this->db = QSqlDatabase::addDatabase(db_type);

    this->db.setHostName(server);
    this->db.setPort(port);
    this->db.setUserName(login);
    this->db.setPassword(pass);
    this->db.setDatabaseName(db_name);

    if(this->db.open())
        emit DBConnected();
    else
        emit DBConnectionError(this->db.lastError().databaseText());
}

/**
 * Ferme la connexion avec la base de données si elle existe.
 */
void DBController::disconnectDB()
{
    if(!this->isDBConnected())
        return;

    this->db.commit();

    this->db.close();

    emit DBDisconnected();
}

bool DBController::isDBConnected() const
{
    return db.isOpen();
}
