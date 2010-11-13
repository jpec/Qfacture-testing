#include "sqltable.h"

#include <QSqlQuery>
#include <QSqlError>
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


void SQLTable::selectionChanged()
{
    assert(table->selectedItems().count() == 1);

    emit itemSelected(table->selectedItems()[0]);
}

void SQLTable::setColumns(const QHash<QString, QString> &columns)
{
    this->columns = columns;

    emit tableModified();
}


void SQLTable::buildTable()
{
    table->clear();

    table->setSortingEnabled(true);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    table->setColumnCount(columns.count());
    table->setHorizontalHeaderLabels(QStringList(columns.values()));

    feedTable();
}

void SQLTable::feedTable()
{
    QSqlQuery query;
    QString fields = QStringList(columns.keys()).join(",");
    int i, j, nb_cols = columns.count();

    if(columns.count() == 0)
        return;

    table->clearContents();

    query.prepare(
        "SELECT id, "+fields+" "
        "FROM "+table_name+" "
        "ORDER BY id ASC"
    );

    if(!query.exec())
    {
        emit DBError(query.lastError().databaseText());

        return;
    }

    table->setRowCount(query.size());

    i = 0;
    while(query.next()) {
        for(j=0; j < nb_cols; ++j) {
            table->setItem(i, j, new QTableWidgetItem(query.value(j+1).toString()));

            table->item(i, j)->setData(Qt::UserRole, query.value(0).toInt());
        }


        i++;
    }

    // pour que la largeur des colonnes soit automatiquement mise à jour
    // pour s'accorder au contenu
    table->resizeColumnsToContents();

}

QTableWidget* SQLTable::getWidget() const
{
    return table;
}
