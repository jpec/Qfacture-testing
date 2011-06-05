#include "templatetab.h"

#include <QMessageBox>

TemplateTab::TemplateTab(QfactureCore *core, QWidget *parent) :
    QWidget(parent)
{
    this->core = core;

    this->buildLayout();
    this->createActions();
}

TemplateTab::~TemplateTab()
{
    delete layout;

}


void TemplateTab::buildLayout()
{
    // construction des layouts
    layout = new QVBoxLayout(this);

}

void TemplateTab::createActions()
{

}

void TemplateTab::setEnabled(bool state)
{

}
