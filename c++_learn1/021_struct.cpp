//
// Created by 29873 on 25-6-2.
//
/* 结构体: 是一种数据类型, 由用户自定义的符复合数据类型, 可以包含不同类型的不同成员
 *      结构体的声明:
 *          struct 结构体名{
 *              数据类型 成员1名;
 *              数据类型 成员2名;
 *              ...
 *          }
 *      结构体变量的声明:
 *          struct 结构体名 结构体变量名;     // 这里的struct 可以省略, 但并不推荐
 *      赋值:
 *          结构体变量名 = {};        // 依次填入
 *      声明和赋值:
 *          struct 结构体名 结构体变量名 = {};
 *      注: 结构体变量本身只是一个包装, 不能通过cout 进行输出, 需要访问结构体中的每一个成员来进行输出
 *      注: 因为结构体是一种数据类型, 所以基于一个结构体的结构体变量只要名称不同, 就能任意声明
 *      注: 即使是由不同结构体定义的结构体变量, 其变量名不能重复
 *      输出:
 *          结构体变量名.结构体中的成员名
 *  结构体成员的默认值, 在后续未设置对应成员的值, 则采用默认值
 *  语法:
 *      struct student {
 *          string name;
 *          int age = 18;       // 直接在声明成员的时候进行赋值, 这里的值就是默认值
 *      }
 */
#include "iostream";
using namespace std;
int main() {
    struct Student {
        string name;
        int age;
        string gender;
    };
    struct Student stu;
    stu = {"周杰伦", 30, "♂"};
    cout << stu.gender << endl;

    return 0;
}