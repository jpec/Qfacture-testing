#ifndef QFACTURECORE_H
#define QFACTURECORE_H

#include <QSqlDatabase>
#include <QObject>
#include <string>

using namespace std;


/**
 * Fait office de contrôleur géant et sera utilisé par la GUI.
 */ 
class QfactureCore : public QObject
{
    Q_OBJECT
    
public:
    void connectDB(const QString &server, int port, const QString &login, 
                   const QString &pass, const QString &db_name, const QString &db_type="QMYSQL");
    bool isDBConnected() const;
    
signals:
    void DBConnected();
    void DBDisconnected();
    void DBConnectionError(const QString &error);
    void DBDError(const QString &error);

private:
    QSqlDatabase db;
};

#endif // QFACTURECORE_H
