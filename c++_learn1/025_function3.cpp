//
// Created by 29873 on 25-7-23.
//
/* 函数的分文件编写
 *      作用: 让代码结构更加清晰
 *      编写步骤:
 *          1. 创建后缀名为 .h 的头文件
 *          2. 创建后缀名为 .cpp 的源文件
 *          3. 在头文件中写函数的声明
 *          4. 在源文件中写函数的定义(在源文件头部写: #include "头文件名", 即可正确链接到头文件)
 *
 *      注: 头文件和源文件一般放在工程文件中的两个子文件夹中
 */

// 实例: 原程序:
#include<iostream>
using namespace std;
void change(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout << "a = " << a << ", b = " << b << endl;
}
int main() {
    int a = 10;
    int b = 5;
    change(a, b);
    return 0;
}

// 使用多文件编写改写
// 首先创建一个 .h 文件, 编写:
void change_(int a, int b);

// 再创建一个源文件, 编写:
// #include ""     // 这里"" 中填入头文件的名称, 就能链接到头文件中
void change_(int a, int b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
    cout << "a = " << a << ", b = " << b << endl;
}