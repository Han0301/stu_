//
// Created by 29873 on 25-5-9.
//
/*
 * 数据类型
 * 1. 整型:
 *      1.1 short(短整型): 占用2 字节, 取值范围: -32768~32767               (2 ^ 15 ~ 2 ^ 15 - 1)
 *      1.2 int(整型):  占用4个字节, 取值范围: -2147483648~2147483647     (2 ^ 31 ~ 2 ^ 31 - 1)
 *      1.3 long(长整型): windows, 32位的linux都是4字节, 64位linux是8字节
 *      1.4 long long(长长整型): 8字节, -2 ^ 64 ~ 2 ^ 64 - 1
 * 2. 通过 sizeof(数据), 确定数据占用的字节
 * 3.无符号与有符号的区分:
 *      无符号: 仅允许正数
 *      有符号: 正负都可
 *      一般直接定义的变量整型, 都是有符号的, 如 signed int num; 不过这里的signed省掉
 *      需要定义无符号的整型, 如 unsigned int num;, 快捷定义: u_int,u_short,
 *
 * 4. 实型:
 *      3.1 float 4字节, 有效位数6-7位, 单精度浮点数
 *      3.2 double 8字节, 有效位数15-16, 双精度浮点数
 *      3.3 long double 16字节, 有效位数18-19, 多精度浮点数
 *      3.4 注: 实型数据没有singed, unsigned, 默认全部有符号
 *      3.5 注: 有效位数仅供参考, 具体受编译器影响
 * 5. cout 默认以科学计数法输出, 若想修改成小数的形式输出, 在输出前: cout << fixed;
 * 6. cout.width(), 设置显示宽度
 *
 * 6. 如何确定字面量的类型: 遵循最小原则, 系统会根据字面常量的大小匹配对应的最小的数据类型
 *      注: 常量后可以跟声明其数据类型的后缀: 如 10L, long型,  123UL, unsigned long
 *          U 表示 unsigned, L: long int 或 long double, LL: long long, F: float ,D: double
 *      注: 整数的默认的是 int, 浮点型的默认的是 double
 *
 * 7. 字符型:
 *      仅占用1字节: 有符号的范围是 -128~127,  无符号的是 0~255, 使用ASCII 表进行转换, 字符在内存中实际是数字
 *      注: char 无法存储中文
 *      注: 若直接打印char类型的变量, 会返回字符, 但由于其本质是数字, 改成 ch + 1, 就会返回数字, 表示ch 的ASCII值
 *      注: ASCII前面的都是非打印控制字符, 无法打印出其形态, 如换行等, 可通过转义字符来调用:
 *          \n: 换行
 *          \t: 水平制表, 跳到下一个tab的位置
 *          \\: 表示反斜杠\本身
 *          \': 表示单引号字符
 *          \": 表示双引号字符
 */

#include "iostream"
#include "windows.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    short num1 = 10;
    int num2 = 20;
    long num3 = 3011111;
    long long num4 = 1111111;
    cout << num1 << num2 << num3 << num4 << endl;
    cout << "short 占用的字节数: " << sizeof(short) << endl;
    cout << "int 占用的字节数: " << sizeof(int) << endl;
    cout << "long 占用的字节数: " << sizeof(long) << endl;
    cout << "long long 占用的字节数: " << sizeof(long long) << endl;
    unsigned int num4_1 = -1111;
    cout << num4_1 << endl;     // 输出 4294966185, 表明unsigned int 定义的只能是正数, 负数不会正常的存储
    u_int num4_2 = 1111;
    u_short num4_3 = 2222;
    cout << num4_2 << num4_3 << endl;

    float num5 = 1234567890;
    cout << "num5 = " << num5 << endl;      // 以科学计数法的形式输出: num5 = 1.23457e+09
    cout << fixed;          // 以小数形式返回
    cout.width(10);     // 以固定的10位数字返回
    cout << "num5 = " << num5 << endl;      // 仅维持前7位的正常的输出: num5 = 1234567936.000000
    double num6 = 1.12345678901234567890;
    cout << "num6 = " << num6 << ", the size of the double is " << sizeof(num6)<< endl;
    long double num7 = 1.12345678901234567890;
    cout << "num7 = " << num7 << ", the size of the double is " << sizeof(num7)<< endl;
    // num6 num7 都是: 1.123457, 受编译器影响

    cout << "------------------------------------" << endl;
    cout << "123的字节数是: " << sizeof(123) << endl;        // 整数的默认的是 int
    cout << "12345678901234的字节数是: " << sizeof(12345678901234) << endl;
    cout << "3.14159265411的字节数是: " << sizeof(3,14159265411) << endl;
    cout << "123LL的字节数是: " << sizeof(123LL) << endl;
    cout << "3.14字节数是: " << sizeof(3.14) << endl;       // 浮点型的默认的是 double
    cout << "3.14F字节数是: " << sizeof(3.14F) << endl;

    char ch = 99;
    cout << ch << endl;     // 输出 c, 表明c的ASCII值为99
    char ch2 = 'a';
    ch2 = ch2 + 1;
    cout << ch2 << endl;
    cout << ch2 + 1 << endl;

    cout << "How are you? \nI am fine!" << endl;
    // 进行对齐, \t, 可以补充8个空的字符
    cout << "name\t小明" << endl;
    cout << "age\t20" << endl;
    cout << "heights\t182" << endl;
    cout << "123\\123" << endl;
    cout << "\"123\"" << endl;
    return 0;
}
