#include "dbcontroller.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>


DBController::DBController()
{
    // table client
    tables_definitions["client"]["id"] = trUtf8("Identifiant");
    tables_definitions["client"]["Name"] = trUtf8("Nom");
    tables_definitions["client"]["Adress"] = trUtf8("Adresse");
    tables_definitions["client"]["Adress2"] = trUtf8("Complément");
    tables_definitions["client"]["Zip"] = trUtf8("Code postal");
    tables_definitions["client"]["City"] = trUtf8("Ville");
    tables_definitions["client"]["Phone"] = trUtf8("Téléphone");
    tables_definitions["client"]["Mail"] = trUtf8("Mail");
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

bool DBController::exec(QSqlQuery &query)
{
    if(!query.exec()) {
        emit DBError(query.lastError().databaseText());

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
