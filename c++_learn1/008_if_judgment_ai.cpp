//
// Created by 29873 on 25-5-10.
//
/* if 判断语句
 * 1. 语法: if (要执行的判断, 结果需要的是布尔型){
 *                  判断为真的时候, 执行的代码;
 *             }
 * 2. ai 辅助编程
 *      在插件市场搜索: TONGYI 和 iflycode
 * 3. if else语句
 *      语法: if (条件判断){
 *       为true 执行的代码
 *      }
 *      else{
 *       为false 执行的代码
 *      }
 * 4. else if 语句
 *      语法:
 *      if (条件判断1){
 *      条件判断1为true 时执行的代码
 *      }
 *      else if (条件判断2){
 *      条件判断2为true时执行的代码
 *      }
 *      else if(){
 *
 *      }
 *      else{
 *      上述判断都为false, 执行的代码
 *      }
 *      注: 有且仅有一个{}中的语句会被执行
 *
 */
#include "iostream"
using namespace std;

int main() {
    int money;
    cout << "今天发工资了, 请输入小明发送的工资: ";
    cin >> money;
    if (money >= 10000) {
        cout << "money is enough, the cost is 9900" << endl;
        money -= 9900;
    }
    cout << "今天还剩: " << money << endl;

    int age;
    cout << "please input your age: ";
    cin >> age;
    if (age <= 12) {
        cout << "it is free for you, come on !!!" << endl;
    }
    else if (age > 12 && age <= 18) {
        cout << "please pay for the ticket for half!" << endl;
    }
    else {
        cout << "please pay for the ticket for total!" << endl;
    }
    return 0;
}

