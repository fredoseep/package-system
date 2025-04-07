
#ifndef PACKAGE_H
#define PACKAGE_H

#include <stdbool.h>
#include "struct.h"

// 包裹尺寸枚举
typedef enum size Size;

// 包裹状态枚举
typedef enum state PackageStatus;

// 包裹分类属性
typedef struct pack_category Pack_category;

// 包裹结构体（链表节点）
typedef struct package Package;

// 函数声明
Package* create_package(long id, char position_code[51], Pack_category category, long pickup_code, char* user_name, PackageStatus status);
void add_package(Package** phead, Package* new_pkg);
bool delete_package(Package** phead, long id);
Package* find_package(Package* phead, long id);
Package* find_package_by_pickup_code(Package* phead, long pickup_code);
void save_to_file(Package* phead, const char* filename);
void load_from_file(Package** phead, const char* filename);
void print_package(Package* pkg);
void print_all_packages(Package* phead);
void free_package_list(Package* phead);

#endif                