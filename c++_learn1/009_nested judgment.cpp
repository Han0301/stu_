//
// Created by 29873 on 25-5-10.
//
/* 循环嵌套判断
 * 在执行语句中在套入判断
 */
#include "iostream"
using namespace std;

int main() {
    int love;
    int weather;
    cout << "please input the love value, 1 or 0: ";
    cin >> love;
    if (love) {
        cout << "I will express my love!" <<endl;
        cout << "please input the weather value, 1 or 0: ";
        cin >> weather;
        if (weather) {
            cout << "let us have a spring outing!" <<endl;
        }
        else{cout << "let us watching a movie" << endl;}
    }
    else{cout << "I am just a joker";}

    int target = 6;
    int num;
    int num2;
    int num3;
    cout << "please input the num(1~10): ";
    cin >> num;
    if (num != target) {
        cout << "that wrong, try for only two times, your input is: ";
        cin >> num2;
        if (num2 != target) {
            cout << "that wrong, try for only one times, your input is: ";
            cin >> num3;
            if (num3 != target) {
                cout << "that wrong, the right answer is 6";
            }else{cout << "that right, the target is 6" <<endl;}
        }else{cout << "that right, the target is 6" <<endl;}
    }else{cout << "that right, the target is 6" <<endl;}
    return 0;
}