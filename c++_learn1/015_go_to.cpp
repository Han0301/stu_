//
// Created by 29873 on 25-6-1.
//
/* goto语句
 * goto 实现无条件跳转的功能
 * 语法:
 *      label1:     // 添加标记, 在程序中标签只有通过goto才能被调用, 否则不执行
 *          code;
 *      label2:
 *          code;
 *      label3:
 *          code;
 *      goto label1;    // 跳到label1中
 *
 */
#include "iostream"
using namespace std;
int main() {
    // 通过 goto 实现循环语句
    int i = 1;
    loop:
        cout << i << endl;
        i += 1;
    if (i <= 10){goto loop;}
    return 0;
}
