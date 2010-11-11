#include "dbwidget.h"

DBWidget::DBWidget(QWidget *parent) : QWidget(parent)
{
    this->buildLayout();
}

DBWidget::~DBWidget()
{
    delete form_layout;
    delete layout;

    delete db_type;
    delete db_host;
    delete db_port;
    delete db_login;
    delete db_pass;
    delete db_base;

    delete btn_ok;
}


void DBWidget::buildLayout()
{
    // création des widgets
    btn_ok = new QPushButton(trUtf8("Connecter"), this);
    db_host = new QLineEdit(this);
    db_port = new QSpinBox(this);
    db_login = new QLineEdit(this);
    db_pass = new QLineEdit(this);
    db_base = new QLineEdit(this);
    db_type = new QComboBox(this);

    // création des layouts
    layout = new QVBoxLayout(this);
    form_layout = new QFormLayout();

    // construction du formulaire
    form_layout->addRow(trUtf8("Type"), db_type);
    form_layout->addRow(trUtf8("Hôte"), db_host);
    form_layout->addRow(trUtf8("Port"), db_port);
    form_layout->addRow(trUtf8("Utilisateur"), db_login);
    form_layout->addRow(trUtf8("Mot de passe"), db_pass);
    form_layout->addRow(trUtf8("Base"), db_base);

    // mise en place des layouts
    form_layout->setLabelAlignment(Qt::AlignLeft);

    layout->addLayout(form_layout);
    layout->addWidget(btn_ok);
    layout->addStretch(); // pour forcer le bouton à être collé au formulaire

    setLayout(layout);
}

void DBWidget::setDBAllowedTypes(const QStringList &types)
{
    db_type->addItems(types);
}
