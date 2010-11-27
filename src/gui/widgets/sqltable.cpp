#include "sqltable.h"
#include "controllers/dbcontroller.h"

#include <QSqlQuery>
#include <assert.h>


SQLTable::SQLTable(const QString &table_name, QWidget *parent) : QObject(parent)
{
    table = new QTableWidget(parent);
    this->table_name = table_name;

    connect(this, SIGNAL(tableModified()), this, SLOT(buildTable()));
    connect(table, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
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

void SQLTable::setColumns(const QList<QString> &columns, const QList<QString> &labels)
{
    if(columns.count() != labels.count())
        return;

    this->columns = columns;
    this->labels =labels;

    emit tableModified();
}


void SQLTable::buildTable()
{
    table->clear();

    table->setAlternatingRowColors(true);
    table->setSortingEnabled(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->setColumnCount(columns.count());
    table->setHorizontalHeaderLabels(QStringList(labels));

    feedTable();
}


void SQLTable::feedTable()
{
    QString where;
    QSqlQuery query;
    QString fields = QStringList(columns).join(",");
    int i, j, nb_cols = columns.count();

    if(columns.count() == 0 || !DBController::getInstance()->isDBConnected())
        return;

    table->clearContents();

    if(!like_filter.toString().isEmpty())
        where = "WHERE "+like_filter_field+" LIKE :like_filter ";

    query.prepare(
        "SELECT id, "+fields+" "
        "FROM "+table_name+" "
        +where+
        "ORDER BY id ASC"
    );

    if(!like_filter.toString().isEmpty())
        query.bindValue(":like_filter", like_filter);

    if(!DBController::getInstance()->exec(query))
        return;

    table->setRowCount(query.size());

    i = 0;
    while(query.next()) {
        for(j=0; j < nb_cols; ++j) {
            table->setItem(i, j, new QTableWidgetItem(query.value(j+1).toString()));

            table->item(i, j)->setData(Qt::UserRole, query.value(0).toInt());
        }

        i++;
    }

    query.finish();

    // pour que la largeur des colonnes soit automatiquement mise à jour
    // pour s'accorder au contenu
    table->resizeColumnsToContents();

}

QTableWidget* SQLTable::getWidget() const
{
    return table;
}
