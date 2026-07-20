#include <stdio.h>
#include <string.h>

#define PLATE_LEN 20
#define MAX_CAR 100

typedef struct {
    char car_brand[20];
    char car_plate[PLATE_LEN];
    char car_color[20];
    int  car_hours;
}car_configure;

car_configure All_packing[MAX_CAR];

int car_count = 0;

int add_car (const char *brand, const char *plate, const char *color, int hours)
{
    if(car_count >= 20){return -1;}
    strncpy(All_packing[car_count].car_brand, brand, 20-1);
    strncpy(All_packing[car_count].car_plate, plate, PLATE_LEN-1);
    strncpy(All_packing[car_count].car_color, color, 20-1);
    All_packing[car_count].car_hours = hours;

    car_count++;
    return 0;
}

int find_car (const char *plate)
{
    for(int i=0; i<car_count; i++)
    {
        if(strcmp(All_packing[i].car_plate, plate) == 0)
        {
            return i;
        }
        
    }
    return -1;
}

int main()
{
    add_car("奔驰", "京A12345", "黑色", 4);
    add_car("奥迪", "沪B67890", "白色", 6);
    add_car("保时捷", "鄂A42673", "红色", 9);
    add_car("宝马", "粤A56732", "黑色", 3);

    int idx = find_car("沪B67890");
    if (idx != -1)
        printf("找到：车的品牌是  %s\n\n ，车颜色是 %s\n\n", All_packing[idx].car_brand, All_packing[idx].car_color);
    return 0;
}
