#include <iostream>
#include <string>
#include <vector>
#include "student.h"
using namespace std;

int main(){
    // 벡터로 학생 객체를 저장
    // 벡터 인덱스를 자리 배정으로 선정
    vector<Student> students={
        Student("Jenny",3),
        Student("Lisa",5),
        Student("Jisoo",7),
        Student("Rose",2),
        Student("Bruno",3),
        Student("Taeeun",4)
    };
    cout << students[1].getName();
    return 0;
}