#ifndef POSITION_CODE_H
#define POSITION_CODE_H

#include <stdbool.h>
#include "struct.h" 
#include "package.h"  // 包含包裹结构体定义

// 货架区类型枚举
typedef enum {
    LARGE_AREA,      // 大件区（货架A-D）
    MEDIUM_AREA,     // 中件区（货架E-I）
    SMALL_AREA,      // 小件区（货架J-N）
    URGENT_AREA,     // 加急区（货架O-S）
    DISABLED_AREA    // 残障用户区（货架T-X）
} ShelfAreaType;

// 货架区配置结构体
typedef struct {
    char base_char;      // 起始字母（如'A'）
    int shelf_count;     // 货架数量
    int current_shelf;   // 当前轮询货架索引
    int counters[24];    // 每个货架的包裹计数器
} ShelfArea;

char* assign_position_code(struct package* pkg, enum user_type user_type);

#endif