//
// Created by 29873 on 25-5-31.
//
/* 1.do while 循环: 一般的while 循环,一旦条件不满足, 就不会再执行while 中的code,
 *      但是do while 如果条件不成立, 至少还会执行一次code
 *      语法:
 *          do
 *          {
 *              code;
 *          }while(条件表达式);
 *      注: 本质上do while 中的code一定会执行一次,后续的运行与传统的while循环一致,即先判断再执行code
 * 2.while 循环嵌套
 *      while (条件1){
 *          while(条件2){
 *          code;
 *          }
 *          code;
 *      }
 */
#include <iostream>
using namespace std;
int main() {
    int guess_num;
    int target = 66;
    do {
        cout << "please input your guess_num:" << endl;
        cin >> guess_num;
        if (guess_num > target) {
            cout << "your guess_num is bigger than the target!" << endl;
        }
        else if (guess_num < target) {
            cout << "your guess_num is less than the target!" << endl;
        }
        else {
            cout << "your guess_num is equal to the target!" << endl;
        }
    }while (guess_num != target);

    // 需求 每次向小美表白, 每次表白送表白次数的玫瑰, 直到表白结束
    int day_count = 1;
    bool accept_or_not = true;
    int rose_count = 0;
    while (accept_or_not) {
        cout << "I love your please accept me!!! ";
        rose_count = 1;
        while (rose_count <= day_count) {
            cout << "this is rose, express my love!" << endl;
            rose_count++;
        }
        cout << "now you need decide accept or not!,please input accept or no" << endl;
        string accept_or_not_str;
        cin >> accept_or_not_str;
        if (accept_or_not_str == "accept") {
            cout << "I love you too" << endl;
            accept_or_not = false;
        }
        day_count++;
    }
    // 输出 99乘法表
    int row_count = 1;
    int num;
    while (row_count <= 9) {
        num = 1;
        while (num <= row_count) {
            cout << num << " * " << row_count << " = " << num * row_count << "  ";;
            num += 1;
        }
        cout << endl;
        row_count++;
    }
    return 0;
}
