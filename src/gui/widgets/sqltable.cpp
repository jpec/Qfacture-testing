#include "sqltable.h"
#include "controllers/dbcontroller.h"

#include <assert.h>
#include <QSqlQuery>


SQLTable::SQLTable(const QString &table_name, int uid, QWidget *parent) : QObject(parent)
{
    table = new QTableWidget(parent);
    this->table_name = table_name;
    this->uid = (uid > 0 || uid == -1) ? uid : -1;

    connect(this, SIGNAL(tableModified()), this, SLOT(buildTable()));
    connect(table, SIGNAL(itemSelectionChanged()), this,
            SLOT(selectionChanged()));
    connect(table, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this,
            SIGNAL(itemDoubleClicked(QTableWidgetItem*)));
}

SQLTable::~SQLTable()
{
    delete table;
}


void SQLTable::setLikeFilter(const QString &like_filter_field, const QVariant &like_filter)
{
    if(!columns.contains(like_filter_field))
        return;

    this->like_filter_field = like_filter_field;
    this->like_filter = like_filter.toString().isEmpty() ? like_filter : "%"+like_filter.value<QString>()+"%";

    feedTable();
}

void SQLTable::selectionChanged()
{
    if(table->selectedItems().count() <= 0)
        return;

    emit itemSelected(table->selectedItems()[0]);
}

void SQLTable::removeItem(const QTableWidgetItem *item)
{
    table->removeRow(table->row(item));

    emit tableModified();
}

void SQLTable::setColumns(const QList<QString> &columns, const QList<QString> &labels)
{
    if(columns.count() != labels.count())
        return;

    this->addColumns(table_name, columns);
    this->labels =labels;

    emit tableModified();
}

void SQLTable::buildTable()
{
    table->clear();

    table->setAlternatingRowColors(true);
    table->setSortingEnabled(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table->setColumnCount(columns.count());
    table->setHorizontalHeaderLabels(QStringList(labels));

    feedTable();
}

void SQLTable::feedTable()
{
    QVariant v;
    QSqlQuery query;
    QString pk_name = DBController::getInstance()->getPK(table_name);
    QString fields = QStringList(columns).join(", "), query_sql, join_table;
    int i, j, nb_cols = columns.count();

    if(columns.count() == 0 || !DBController::getInstance()->isDBConnected())
        return;

    table->clearContents();

    /** construction de la requête **/

    query_sql = "SELECT "+pk_name+", "+fields+" FROM "+table_name+" ";

    foreach(join_table, to_join)
    {
        query_sql.append("LEFT JOIN "+join_table+" ON "+
                         DBController::getInstance()->getJoinClause(table_name, join_table)+" ");
    }

    // filtre en fonction de l'utilisateur courant
    if(uid != -1)
        query_sql.append("WHERE "+table_name+".u_ID = :uid");
    else
        query_sql.append("WHERE 1 = 1 "); // dirty hack pour ne pas avoir de bug avec les autres clauses du WHERE

    if(!like_filter.toString().isEmpty())
        query_sql.append("AND "+like_filter_field+" LIKE :like_filter ");

    query_sql.append("ORDER BY "+table_name+"."+pk_name+" ASC");

    /** exécution de la requête **/
    query.prepare(query_sql);

    if(uid != -1)
        query.bindValue(":uid", this->uid);

    if(!like_filter.toString().isEmpty())
        query.bindValue(":like_filter", like_filter);

    if(!DBController::getInstance()->exec(query))
        return;

    table->setRowCount(query.size());

    i = 0;
    while(query.next()) {
        for(j=0; j < nb_cols; ++j) {
            v = query.value(j+1);

            // application du filtre
            if(filters.keys().contains(columns.at(j)))
            {
                if(filters[columns.at(j)] != 0)
                    v = (*filters[columns.at(j)])(v);
            }

            table->setItem(i, j, new QTableWidgetItem(v.toString()));

            //table->item(i, j)->setData(Qt::UserRole, query.value(0).toInt());
        }

        i++;
    }

    query.finish();

    // pour que la largeur des colonnes soit automatiquement mise à jour
    // pour s'accorder au contenu
    table->resizeColumnsToContents();
}

void SQLTable::setFilter(const QString& column, Filter filter)
{
    if(!columns.contains(column))
        return;

    filters[column] = filter;
}

QTableWidget* SQLTable::getWidget() const
{
    return table;
}

QTableWidgetItem* SQLTable::getSelectedItem() const
{
    return table->selectedItems()[0];
}

void SQLTable::addColumns(const QString &origin_table, const QStringList &columns)
{
    // on préfixe les noms des colonnes par le nom de la table à laquelle elles
    // appartiennent
    QString col;
    foreach(col, columns)
    {
        this->columns.append(QString(origin_table) + "." + col);
    }
}

void SQLTable::join(const QString &table, const QStringList &cols)
{
    if(to_join.contains(table))
        return;

    to_join.append(table);

    addColumns(table, cols);

    foreach(QString col, cols)
    {
        this->labels.append(DBController::getInstance()->getLabel(table, col));
    }

    emit tableModified();
}
