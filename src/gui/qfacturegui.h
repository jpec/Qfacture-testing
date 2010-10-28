#ifndef QFACTUREGUI_H
#define QFACTUREGUI_H

#include <QMainWindow>
#include "qfacturecore.h"

namespace Ui {
    class QfactureGui;
}

class QfactureGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit QfactureGui(QfactureCore *core, QWidget *parent = 0);
    ~QfactureGui();
    
private slots:
    void DBConnect();
    void onDBConnected();
    void onDBConnectionError(const QString &error);

private:
    void setupActions();
    
    Ui::QfactureGui *ui;
    QfactureCore *core;
};

#endif // QFACTUREGUI_H
