#include "billing.h"
#include <math.h>

// 重量计费：首重1kg 10元，续重每0.5kg 5元（向上取整）
static float _calculate_base_fee(float weight) {
    if (weight <= 1.0f) return 10.0f;
    float exceed_weight = weight - 1.0f;
    int exceed_units = (int)ceil(exceed_weight / 0.5f); // 向上取整
    return 10.0f + exceed_units * 5.0f;
}

// 用户折扣率映射表
static float _get_user_discount(enum user_type user_type) {
    switch (user_type) {
        case student:    return 0.8f;  // 学生8折
        case teacher:    // 教职工7折
        case bussiness: return 0.7f;  // 商家7折
        case disabled:   return 0.1f;  // 残障人士1折
        default:         return 1.0f;  // 普通用户无折扣
    }
}

// 总运费计算（严格按用户规则分步计算）
float calculate_total_fee(const struct pack_category* category, enum user_type user_type) {
    // 1. 计算基础运费（重量）
    float total_fee = _calculate_base_fee(category->weight);

    // 2. 加急费用（urgency=true时加收1.5倍）
    if (category->urgency) {
        total_fee *= 1.5f;
    }

    // 3. 易碎品附加费（总运费 ×10%）
    if (category->delicacy) {
        total_fee += total_fee * 0.1f;
    }

    // 4. 保价费（保价费 = 当前总费用 ×0.5%，在用户折扣前计算）
    if (category->insurance) {
        total_fee += total_fee * 0.005f;
    }

    // 5. 应用用户折扣（最后一步）
    total_fee *= _get_user_discount(user_type);

    // 返回结果（保留两位小数）
    return roundf(total_fee * 100) / 100;
}