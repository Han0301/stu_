//
// Created by 29873 on 25-5-10.
//
/* switch 控制语句
 * 1. 基本语法:
 *  switch(常量表达式){
 *      case 常量1:
 *          code;
 *          break;
 *      case 常量2:
 *          code;
 *          break;
 *      ...
 *      default:    // 可选, default 表示没有case匹配时执行的语句
 *          code
 *  }
 *  2. 注: break 用于跳出整个switch 循环,
 *      因为一旦有case 匹配, 执行完code会不看后面的case 自动执行之后的所有case下语句, 所以每个case都要有break;
 *      由于break 的特性: 可以实现:
 *          如果多个case 的值指向一个同样的输出, 可以这样做:
 *              switch(num){
 *                  case 10:
 *                  case 9:
 *                      cout << "优秀" << endl:
 *                      break;
 *                  case 8:
 *                  case 7:
 *                  case 6:
 *                      cout << "良好" << endl;
 *                      break;
 *                  defaulit:
 *                      cout << "一般" << endl;
 *                      break;
 *              }
 */

#include "iostream"
using namespace std;

int main() {
    // 输入数字1-7来表示星期几
    cout << "please input your num: " << endl;
    int num;
    cin >> num;
    switch (num) {
        case 1:
            cout << "today is Monday!" << endl;
            break;      // 不带 case 会自动执行case 1 下所有的可执行语句
        case 2:
            cout << "today is Tuesday!" << endl;
            break;
        case 3:
            cout << "today is Wednesday!" << endl;
            break;
        default:
            cout << "I don't konw it..." << endl;
    }
    return 0;
}
