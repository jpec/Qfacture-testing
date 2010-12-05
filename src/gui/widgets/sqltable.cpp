#include "sqltable.h"
#include "controllers/dbcontroller.h"

#include <assert.h>
#include <QSqlQuery>


SQLTable::SQLTable(const QString &table_name, QWidget *parent) : QObject(parent)
{
    table = new QTableWidget(parent);
    this->table_name = table_name;

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
    QString fields = QStringList(columns).join(", "), query_sql, table_to_join;
    int i, j, nb_cols = columns.count();

    if(columns.count() == 0 || !DBController::getInstance()->isDBConnected())
        return;

    table->clearContents();

    /** construction de la requête **/

    query_sql = "SELECT "+table_name+".id, "+fields+" FROM "+table_name+" ";

    foreach(table_to_join, to_join)
    {
        query_sql.append("LEFT JOIN "+table_to_join+" ON "+
                         DBController::getInstance()->getJoinClause(table_name, table_to_join)+
                         " ");
    }

    if(!like_filter.toString().isEmpty())
        query_sql.append("WHERE "+like_filter_field+" LIKE :like_filter ");

    query_sql.append("ORDER BY "+table_name+".id ASC");

    /** exécution de la requête **/
    query.prepare(query_sql);

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

            table->item(i, j)->setData(Qt::UserRole, query.value(0).toInt());
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
