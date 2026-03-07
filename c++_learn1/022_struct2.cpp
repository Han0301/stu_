//
// Created by 29873 on 25-6-2.
//
/* 结构体数组
 *      结构体数组的声明:
 *          基于已经定义好的结构体, 其本身作为一种数据类型, 在定义结构体数组时
 *          原先格式: 数据类型 数组名[数组长度]   其中的数据类型用声明好的结构体即可
 * 结构体指针
 *      (1) 引入已经存在的结构体地址(静态内存)
 *          对于已经声明好的结构体和结构体变量,
 *              struct 结构体名 * 指针名 = & 结构体变量名
 *              例: struct student * p_stu = & stu
 *      (2) 通过 new 申请指针空间(动态内存)
 *          语法: struct 结构体名 * 指针名 = new 结构体名 {结构体内容具体的值}
 *      (3) 使用结构体指针访问结构体成员: 使用 ->
 *          语法: 指针名 -> 成员名
 * 结构体数组指针
 *      (1)常用于动态内存分配, 方便管理大量结构体占用的内存
 *      在已经声明好的结构体数组array, 使用 struct student *p_array = array;
 *      (2)语法:(静态内存)
 *          struct 结构体名 * 指针名 = 提前声明好的结构体数组名
 *         语法(动态内存申请)
 *         struct *指针名 = new 结构体名[数组长度] {{struct1}, {struct2},...}
 *         调用方式:    指针名[下标].指针成员名
 *
 *
 */
#include "iostream";
using namespace std;
int main() {
    struct student {
        string name;
        string gender;
        int age;
    };
    student stu_array[3];       // 声明结构体数组
    stu_array[0] = {"bob","♂", 16};
    stu_array[1] = {"<UNK>","<UNK>", 16};
    stu_array[2] = {"<UNK>","<UNK>", 16};
    for(int i=0;i<3;i++) {
        cout << "No " << i << ", " << stu_array[i].name << ", " << stu_array[i].gender << stu_array[i].age <<  endl;
     }

    struct student stu = {"周杰伦","1",33};
    struct student *p_stu = &stu;
    cout <<"the name is " << p_stu -> name << endl;

    struct student * stu_2 = new student {"周杰伦","1",33};
    cout <<"the name is " << stu_2 -> name << endl;
    delete stu_2;

    struct student * p_stu_ = new student[2] {
        {"周jie伦","1",22},
        {"周杰lun","1",11},
    };
    cout << p_stu_[0].name << endl << p_stu_[1].name << endl;
    delete[] p_stu_;

    // 信息录入
    struct student * p_student = new student[5] {
        {},{},{},{},{},
    };
    for (int i = 0; i <= 4; i++) {
        cout << "now it is No " << i << endl;
        cout << "please input your name: ";
        cin >> p_student[i].name;
        cout << "please input your gender: ";
        cin >> p_student[i].gender;
        cout << "please input your age: ";
        cin >> p_student[i].age;
        cout << "your input is " << "the name is " << p_student[i].name << ", the age is " << p_student[i].age << ", the gender is " << p_student[i].gender << endl;
     }
    delete[] p_student;
    return 0;
}