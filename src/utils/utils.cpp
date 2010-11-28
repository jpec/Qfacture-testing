#include "utils/utils.h"

#include <QDate>


QVariant displayDate(QVariant date)
{
    return QDate::fromString(date.toString(), Qt::ISODate)
                 .toString(Qt::SystemLocaleShortDate);
}

QVariant displayPhone(QVariant phone)
{
    QString tel = phone.toString();

    if(tel.isEmpty())
        return tel;

    tel.insert(2, ' ');

    int i=5;
    while(i < tel.size())
    {
        tel.insert(i, ' ');
        i+=3;
    }

    return tel;
}
