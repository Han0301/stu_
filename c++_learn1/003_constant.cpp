//
// Created by 29873 on 25-5-8.
//
/* 常量: 分为字面常量, 符号常量
 * 1.字面常量: 直接书写到代码中的常量即为字面常量, 常用的有整型, 实型, 字符, 字符串
 * 2. 标识符: 给变量, 类, 函数 命名, 称作标识符, 即表示一类实体的符号
 * 3. 符号常量: 使用标识符去定义的常量
 *      格式: #define 标识符(名称) 常量  #define 为宏定义, 标识符中字母建议大写, 与后面的变量区分
 *      注: 符号常量要定义在代码的头部
 *      注: 定义的是否不需要分号结尾
 * 4. 解决中文输出乱码的问题:
 *      方式一: 引入 windows.h库:
 *          在代码的头部, 声明: #include windows.h
 *          在main函数中: SetconsoleOutputCP(CP_UTF8)  //设置控制台的字符编码
 *      方式二: 使用system:
 *          在main函数中: system("chcp 65001");
 *          缺点: 会在执行时输出: Active code page: 65001
*/
#include "iostream"
#include "windows.h"

using namespace std;
#define FAT_BMI 28

int main() {
    //SetConsoleOutputCP(CP_UTF8);
    system("chcp 65001");
    1;
    1.1;
    'a',
    "this is a string";
    cout << "Hello World!" << endl;
    cout << "Your BMI is " << FAT_BMI << endl;
    cout << "你的BMI是 " << FAT_BMI << endl;
    return 0;
}
