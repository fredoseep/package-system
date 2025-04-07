#include "position_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 货架区配置表
static ShelfArea areas[] = {
    [LARGE_AREA] = {'A', 4, 0, {0}},  // 大件区：A-D（4个货架）
    [MEDIUM_AREA] = {'E', 5, 0, {0}},  // 中件区：E-I（5个货架）
    [SMALL_AREA] = {'J', 5, 0, {0}},  // 小件区：J-N（5个货架）
    [URGENT_AREA] = {'O', 5, 0, {0}},  // 加急区：O-S（5个货架）
    [DISABLED_AREA] = {'T', 5, 0, {0}}  // 残障用户区：T-X（5个货架）
};

// 分配位置码
char* assign_position_code(struct package* pkg, enum user_type user_type) {
    ShelfAreaType area_type;

   
    if (pkg->category.urgency) {
        area_type = URGENT_AREA;
    }
   
    else if (user_type == disabled) {
        area_type = DISABLED_AREA;
    }

    else {
        switch (pkg->category.size) {
        case large:  area_type = LARGE_AREA; break;
        case middle: area_type = MEDIUM_AREA; break;
        case small:  area_type = SMALL_AREA; break;
        default: return NULL; // 无效尺寸
        }
    }

  
    ShelfArea* area = &areas[area_type];

    // 从第一个货架开始顺序查找
    for (int shelf_idx = 0; shelf_idx < area->shelf_count; shelf_idx++) {
        if (area->counters[shelf_idx] < 50) {
            // 生成位置码
            char shelf_char = area->base_char + shelf_idx;
            int package_num = ++area->counters[shelf_idx]; // 递增编号

            // 格式化
            char* code = (char*)malloc(5);
            snprintf(code, 5, "%c%03d", shelf_char, package_num);

            // 更新轮询起点（下次从下一个货架开始）
            area->current_shelf = (shelf_idx + 1) % area->shelf_count;
            return code;
        }
    }

    // 所有货架已满
    fprintf(stderr, "[错误] %s区货架已满\n",
        (area_type == LARGE_AREA) ? "大件" :
        (area_type == MEDIUM_AREA) ? "中件" :
        (area_type == SMALL_AREA) ? "小件" :
        (area_type == URGENT_AREA) ? "加急" : "残障用户");
    return NULL;
}

