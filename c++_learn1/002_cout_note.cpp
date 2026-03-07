//
// Created by 29873 on 25-5-8.
//
/*
 * 1. cout: 结构:
 *      输出单个内容: cout << ... << endl;
 *      输出多个内容: cout << ... << ... << ... << endl
 * 2. 注释的使用:
 *      单行注释: //
 *      多行注释: /*
 * 3. CLion 的使用
 * 快捷键:  shirt + alt + 键盘的上下: 控制当前行的代码整体上移或下移
 *         ctrl + d: 复制当前行
 *         ctrl + f5: 编译并运行当前的代码
 */


#include "iostream"
using namespace std;

int main() {
    cout << "only one message..." << endl;
    cout << 10 << "first message..." << "second message..." << "third message..." << endl;
    cout << "with no endl";     // 不以endl 结尾的话, 输出的最后就不会换行
    cout << "with no endl" << endl;
    cout << "C++ is " << "the best " << "programming languare" << endl;
    return 0;

}