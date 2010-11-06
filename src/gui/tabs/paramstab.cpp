#include "paramstab.h"
#include "ui_paramstab.h"

ParamsTab::ParamsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParamsTab)
{
    ui->setupUi(this);
}

ParamsTab::~ParamsTab()
{
    delete ui;
}
