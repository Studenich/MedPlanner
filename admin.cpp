#include "admin.h"

Admin::Admin()
{
    representatives = new Representative;
}

Admin::~Admin()
{
    delete representatives;
}
