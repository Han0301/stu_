//
// Created by 29873 on 25-5-8.
// CLion 以工程管理代码, 由于main函数是主程序的入口, 一般仅允许一个main函数
//1. 预编译
#include "iostream"
using namespace std;

int main() {    //2. main函数: 主函数(程序入口), int main() {} {}中即执行语句, 都要以;结尾
    //3. cout << "  " << endl;
    // cout表示对外输出, " "中为输出的信息, endl表示输出一个换行
    std::cout << "Hello World!!!" << std::endl;
    std::cout << "for the first cpp!!!" << std::endl;
    system("puase");
    return 0;       //4. 返回值函数
}

// 5. 在终端中编译
// 通过MinGW在终端编译: 进入到文件夹目录, 按照 g++ cpp文件名 -o 输出的程序名(以.exe结尾)
// 然后直接输入以.exe结尾的程序名运行