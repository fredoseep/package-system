#pragma once

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

// 创建包裹节点
Package* create_package(long id, char position_code[5], Pack_category category, long pickup_code, char* user_name, PackageStatus status);

// 添加包裹到链表尾部
void add_package(Package** phead, Package* new_pkg);

// 根据ID删除包裹（返回是否成功）
bool delete_package(Package** phead, long id);

// 根据ID查找包裹
Package* find_package_by_package_id(Package* phead, long id);

// 根据驿站位置查找包裹       
Package** find_packages_by_package_shelf(Package* phead, const char* position_shelf, int* count);

// 根据包裹状态查找包裹
Package** find_packages_by_package_state(Package* phead, PackageStatus state, int* found_count);

// 保存链表数据到文件
void save_to_file(Package* phead);

// 从文件加载数据到链表
void load_from_file(Package** phead);

//管理员 打印单个包裹信息
void print_package_for_administrator(Package* pkg);

//用户 打印单个包裹信息
void print_package_for_user(Package* pkg);

// 打印所有包裹
void print_all_packages(Package* phead);

// 释放链表内存
void free_package_list(Package* phead);


#endif                