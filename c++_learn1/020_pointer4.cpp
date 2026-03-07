//
// Created by 29873 on 25-6-1.
//
/* 指针悬挂问题
 *      定义: 指针指向的区域已经被回收(即被delete了), 访问指针悬挂的指针每次都是随机的访问, 进行修改会导致数据安全问题
 *      经验: 不能轻易的进行指针之间的相互赋值(原指针若被删除, 赋值的指针就会悬挂)
 *           delete的指针确保100%不会在被使用
 * const 指针(常量指针)
 *      (1). 指向const的指针, 表示指向区域的数据是不可变的, 但是指针本身可以更换指向, 即 *p 不可变, p 可变
 *          语法: 将const写在 * 之前, 如 const 数据类型 * 指针, 数据类型 const * 指针
 *          例: int num1 = 10, num2 = 20;
 *              const int * p = 10;
 *              *p = 20;        // 会报错, 这里改变了 *p 下的值
 *              p = &num2;      // 这里改变了指针的指向
 *      (2).const指针, 表示指针本身的指向地址不可以修改, 但是指针内容可以修改(即 p 不能修改, *p 可以修改)
 *          注:必须要初始化地址, 因为指针的地址不能在修改了
 *          语法: 在 * 后, 数据类型 * const 指针 = 地址;
 *          例: int num1 = 10,num2 = 20;
 *              int * const p = &num1;
 *              p = &num2;      // 运行错误, 因为这里改变了指针的地址
 *              *p = 20;        // 可以正常改变内容
 *      (3).指向const的const指针: 指针和指针区域的值都不可以修改
 *          语法: const 数据类型 * const 指针名
 *      简记成: const 后直接跟指针, 表示指针指向不变, const 跟* 指针, 即指针内数据, 表示指针内数据不可变
 */
#include "iostream";
using namespace std;
int main() {
    int * p1 = new int;
    * p1 = 10;
    int *p2 = p1;
    cout << "p1 = " << p1 << ", p2 = " << p2 << endl;       // p1 = 0x13444d01ab0, p2 = 0x13444d01ab0
    delete p1;
    cout << "after delete, the p2 = " << p2 << ", *p2 = " << *p2 << endl;
        // after delete, the p2 = 0x24942c11ab0, *p2 = 1119974672
        // 这时每次运行, p2 和 *p2 的值每次都不同

    // const 指针
    int num1 = 10, num2 = 20;
    const int *p_num1 = &num1;      // 数据不可变
    cout << "for the const int * p_num1, the p_num1 is " << p_num1 << endl;
    p_num1 = &num2;     //改变指向
    cout << "for the const int * p_num1, the changed p_num1 is " << p_num1 << endl;
        //for the const int * p_num1, the p_num1 is 0xba109ffb04
        //for the const int *p_num1, the changed p_num1 is 0xba109ffb00
    int * const p_num2 = &num2;
    cout << "for the int * const p_num2, the * p_num2 is " << * p_num2 << endl;
    * p_num2 = 30;
    cout << "for the int * const p_num2, the * p_num2 is " << * p_num2 << endl;
    int num3 = 100;
    const int * const p_num3 = &num3;
    cout << "for the const int * const p_num3, the * p_num3 is " << *p_num3 << ", the p_num3 is"<< p_num3 << endl;

    // 例: 对数组内的元素进行排序
    int * array_  =  new int[10] {1,5,7,6,10,3,8,2,9,4};
    int * a = new int;
    * a = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            if (array_[i] > array_[j]) {
                * a = array_[i];
                array_[i] = array_[j];
                array_[j] = * a;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << array_[i] << endl;
    }
    return 0;
}
