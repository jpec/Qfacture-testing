#ifndef INVOICETAB_H
#define INVOICETAB_H

#include "qfacturecore.h"
#include "gui/widgets/sqltable.h"

#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>

class InvoiceTab : public QWidget
{
    Q_OBJECT
public:
    explicit InvoiceTab(QfactureCore *core, QWidget *parent = 0);
    ~InvoiceTab();

public slots:
    /**
     * (Dés)active l'onglet
     *
     * @param state État d'activation de l'onglet
     */
    void setEnabled(bool state=true);

    /**
     * Recharge la facture à partir de la DB
     */
    void loadInvoice();

private:

    /**
     * Pointeur vers le contrôleur principal
     */
    QfactureCore *core;
};

#endif // INVOICETAB_H
