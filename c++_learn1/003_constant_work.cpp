//
// Created by 29873 on 25-5-8.
//

#include<iostream>
#include "windows.h"

using namespace std;
#define AGE 21
#define TALL 180.5
#define WEIGHT 56

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "我是周杰伦, 今年" << AGE << "岁." <<endl;
    cout << "身高" << TALL << "cm, 体重" << WEIGHT << "KG" << endl;
    return 0;
}
