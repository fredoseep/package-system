#include "package.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 创建包裹节点
Package* create_package(long id, char position_code[51], Pack_category category, long pickup_code, const char* user_name, PackageStatus status) {
    Package* new_pkg = (Package*)malloc(sizeof(Package));
    if (!new_pkg) {
        fprintf(stderr, "错误：内存分配失败\n");
        return NULL;
    }
    new_pkg->id = id;
    strncpy(new_pkg->position_code, position_code, 50);
    new_pkg->position_code[50] = '\0'; // 防止溢出
    new_pkg->category = category;
    new_pkg->pickup_code = pickup_code;
    strncpy(new_pkg->user_name, user_name, 50);
    new_pkg->user_name[50] = '\0';
    new_pkg->state = status;
    new_pkg->pnext = NULL;
    return new_pkg;
}

// 添加包裹到链表尾部
void add_package(Package** phead, Package* new_pkg) {
    if (*phead == NULL) {
        *phead = new_pkg;
    }
    else {
        Package* current = *phead;
        while (current->pnext != NULL) {
            current = current->pnext;
        }
        current->pnext = new_pkg;
    }
}

// 根据ID删除包裹（返回是否成功）
bool delete_package(Package** phead, long id) {
    Package* prev = NULL, * current = *phead;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->pnext;
    }
    if (current == NULL) {
        fprintf(stderr, "错误：未找到包裹 %ld\n", id);
        return false;
    }
    if (prev == NULL) {
        *phead = current->pnext; // 删除头节点
    }
    else {
        prev->pnext = current->pnext; // 删除中间或尾节点
    }
    free(current);
    return true;
}

// 根据用户名查找包裹
Package* find_package(Package* phead, char* user_name) {
    Package* current = phead;
    while (current != NULL) {
        if (strcmp(current->user_name, user_name)) return current;
        current = current->pnext;
    }
    return NULL;
}

// 根据取件码查找包裹
Package* find_package_by_pickup_code(Package* phead, long pickup_code) {
    Package* current = phead;
    while (current != NULL) {
        if (current->pickup_code == pickup_code) return current;
        current = current->pnext;
    }
    return NULL;
}

// 保存链表数据到文件（字段用逗号分隔）
void save_to_file(Package* phead, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("错误：文件打开失败");
        return;
    }
    Package* current = phead;
    while (current != NULL) {
        fprintf(file, "%ld,%s,%d,%d,%d,%f,%d,%ld,%s,%d\n",
            current->id,
            current->position_code,
            current->category.size,
            current->category.delicacy,
            current->category.urgency,
            current->category.weight,
            current->category.insurance,
            current->pickup_code,
            current->user_name,
            current->state);
        current = current->pnext;
    }
    fclose(file);
}

// 从文件加载数据到链表
void load_from_file(Package** phead, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("错误：文件打开失败");
        return;
    }
    long id, pickup_code;
    char position_code[51], user_name[51];
    Pack_category category;
    int size, state;
    while (fscanf(file, "%ld,%50[^,],%d,%d,%d,%f,%d,%ld,%50[^,],%d\n",
        &id,
        position_code,
        &size,
        &category.delicacy,
        &category.urgency,
        &category.weight,
        &category.insurance,
        &pickup_code,
        user_name,
        &state) == 10) {
        category.size = (enum size)size;
        Package* pkg = create_package(id, position_code, category, pickup_code, user_name, (PackageStatus)state);
        add_package(phead, pkg);
    }
    fclose(file);
}

// 打印单个包裹信息
void print_package(Package* pkg) {
    if (!pkg) {
        printf("错误：包裹不存在\n");
        return;
    }
    const char* size_str[] = { "小件", "中件", "大件" };
    const char* state_str[] = { "在途（用户）", "在库", "已取件", "退回", "误领", "在途（其他）" };
    printf("----- 包裹详情 -----\n");
    printf("包裹ID: %ld\n", pkg->id);
    printf("驿站位置: %s\n", pkg->position_code);
    printf("用户ID: %s\n", pkg->user_name);
    printf("取件码: %ld\n", pkg->pickup_code);
    printf("尺寸: %s | 重量: %.2fkg\n", size_str[pkg->category.size], pkg->category.weight);
    printf("易碎: %s | 加急: %s | 保价: %s\n",
        pkg->category.delicacy ? "是" : "否",
        pkg->category.urgency ? "是" : "否",
        pkg->category.insurance ? "是" : "否");
    printf("状态: %s\n", state_str[pkg->state]);
    printf("--------------------\n");
}

// 打印所有包裹
void print_all_packages(Package* phead) {
    Package* current = phead;
    if (!current) {
        printf("包裹列表为空\n");
        return;
    }
    printf("======= 所有包裹 =======\n");
    while (current != NULL) {
        print_package(current);
        current = current->pnext;
    }
    printf("=======================\n");
}

// 释放链表内存
void free_package_list(Package* phead) {
    Package* tmp;
    while (phead != NULL) {
        tmp = phead;
        phead = phead->pnext;
        free(tmp);
    }
}