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

    /**
     * Définit une condition LIKE %like_filter% dans la clause Where de la requête
     *
     * @param like_filter_field Nom du champ
     * @param like_filter Valeur à tester
     */
    void setLikeFilter(const QString &like_filter_field, const QVariant &like_filter);

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
     * Clause à ajouter dans la clause WHERE sous forme de LIKE %like_filter%
     */
    QVariant like_filter;

    /**
     * Champ sur lequel appliquer le filtre LIKE
     */
    QString like_filter_field;

    /**
     * Nom de la table en DB à interroger
     */
    QString table_name;
};

#endif // SQLTABLE_H
