#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLATE_LEN 20
#define HASH_SIZE 101      // 桶的个数，取一个素数能减少冲突

/* 链表节点 */
typedef struct CarNode {
    char plate[PLATE_LEN];    // 车牌（键）
    char brand[20];
    char color[20];
    int  hours;
    struct CarNode *next;     // 指向同一桶的下一个节点
} CarNode;

/* 哈希表：一个指针数组，每个元素是一个链表的头指针 */
CarNode *hash_table[HASH_SIZE] = {NULL};

/* 简单哈希函数：字符 ASCII 码求和后取模 */
unsigned int hash(const char *plate) {
    unsigned int sum = 0;
    while (*plate) {
        sum += (unsigned char)*plate;
        plate++;
    }
    return sum % HASH_SIZE;
}

/* 添加车辆 */
int add_car(const char *brand, const char *plate, const char *color, int hours) {
    unsigned int idx = hash(plate);

    // 检查是否已存在该车牌
    CarNode *cur = hash_table[idx];
    while (cur != NULL) {
        if (strcmp(cur->plate, plate) == 0)
            return -1;   // 重复车牌
        cur = cur->next;
    }

    // 新建节点
    CarNode *new_node = (CarNode*)malloc(sizeof(CarNode));
    strncpy(new_node->plate, plate, PLATE_LEN - 1);
    strncpy(new_node->brand, brand, 19);
    strncpy(new_node->color, color, 19);
    new_node->hours = hours;

    // 头插法插入链表（方便，O(1)）
    new_node->next = hash_table[idx];
    hash_table[idx] = new_node;
    return 0;
}

/* 查找车辆，返回节点指针（NULL 表示未找到） */
CarNode* find_car(const char *plate) {
    unsigned int idx = hash(plate);
    CarNode *cur = hash_table[idx];
    while (cur != NULL) {
        if (strcmp(cur->plate, plate) == 0)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

/* 删除车辆 */
int delete_car(const char *plate) {
    unsigned int idx = hash(plate);
    CarNode *cur = hash_table[idx];
    CarNode *prev = NULL;

    while (cur != NULL) {
        if (strcmp(cur->plate, plate) == 0) {
            if (prev == NULL)
                hash_table[idx] = cur->next;   // 删除头节点
            else
                prev->next = cur->next;         // 删除中间节点
            free(cur);
            return 0;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1;   // 未找到
}

/* 打印所有车辆（遍历整个哈希表） */
void print_all() {
    printf("--- 停车场车辆列表 ---\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        CarNode *cur = hash_table[i];
        while (cur != NULL) {
            printf("车牌:%s  品牌:%s  颜色:%s  时长:%d小时\n",
                   cur->plate, cur->brand, cur->color, cur->hours);
            cur = cur->next;
        }
    }
    printf("----------------------\n");
}

int main() {
    add_car("奔驰", "京A12345", "黑色", 4);
    add_car("奥迪", "沪B67890", "白色", 6);
    add_car("保时捷", "鄂A42673", "红色", 9);
    add_car("宝马", "粤A56732", "黑色", 3);

    print_all();

    // 查找
    CarNode *found = find_car("沪B67890");
    if (found != NULL)
        printf("找到：颜色是 %s\n\n", found->color);
    else
        printf("未找到该车\n\n");

    // 删除
    delete_car("京A12345");
    printf("删除 京A12345 后：\n");
    print_all();

    return 0;
}