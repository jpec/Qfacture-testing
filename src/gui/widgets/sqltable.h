#ifndef SQLTABLE_H
#define SQLTABLE_H

#include <QTableWidget>


class SQLTable : public QObject
{
    Q_OBJECT
public:
    explicit SQLTable(const QString &table_name, QWidget *parent = 0);
    ~SQLTable();

    /**
     * Définit les colonnes à afficher dans le tableau.
     *
     * @param columns HashMap des correspondances clé en DB <-> Nom de la colonne
     */
    void setColumns(const QHash<QString, QString> &columns);

    /**
     * Retourne le widget correspondant au tableau
     *
     * @return QTableWidget* Le widget
     */
    QTableWidget *getWidget() const;

signals:
    /**
     * Émit dès que la structure du tableau est modifiée (colonnes
     * par ex)
     */
    void tableModified();

    /**
     * Émit lorsque une erreur lors d'une requête à la DB survient
     *
     * @param error Le message d'erreur retourné
     */
    void DBError(const QString &error);

    /**
     * Émit lorsque l'utilisateur clique sur un élément du tableau
     */
    void itemClicked(QTableWidgetItem *item);

public slots:
    /**
     * Interroge la base de données pour remplir le tableau
     */
    void feedTable();

private slots:
    /**
     * Construit la structure du tableau.
     */
    void buildTable();

private:
    /**
     * Colonnes du tableau
     */
    QHash<QString, QString> columns;

    /**
     * Tableau
     */
    QTableWidget *table;

    /**
     * Nom de la table en DB à interroger
     */
    QString table_name;
};

#endif // SQLTABLE_H
