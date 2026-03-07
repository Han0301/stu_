//
// Created by 29873 on 25-6-2.
//
/* 函数
 *      作为一种提前封装好的, 可重复使用的, 完成特定功能的独立的代码单元
 *      语法:
 *          返回值类型 函数名称(需要传入的参数){
 *              code;       // 函数体
 *              return 返回值;
 *          }
 *      注: 函数执行到return 就结束了
 *      注: 函数不可以定义在main内部
 * 无返回值函数与 void 类型
 *      当函数不提供返回值时:
 *          声明函数的类型为 void
 *          不需要写 return 语句
 * 空参函数
 *      除了返回值除外, 函数的传入参数也是可选的, 如果函数的代码逻辑中不需要参数, 函数也可以没有参数提供
 * 函数的嵌套调用
 *      函数作为一个独立的代码单元, 可以相互调用
 * 参数的值转递和地址传递
 *      在函数的参数传递中, 实参转给了形式参数, 若在函数中改变两个形式参数的值, 不影响函数外原本的实际数值
 *      只有进行地址的传递, (即传递指针进行交换, 会影响原本实际的值)
 */
#include "iostream";
using namespace std;

// 需求 给定三个输入数字, 返回最大值
int get_max(int num1,int num2,int num3) {       // 形式参数
    int max_num;
    int array[3] = {num1,num2,num3};
    for (int i = 0; i <= 2; i ++) {
        if (max_num < array[i]) {
            max_num = array[i];
        }
    }
    return max_num;
    }

// 需求 传入名字, 打印提示
void say_hello(string name) {
    cout << "hello " << name << ", I am Han" << endl;
}

// 需求 要三个函数, 函数1 取到2个int 的最小值, 函数2 取到2个int 的最大值, 函数3 需要接受函数1, 函数2 的输出, 并返回一个结构体, 结构体由两个成员组成
int get_max_(int a,int b) {
    if (a > b) {return a;}
    return b;
}
int get_min_(int a,int b) {
    if (a < b){return a;}
    return b;
}
struct max_min {
    int max_num;
    int min_num;
};

struct max_min get_max_min(int a,int b) {
    int min = get_min_(a,b);
    int max = get_max_(a,b);
    struct max_min v = {max,min};
    return v;
}

// 参数的值传递和地址传递
void switch_num(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void switch_pointer(int *a, int *b) {       // 传进去的a,b 为地址
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int num1,num2,num3, max_num;
    cin >> num1;
    cin >> num2;
    cin >> num3;
    max_num = get_max(num1,num2,num3);      // 实际参数
    cout << max_num << endl;;

    string name;
    cout << "please input your name: ";
    cin >> name;
    cout << name << endl;
    say_hello(name);

    struct max_min v = get_max_min(num1,num2);
    cout << v.max_num << endl;
    cout << v.min_num << endl;

    int x = 10, y = 20;
    cout << x << y << endl;
    switch_num(x, y);
    cout << "after switch the num: " << x << y << endl;

    int * p_x = &x;
    int * p_y = &y;
    cout << *p_x << *p_y << endl;
    switch_pointer(p_x, p_y);
    cout << "after switch pointer: " << *p_x << *p_y << endl;
    return 0;
}
