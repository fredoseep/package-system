#ifndef BILLING_H
#define BILLING_H

#include "struct.h"

/**
 * @brief 计算包裹的总运费（严格遵循用户计费规则）
 * @param category 包裹属性（重量、加急、易碎、保价等）
 * @param user_type 用户类型（学生、教职工等）
 * @return 总运费（单位：元，精确到小数点后两位）
 */
float calculate_total_fee(const struct pack_category* category, enum user_type user_type);

#endif