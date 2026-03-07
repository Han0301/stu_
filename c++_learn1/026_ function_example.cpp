//
// Created by 29873 on 25-8-3.
//
/* 实例: ATM 取款程序
 *
 */

#include<iostream>
using namespace std;

// 查询余额函数
// 这里涉及到怎么传递数据, 选择值传递(复制, 性能较差)还是地址传递(性能远好于值传递), 本函数涉及大量调用, 考虑性能优先,所以使用地址传递
void query_money(string * name, int * money) {
    cout << "---------------查询余额---------------" << endl;
    cout << *name << ", 你好, 你的余额为: " << *money << endl;
}

// 存款函数
void save_money(string *name, int * money, int * input_money) {
    cout << "---------------准备存款---------------" << endl;
    cout << *name << ",你已存款: " << *input_money << endl;
    *money += *input_money;
    cout << "现在你的余额为: " << *money << endl;
}

// 取款函数
void get_money(string *name, int * money, int * get_money) {
    cout << "---------------准备存款---------------" << endl;
    cout << *name << ",你已取款: " << *get_money << endl;
    *money -= *get_money;
    cout << "现在你的余额为: " << *money << endl;
}

// 主菜单函数
// 要根据input 跳转到指定函数中,执行好指定的业务逻辑后返回到主菜单
int menu(string * name) {
    cout << "---------------主菜单---------------" << endl;
    cout << "你好, 查询余额输入'1'" << endl;
    cout << "你好, 存款输入'2'" << endl;
    cout << "你好, 取款输入'3'" << endl;
    cout << "你好, 退出输入'4'" << endl;
    int number;
    cin >> number;
    return number;
}

int main() {
    // 1. 启动时输入用户姓名
    string name;
    cout << "请输入你的姓名: " << endl;
    cin >> name;
    // 2. 启动好调用主菜单
    bool is_running = true;
    while (is_running) {
        int select_num = menu(&name);
        int money = 114514;
        switch (select_num) {
            case 1:
                query_money(&name, &select_num);
            case 2:
                int input_money;
                cout << "您要存入 : " << endl;
                cin >> input_money;
                save_money(&name, &money, &input_money);
            case 3:
                int get_money;
                cout << "您要取出 : " << endl;
                cin >> get_money;
                get_money(&name, &money, &get_money);
            case 4:
                cout << "程序结束" << endl;
                is_running = false;
        }
    }

}