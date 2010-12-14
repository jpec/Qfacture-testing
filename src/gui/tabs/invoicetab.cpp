#include "invoicetab.h"
#include "controllers/dbcontroller.h"

InvoiceTab::InvoiceTab(Invoice invoice, QfactureCore *core, QWidget *parent) :
        QWidget(parent)
{
    this->core = core;
    this->invoice = invoice;

    this->loadInvoice();
}

InvoiceTab::~InvoiceTab()
{


}

void InvoiceTab::loadInvoice()
{
    // do sth here
}

void InvoiceTab::setEnabled(bool state)
{

}
