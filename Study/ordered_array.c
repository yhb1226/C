#include <stdio.h>
#include <string.h>

#define MAX_CARS 100
#define PLATE_LEN 20

typedef struct {
    char plate[PLATE_LEN];
    char owner[50];
    int  parked_hours;
} Car;

Car parking_lot[MAX_CARS];
int car_count = 0;

// 有序插入：按车牌号从小到大排列（字典序）
int add_car_sorted(const char *plate, const char *owner, int hours) {
    if (car_count >= MAX_CARS) return -1;

    // 找到插入位置
    int pos = 0;
    while (pos < car_count && strcmp(parking_lot[pos].plate, plate) < 0) {
        pos++;
    }

    // 如果车牌已存在，可以选择拒绝或覆盖，这里拒绝
    if (pos < car_count && strcmp(parking_lot[pos].plate, plate) == 0) {
        return -2; // 车牌重复
    }

    // 将 pos 及之后的元素整体后移一位
    for (int i = car_count; i > pos; i--) {
        parking_lot[i] = parking_lot[i - 1];
    }

    // 插入新元素
    strncpy(parking_lot[pos].plate, plate, PLATE_LEN - 1);
    strncpy(parking_lot[pos].owner, owner, 49);
    parking_lot[pos].parked_hours = hours;
    car_count++;

    return 0;
}

// 二分查找：返回下标，找不到返回 -1
int find_car_sorted(const char *plate) {
    int left = 0, right = car_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(parking_lot[mid].plate, plate);
        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// 有序删除：找到后把后面元素前移
int delete_car_sorted(const char *plate) {
    int pos = find_car_sorted(plate);   // O(log n) 查找
    if (pos == -1) return -1;

    // 后面的元素整体前移一位
    for (int i = pos; i < car_count - 1; i++) {
        parking_lot[i] = parking_lot[i + 1];
    }
    car_count--;
    return 0;
}

void print_all() {
    printf("当前停车场有 %d 辆车:\n", car_count);
    for (int i = 0; i < car_count; i++) {
        printf("[%d] 车牌:%-10s 车主:%-6s 已停:%d 小时\n",
               i, parking_lot[i].plate,
               parking_lot[i].owner,
               parking_lot[i].parked_hours);
    }
    printf("\n");
}

int main() {
    // 插入时自动保持有序
    add_car_sorted("沪B67890", "李四", 5);
    add_car_sorted("京A12345", "张三", 2);
    add_car_sorted("粤C99999", "王五", 1);
    print_all();

    // 二分查找
    int idx = find_car_sorted("沪B67890");
    if (idx != -1)
        printf("找到：车主是 %s\n\n", parking_lot[idx].owner);

    // 删除
    delete_car_sorted("京A12345");
    print_all();

    return 0;
}