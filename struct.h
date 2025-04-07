#pragma once
#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>
#include<time.h>
enum user_type { administrator, bussiness, student, disabled, teacher, civilian };

// 包裹状态枚举
enum state {
    waytousers,      // 在途（送往用户）
    storage,         // 在库
    already,         // 已取件
    returned,        // 退回
    mistaken,        // 误领
    lose,            // 丢失
    broken,          // 损坏
    wayto_others     // 在途（送往其他驿站）
};

// 包裹尺寸枚举
enum size {
    small,
    middle,
    large
};

// 包裹分类属性
struct pack_category
{
    enum size size;    // 尺寸
    bool delicacy;     // 是否易碎
    bool urgency;      // 是否加急
    float weight;      // 重量（kg）
    bool insurance;    // 是否保价

};
// 包裹结构体（链表节点）
struct package
{
    long id;                       // 包裹ID
    char position_code[51];        // 驿站位置
    struct pack_category category; // 包裹属性
    long pickup_code;              // 取件码
    char user_name[51];            // 用户ID
    enum state state;              // 当前状态
    struct package* pnext;         // 链表指针
    time_t take_time;              // 包裹取走日期
};
struct account
{
    char user_name[51];
    enum user_type type;
    char password[51];
    char phone_number[12];
    bool state;//0为封禁，1为未封禁
    struct account* next;
};
struct message
{
    char user_name[51];
    char note[300];
    struct message* next;
    struct message* pre;
    time_t time;

};

struct account user_account;

#endif
