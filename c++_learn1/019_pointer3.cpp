//
// Created by 29873 on 25-6-1.
//
/* 动态内存分配
 *      手动的进行内存的分配, 内存空间的释放等等内存管理操作
 *      使用场景: 对于在很长的代码中, 某个变量或数组, 声明使用往后, 后面的代码再也用不到了, 这时可以手动的去释放这部分的空间
 *      静态内存分配: 在变量, 数组等对象的创建时, 是由c++ 自动分配内存, 且不使用也不会自动删除
 *      new 与 delete 运算符
 *          new 用于申请并分配内存空间, 并指向该空间的指针
 *              基本语法:
 *              new type;       // 申请普通变量的内存空间
 *              new type[i];    // 申请数组的内存空间, i 表示数组的长度
 *          delete 用于释放内存, 仅能用于new 运算符自行申请的内存空间, 不要删除静态内存地址!!!
 *              基本语法:
 *              delete 指针;      // 释放普通变量的内存空间
 *              delete[] 指针;    // 删除数组的内存空间
 *          实例:
 *          int * p = new int;      // 申请内存空间的同时指定指针, 这样才能访问
 *          * p = 10;
 *          delete p;       // 释放内存空间
 *          int * p = new int[5];       // int * p = new int[5]{1,2,3,4,5}; 并赋值
 *          *p = 1;
 *          delete[] p;
 * 数组元素的移除
 *      c++ 未内置相关功能, 需要手动实现
 *      移除元素的核心思路:
 *          1. 通过new 操作符, 申请新数组的内存空间, 并赋值数据到新的数组
 *          2. 通过delete 删除旧数组的空间
 *          3. 将旧数组的指针, 指向新数组的指针
 *          注: 要处理好对应下标, 可使用 offset 偏移量辅助
 * 数组元素的插入
 *      核心思路:
 *          创建新数组,将老数组和待插入元素一起赋值到新元素
 *          循环新数组, 挨个进行元素的填充, 在非插入的位置填入老数组中的数
 *          注: 新元素的插入, 老数组的元素需要配合做下标增加
 */
#include "iostream";
using namespace std;
int main() {
    int * p = new int;
    * p = 10;
    cout << "*p = " << *p << endl;
    delete p;

    int * p_arr = new int[6];
    p_arr[0] = 1;
    delete[] p_arr;

    // 数组元素的移除
    int * parray = new int[5] {1,2,3,4,5};
    int * parray_new = new int[4];
    for (int i = 0; i <= 4; i++) {      // 循环遍历老数组
        if (i == 2){continue;}      // 删掉不用的元素

        if (i < 2){parray_new[i] = parray[i];}
        else if (i > 2) {parray_new[i - 1] = parray[i];}        // 处理好下标的对应
    }
    // 可选
    delete[] parray;    // 如果老数组不用, 回收老数组的空间
    parray = parray_new;    // 将旧数组的指针, 指向新数组的指针
    for (int i = 0; i <= 3; i++) {
        cout << parray[i] << endl;
        cout << parray_new[i] << endl;      // 这时 parray 和 parray_new 都指向修改后的数组
    }

    int * p_array = new int[10] {1,2,3,4,5,6,7,8,9,10};
    // 要求 删除这里的3,7 (多元素删除), 定义offset 偏移量
    int * p_array_new = new int[8];
    int offset = 0;
    for (int i = 0; i <= 9; i++) {
        if (i == 2 || i == 6) {
            offset += 1;
        }
        else{p_array_new[i - offset] = p_array[i];}
    }
    delete[] p_array;
    p_array = parray_new;
    for (int i = 0; i <= 7; i++) {cout << p_array_new[i] << endl;}
    // 插入新元素
    int * p_in_array = new int[8] {1,2,3,4,5,7,8,10};
    int * p_in_array_new = new int[10];
    int offset_ = 0;
    for (int i = 0; i <= 9; i++) {
        if (i == 5 || i == 8) {
            if (i == 5){p_in_array_new[i] = 6;}
            else{p_in_array_new[i] = 9;}
            // 插入新元素
            offset_ += 1;
        }else{p_in_array_new[i] = p_in_array[i - offset_];}     // 注意好下标的对应关系
    }
    for (int i = 0; i <= 9; i++) {cout << " " << p_in_array_new[i];}
    return 0;
}