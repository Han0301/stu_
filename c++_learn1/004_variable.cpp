//
// Created by 29873 on 25-5-9.
//
/* 变量: 用于存储数据
 * 1. 变量的声明:
 *      语法: 变量类型 变量吗名, 如
 *          int num; 来定义整型
 *          float fudian; 定义实型
 *          char zifu; 定义字符型
 *          string zifuchaung; 字符串型
 * 2. 变量的赋值.0
 * 3. 变量的特征: 存储的数据可变, 修改的方式直接使用赋值语句即可
 *      语法: 变量名 = 变量值, 如 num = 10
 * 4. 变量的快速定义
 *      4.1 变量的声明和赋值同时进行, 如 string name = "周杰伦";
 *      4.2 一次性声明多个变量, 如 int a,b,c;
 *      4.3 一次性声明多个变量并同步赋值; 如 int a = 10, b = 20, c = 30;
 */
#include "iostream"
#include "windows.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int age;
    float height;
    char sex;
    string name;
    age = 21;
    height = 180.5;
    sex = 'man';
    name = "小明";
    cout << name << "的年龄是" << age << ", 身高是" << height <<  endl;

    int total;
    int cost_minktea;
    int get_milktea;
    int ticket;
    total = 50;
    cost_minktea = 5;
    get_milktea = 10;
    ticket = 2;
    cout << "小明的余额: " << total << endl;
    total = total - cost_minktea;
    cout << total << endl;
    total = total + get_milktea;
    cout << total << endl;
    total = total - 2;
    cout << total << endl;
    total = total * 2;
    cout << total << endl;
    cout << "------------------------------" << endl;
    int a = 21;

    string name1 = "小明", name2 = "小红", name3 = "小兰";
    cout << name1 << "<UNK>" << name2 << "<UNK>" << name3 << endl;
    return 0;
}

