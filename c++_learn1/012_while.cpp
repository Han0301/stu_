//
// Created by 29873 on 25-5-31.
//
/* while 循环语句, 三要素: 循环因子, 循环因子的更新, 循环条件的判断
 * 语句:
 *      while (条件表达式){
 *          code;
 *      }
 */
#include <bemapiset.h>

#include "iostream"
using namespace std;
int main() {
    bool is_run = true;     // 这里的 is_run 称作循环的控制因子
    int num = 1;            // 这里的 num 用于控制因子的更新
    while (is_run) {
        cout << "Hello World!(count:" << num << endl;
        num ++;
        if (num > 8) {
            is_run = false;
        }
    }

    // 需求: 我要向小美表白, 每一天都表白, 表白10天
    int is_run_num = 1;
    while (is_run_num <=10) {
        cout << "today is " << is_run_num << ", I love you, xiaomei" << endl;
        is_run_num ++;
    }
    // 需求: 累加1到100
    int total_num = 0;
    int epoch_num = 1;
    while (epoch_num <= 100) {
        total_num += epoch_num;
        epoch_num ++;
    }
    cout << "total_num is " << total_num << endl;

    // 需求: 使用while 实现猜数字, 无限次机会, 猜中返回所猜的次数
    int target = 66;
    int epoch = 0;
    int guess_num;
    bool guess = true;
    while (guess) {
        cout << "please input your guess_num:" << endl;
        cin >> guess_num;
        epoch ++;
        if (guess_num == target) {
            cout << "you win! the guessing epoch is " << epoch << endl;
            guess = false;
        }
        else if (guess_num > target) {
            cout << "your guess_num is bigger than the target" << endl;
        }
        else {
            cout << "your guess_num is smaller than the target" << endl;
        }
    }
    return 0;
}