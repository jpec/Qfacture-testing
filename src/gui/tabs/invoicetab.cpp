#include "invoicetab.h"
#include "controllers/dbcontroller.h"

InvoiceTab::InvoiceTab(QfactureCore *core, QWidget *parent) :
        QWidget(parent)
{
    this->core = core;

    this->loadInvoice();
}

InvoiceTab::~InvoiceTab()
{


}

void InvoiceTab::loadInvoice()
{
    if(!core->isDBConnected())
        return;
}

void InvoiceTab::setEnabled(bool state)
{

}
