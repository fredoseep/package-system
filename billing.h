#ifndef BILLING_H
#define BILLING_H

#include "struct.h"

float total_fee(const struct pack_category* category, enum user_type user_type);

#endif