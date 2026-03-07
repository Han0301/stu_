//
// Created by 29873 on 25-6-1.
//
/* 数组: 由一批相同类型的元素的集合所组成的数据类型, 分配一块连续的内存来存储
 * 声明语法1:
 *      数据类型 数组名[数组长度];
 *      int v[6];
 *  注: 下标从0 开始, 可以通过 数组名[下标] 存储/调用数组内的元素
 *  注: 直接 cout << v << endl; 访问只会返回数组的内存地址
 *  声明语法2:      // 声明的同时赋值
 *      数据类型 数组名[数组长度] = {元素1, 元素2, ...}
 *      注: 这里可以不指定 数组长度, 会自动根据后面的元素数确定
 *  特点1: 任意数据类型都可以构建数组, 如 int, float, double, char, string, bool...包括后面学的结构体, 指针, 枚举类型
 *  特点2: c++ 的数组一旦定义完成, 数组的长度是固定的
 *      c++ 不会做边界的检查, 即使下标超出索引的范围, 编译的过程中也不会报错, 但是运行是可能有未知的问题, 甚至修改未知内存未知的数据
 *      注意下标索引不要超过数组所定义的长度
 *  特点3: 数组在内存中连续且有序, 单个元素的分配大小与数据的类型相关
 *      通过 sizeof(数组) 返回数组所占用的总内存大小
 *      通过 sizeof(数组) / sizeof(数组总任一的元素) 返回数组的元素个数
 *  特点4: 数组中的元素的值可以修改, 但是元素的类型不能修改
 *  特点5: 数组变量 v 本身不记录任何元素的数据, 而是记录了v[0]的内存地址
 *
 *  数组的遍历:
 *      通过 while / for 循环完成, 将循环的控制因子, 作为数组的索引,
 *          注意循环的控制因子要小于数组长度, 即 i <= sizeof(li) / sizeof(li[0])
 *      其他写法:
 *          for (元素类型 临时变量名: 数组变量){     // 这里依次取数组内的变量, 将其赋值给临时的变量
 *          code;                               // 数组中有几个元素, 这个循环就循环几次
 *          }
 *  字符数组:
 *      之前定义的字符串类型:
 *          "hello"
 *          char s[] = "hello"
 *          char *s = "hello"
 *          这里前两种本质上都是字符数组, 在存储时, 会在最后一个元素添加 "\0" 作为结束的标记(空字符)
 *          所以通过 sizeof 统计长度时需要 - 1
 *          注: 这种规律不适用于中文, ASCII 无法表示, 中文需要使用string 类型进行存储, 而不是字符数组
 * 多维数组:
 *      对数组进行嵌套
 *      语法:
 *      int v[3][3];        // 声明一个二维数组
 *      v[0][0] = 11;
 *      ...         // 进行赋值
 *      int v2[3][3] = {{1,2,3},{4,5,6},{7,8,9}}      // 声明的同时定义
 *      注: 这里声明的同时赋值, 需要确定各个维度的数组长度, 不能省略
 *  多维数组的遍历: 通过 for 循环层层遍历
 *      注意下标的确定: 对于二维数组:
 *          第一层: sizeof(v2) / sizeof(v2[0]) - 1
 *          第二层: sizeof(v2[0]) / sizeof(v2[0][0]) - 1
 *      例:
*       for (int i = 0; i <= sizeof(v2) / sizeof(v2[0]) - 1; i++) {
            for (int j = 0; j <= sizeof(v2[0]) / sizeof(v2[0][0]) - 1; j++) {
                cout << "v2[" << i << "][" << j << "] is " << v2[i][j] << endl;
            }
        }
 */

#include "iostream"
using namespace std;
int main() {
    int v[5];
    for (int i = 0;i < 5; i ++) {
        v[i] = i;
    }
    cout << v << endl;      // 返回: 0xf569fffe00, 是数组第一个元素的的内存地址
    // 猜数字: 通过数组存储10个(1~10内) 的数字, 让用户依次猜数字, 返回猜中的数字数量
    int target_num[] = {3,2,7,5,8,1,3,5,7,2};
    int guess_num[10];
    int count = 0;
    for (int i = 0; i <= 9; i ++) {
        cout << "for the " << i + 1 << " , please input your guess num ";
        cin >> guess_num[i];
        if (target_num[i] == guess_num[i]) {
            count ++;
        }
    }
    cout << "game over! your guess for the same is " << count <<  endl;
    cout << "the sizeof of the target_num is " << sizeof(target_num) << endl;
    cout << "the num count of the target_num is " << (sizeof(target_num) / sizeof(target_num[0])) << endl;
    for (int element:target_num) {
        cout << element << endl;
    }
    string str = "hello";
    cout << "the size of str is " << (sizeof(str) / sizeof(str[0])) << endl;;
    char str2[] = "hello world";
    cout << "the size of str is " << (sizeof(str2) / sizeof(str2[0])) << endl;
    for (char src : str2) {
        cout << src << endl;
    }
    cout << str[5];     // 返回空字符
    int v2[3][3] = {{1,2,3}, {4,5,6}, {11,22,33}};
    cout << "c2[2][2] is " << v2[2][2] << endl;
    cout << "c2[1]" << v2[1] << endl;       // 只能返回子数组的地址
    for (int i = 0; i <= sizeof(v2) / sizeof(v2[0]) - 1; i++) {
        for (int j = 0; j <= sizeof(v2[0]) / sizeof(v2[0][0]) - 1; j++) {
            cout << "v2[" << i << "][" << j << "] is " << v2[i][j] << endl;
        }
    }
    return 0;
}