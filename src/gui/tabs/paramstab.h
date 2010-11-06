#ifndef PARAMSTAB_H
#define PARAMSTAB_H

#include <QWidget>

namespace Ui {
    class ParamsTab;
}

class ParamsTab : public QWidget
{
    Q_OBJECT

public:
    explicit ParamsTab(QWidget *parent = 0);
    ~ParamsTab();

private:
    Ui::ParamsTab *ui;
};

#endif // PARAMSTAB_H
