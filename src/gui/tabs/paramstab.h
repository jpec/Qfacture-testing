#ifndef ParamsTab_H
#define ParamsTab_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>


class ParamsTab : public QWidget
{
    Q_OBJECT
public:
    explicit ParamsTab(QWidget *parent = 0);
    ~ParamsTab();

private:
    void buildLayout();


    QHBoxLayout *layout;
    QHBoxLayout *gbox_profile_layout;
    QHBoxLayout *gbox_db_layout;

    QGroupBox *gbox_profile;
    QGroupBox *gbox_db;
};

#endif // ParamsTab_H
