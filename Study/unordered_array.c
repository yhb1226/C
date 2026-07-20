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

int add_car(const char *plate, const char *owner, int hours) {
    if (car_count >= MAX_CARS) return -1;
    strncpy(parking_lot[car_count].plate, plate, PLATE_LEN-1);
    strncpy(parking_lot[car_count].owner, owner, 49);
    parking_lot[car_count].parked_hours = hours;
    car_count++;
    return 0;
}

int find_car(const char *plate) {
    for (int i = 0; i < car_count; i++) {
        if (strcmp(parking_lot[i].plate, plate) == 0)
            return i;
    }
    return -1;
}

int delete_car(const char *plate) {
    int pos = find_car(plate);
    if (pos == -1) return -1;
    if (pos != car_count - 1) {
        parking_lot[pos] = parking_lot[car_count - 1];
    }
    car_count--;
    return 0;
}

void print_all() {
    printf("当前停车场有 %d 辆车:\n", car_count);
    for (int i = 0; i < car_count; i++) {
        printf("[%d] 车牌:%s  车主:%s  已停:%d 小时\n",
               i, parking_lot[i].plate,
               parking_lot[i].owner,
               parking_lot[i].parked_hours);
    }
    printf("\n");
}

int main() {
    add_car("京A12345", "张三", 2);
    add_car("沪B67890", "李四", 5);
    add_car("粤C99999", "王五", 1);
    print_all();

    // 查找
    int idx = find_car("沪B67890");
    if (idx != -1)
        printf("找到：车主是 %s\n\n", parking_lot[idx].owner);

    // 删除
    delete_car("京A12345");
    print_all();

    return 0;
}