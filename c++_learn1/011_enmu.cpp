//
// Created by 29873 on 25-5-31.
//
/*  枚举:用户自定义的类型, 将数字标号定义为指定的符号
 *  定义:将数字或字符串符号化, 默认以0开始递增, 可单独为某一个元素指定数字的整数标号
 *  语法:
 *      enum 枚举名 {
 *          枚举元素1,      // 本质为数字0
 *          枚举元素2,      // 本质为数字1
 *          枚举元素3,      // 本质为数字2
 *          ...           // 最后的元素可有, 可无
 *      };
 *      或:
 *      enum 枚举名{
 *          枚举元素1 = 指定的整数标号     // 指定整数标号
 *          枚举元素2 = 指定的整数标号
 *          ...
 *      };
 */

#include "iostream"
using namespace std;
int main() {
    // 例:
    enum Season {
        String = 1,
        Summer,
        Autumn,
        Winter,
    };
    int num;
    cout << "please enter your number: (1 mean String, 2 mean Summer, 3 mean Autumn, 4 mean Winter)" << endl;
    cin >> num;
    switch (num) {
        case String:
            cout << "you've entered String" << endl;
            break;
        case Summer:
            cout << "you've entered Summer" << endl;
            break;
        case Autumn:
            cout << "you've entered Autumn" << endl;
            break;
        case Winter:
            cout << "you've entered Winter" << endl;
            break;
        default:
            cout << "you've entered nothing" << endl;
    }
    return 0;
}