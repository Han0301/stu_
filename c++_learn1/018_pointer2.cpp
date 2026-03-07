//
// Created by 29873 on 25-6-1.
//
/* 野指针与空指针
 *      野指针: 被声明但是并未初始化(赋值)的指针, 会导致这个指针会指向随机的其他的内存地址, 可能会倒是未知的问题
 *      所以 声明后所分配的地址, 不一定是干净的, 需要初始化进行赋值
 *          int * p;
 *          * p = 10;       // 向未知的, 随机的4字节的内存区域, 修改存储值为10
 *      注: 所以尽量不要修改 野指针, 会修改未知的数据, 具有数据的安全隐患
 *      空指针: 为了避免空指针, 可以将指针设置为空指针, 下面的两种方式都可以声明空指针
 *          int * p = NULL;     // NULL 为一种宏
 *          int * p = nullptr;      // nullptr 作为一种关键字
 *      注:一般也不推荐使用空指针, 只有在需要指针, 但需要延迟赋值的场景下才作为过渡使用
 * 指针的运算
 *      指针运算对指针的基础操作, 非常适合用于操纵数组并配合做动态的内存分配
 *      若p 为指针, n 为数字, 常用的有: p + n, p - n ,还有 p-- , p++
 *      对于指针运算的结果, 与内存区域的数据类型息息相关
 *          对于char 型, p++, 地址 +1
 *          对于int 型, p++, 地址 +4
 *          对于double 型, P++, 地址 +8
 *          即: 指针+n, 内存地址 +n * 类型大小
 *      指针也可以用下标, 如p[0],p[1] 等同于 *(p + 0), *(p + 1)
 */
#include "iostream"
using namespace std;
int main() {
    // 野指针:
    // int * p;
    // * p = 10;

    // 定义空指针
    int * p1 = NULL;
    int * p2 = nullptr;

    int num = 10;
    int *p3 = &num;
    cout << "p = " << p3 << endl;       //p = 0xb67b7ff724
    p3++;
    cout << "p = " << p3 << endl;       //p = 0xb67b7ff728, 加上 4
    double num2 = 10.00;
    double * p32 = &num2;
    cout << "p = " << p32 << endl;
    p32++;
    cout << "p = " << p32 << endl;

    int array[] = {1,2,3,4,5};
    int * array_0 = &array[0];
    int * array_1 = array;      // 可以直接用数组名称, 不用 & , 因为数组名称存储的就是数组中第一个元素的地址
    cout << "array_0 = " << array_0 << ", array_1 = " << array_1 << endl;       // *array[0] = 0xfd113ffcf0
    array_0 ++;
    cout << "array_1 = " << array_0 << endl;
    cout << "array[1] = " << *array_0 << endl;      // 通过++, 访问array_0 地址的下一个元素, 即 array[1]
    // 通过指针循环遍历出数组的值
    int v1[] = {1,2,3,4,5,6,7,8,9,10};
    char v2[] = {'a','b','c','d','e','f','g','h','i'};
    int * v1_place = v1;
    char * v2_place = v2;
    for (int i = 0; i <= sizeof(v1) / sizeof(v1[0]) - 1; i ++) {
        cout << "in v1, the No " << i + 1 << " is " << *v1_place << endl;
        v1_place ++;
    }
    for (int i = 0; i <= sizeof(v2) / sizeof(v2[0]) - 1; i ++) {
        cout << "in v2, the No " << i + 1 << " is " << *v2_place << endl;
        v2_place ++;
    }

    return 0;
}