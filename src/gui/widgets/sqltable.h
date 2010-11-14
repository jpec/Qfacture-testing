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
     * @param columns Liste des colonnes du tableau
     * @param labels Libellés des colonnes
     */
    void setColumns(const QList<QString> &columns, const QList<QString> &labels);

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
     * Émit lorsque l'utilisateur clique ou se déplace sur un élément du tableau
     */
    void itemSelected(QTableWidgetItem *item);

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

    /**
     * Lorsque la selection change
     */
    void selectionChanged();

private:
    /**
     * Colonnes du tableau
     */
    QList<QString> columns;

    /**
     * Libellés des colonnes
     */
    QList<QString> labels;

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
