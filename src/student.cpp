#include "student.h"

// 생성자 : 파라미터 없을 때, 주량이 상수라 초기화 시켜줘야한다.
Student::Student()
    // 초기화
    : name(""), glasses(0), tolerance(0) {}

// 생성자 : 파라미터 없을 때, 주량이 상수라 초기화 시켜줘야한다.
Student::Student(string name, int tolerance)
    // 초기화
    : name(name), glasses(0), tolerance(tolerance) {}

// 이름 출력하는 함수
string Student::getName(){
    return name;
}
// 주량 출력하는 함수
int Student::getTolerance(){
    return glasses;
}
// 한잔씩 마시게 하고, 현재 마신 잔 수 출력.
void Student::inc_glasses(){
    glasses+=1;
    cout << glasses << endl;
}

