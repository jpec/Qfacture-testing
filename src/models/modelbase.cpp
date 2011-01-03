#include "modelbase.h"

bool ModelBase::isNew() const
{
    return getId() == 0;
}
