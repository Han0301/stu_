//
// Created by 29873 on 25-5-31.
//
/* 1.for循环
 *  语法:
 *      for (循环因子的初始化;条件判断;循环因子的更新){
 *      code;
 *      }
 *  注: 对于for( ; ; )三要素都可以省略, 但不能在整体的代码中缺失
 *      int num = 1;
 *      for( ;num <= 10; ){
 *      code;
 *      num += 1;
 *      }
 *  2.嵌套同上, 也可以for, while 相互嵌套
 *  3. 变量的作用域:
 *      代码块: 将 {......code; } 称作代码块, 在一个代码块中声明的变量, 仅能在本代码块中使用, 在{} 外不能访问
 * 4. 循环终端语句
 *      continue;   跳过本次循环
 *      break;      直接退出这个循环体
 */
#include "iostream"
using namespace std;
int main() {
    for (int count=0; count<=10; count++) {
        cout << "the count is " << count << endl;
    }
    // 求1~100 的偶数之和
    int num_total = 0;
    for (int num = 0; num <= 100; num += 2) {
        num_total += num;
    }
    cout << "the total number is " << num_total << endl;
    // 通过 for 循环实现猜数字
    int epoch = 0;
    int target = 55;
    for (int guess_num;guess_num != target;) {
        cout << "your input guess_num is ";
        cin >> guess_num;
        if (guess_num > target) {
            cout << "your input guess_num is bigger than the target" << endl;
        }
        else if (guess_num < target) {
            cout << "your input guess_num is smaller than the target" << endl;
        }
        epoch ++;
    }
    cout << "you win!!! the epoch is " << epoch << endl;

    // 通过 for 循环实现九九乘法表
    for (int i = 1; i <=9; i += 1) {
        for (int j = 1; j <= i; j += 1) {
            cout << i << " * " << j << " = " << i * j << "  ";
            if (i == j) {
                cout << endl;
            }
        }
    }

    // 通过for 循环输出1到20的奇数
    for (int i = 1;i <=20; i ++) {
        if (i % 2 == 0) {
            continue;
        }
        cout << i << endl;
    }
    return 0;
}
