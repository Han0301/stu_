//
// Created by 29873 on 25-5-9.
//
/* 数据类型(续上)
 * 8. 字符串
 *      8.1: 定义方式: c++风格: string c;
 *                    c风格: char a[];    字符数组的形式, 只读, 不可直接通过赋值语句修改
 *                          char *b;     指针形式
 *      8.2: 字符串的拼接: 直接通过 + 拼接, + 仅能拼接字符串型的, 其他可通过 to_string()进行转换
 * 9. 布尔型,bool
 *      字面量仅有两个: true, false, 本质上是1, 0, 通过bool进行声明, 主要用于流程的控制
 * 10. cin 输入, 语法: cin >> 变量(提前声明好)
 *      10.1 通过cin, cout 配合使用, 提示输入, 指示输出
 *      10.2 通过cin 乱码怎么解决:
 *          按住 ctcl +shirt + alt + / 配置, 进入注册表,  取消勾选: run.processes.with.ptY
 *          取消勾选后, cout 也不会遇到乱码的问题, 不用再在代码中配置了
 */

#include "iostream"
#include "windows.h"
using namespace std;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    char s1[] = "abc";
    char *s2 = "abcdef";
    string str1 = s1;
    cout << s1 << s2 << str1 << endl;

    string str2 = "物理";
    int score = 66;
    string str3 = "及格";
    string total_str = "你的" + str2 + "成绩是" + to_string(score) + ", " + str3;
    cout << total_str << endl;

    bool flag = true;
    bool flag2 = false;
    cout << flag << endl;
    cout << flag2 << endl;

    int num;
    cout << "请输入一个数字: " << endl;
    cin >> num;
    cout << "you input is " << num << endl;
    char ch;
    cout << "请输入一个字符: " << endl;
    cin >> ch;
    cout << "you input is " << ch << endl;
    string str4;
    cout << "请输入你的名字: " << endl;
    cin >> str4;
    cout << "you input is " << str4 << endl;
    return 0;
}
