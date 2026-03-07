//
// Created by 29873 on 25-5-10.
//
/* 运算符
 * 1. 算数运算符
 *      1.1 常用的有: + - * / % 取余
 *      1.2 ++ -- 前置/后置 递增/递减, ++, --本身表示+1,-1
 *          区别: 前置++, 表示先+1, 再进行赋值, 后置就表示先赋值,再+1
 *      1.3 单目: 有一个操作数, 双目: 有两个操作数
 * 2. 赋值运算符(是一种双目运算符)
 *      2.1 定义: 先运算, 再赋值
 *      2.2 常用的有: = , += , -= , *= , /=, %=
 * 3. 比较运算符, 通过比较, 得到布尔型的结果, true,false, cout 打印结果为1, 0
 *      注: 一般通过cout 进行输出比较, 对于表达式, 需要 () 括住
 *      == 相等
 *      != 不等于
 *      <, >
 *      <=, >=
 *      注: 字符串的比较
 *          如果通过c风格定义, 比如char ch[], char *ch, 使用运算符比较, 比较的是内存地址, 而非内容, 所以结果一般都是0
 *          需要使用c语言中的函数 strcmp 进行比较
 *              #include "cstring"
 *              int result = strcmp(s1,s2);
 *              结果分为-1, s1 < s2, 0 s1 = s2, 1, s1 > s2
 *          通过c++定义的字符串, 进行比较的两个字符串, 只要有一个是通过string定义的, 那么就可以通过比较运算符进行比较
 * 4. 逻辑运算符
 *      !, 取相反, 单目
 *      &&, 与, 都真才真
 *      ||, 或, 都假才假
 * 5.三元运算符
 *      5.1 定义: 对逻辑进行判断, 根据bool的结果, true 则提供值1, false 则提供值2
 *      5.2 语法: 产生bool结果的表达式? 值1 : 值2;
 */
#include "iostream"
#include "cstring"
using namespace std;

int main() {
    int a = 2,b;
    b = ++ a;    //前置++, 表示先+1, 再进行赋值
    cout << "a = " << a << ", b = " << b <<  endl;
    // a = 3, b = 3
    b = a ++;       // 后置就表示先赋值,再+1
    cout << "a = " << a << ", b = " << b <<  endl;
    // a = 4, b = 3
    cout << "b ++ = " << b++  << ", b =  "<< b <<  endl;        //后置, 先赋值, 所以显示为 b++ = 3, 实际的b = 4
    cout << "++ b = " << ++b << ", b = " << b << endl;
    //前置, 先计算, 所以b = b ++ = 5

    int num  = 2;
    num += 3;
    num *= 2;
    cout << "num = " << num << endl;
    num %= 3;
    cout << "num = " << num << endl;

    int num2 = 3;
    int num3 = 4;
    bool r1 = num2 == num3;
    cout << "num2 = num3: " << r1 << endl;      // 返回0
    bool r2 = num2 != num3;
    cout << "num2 != num3: " << r2 << endl;     // 返回1
    cout << "num2 != num3: " << (num2 != num3) << endl;     // 返回1
    char str1[] = "hello world";
    char *str2 = "hello world";
    cout << "str1 = str2: " << (strcmp(str1, str2)) << endl;    // 0 表示相等
    cout << strcmp("a", "g") << endl;
    string str3 = "hello worldd";
    cout << "str1, str3: " << (str1 == str3) << endl;       //只要有一个是通过c++定义的字符串, 就可应通过比较运算符
    cout << "str1, str3: " << (str1 < str3) << endl;
    cout << "!(str1, str3): " << !(str1 < str3) << endl;
    cout << "str1, str3: " << !(str1 < str3) << endl;


    int number1, number2;
    cout << "number1 = " << endl;
    cin >> number1;
    cout << "number2 = " << endl;
    cin >> number2;
    string str = number1 > number2 ? "number1 > number2" : "number1 <= number2";
    cout << str << endl;
    return 0;
}