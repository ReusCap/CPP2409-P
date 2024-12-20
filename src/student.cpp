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
string Student::GetName(){
    return name;
}
// 주량 출력하는 함수
int Student::GetTolerance(){
    return tolerance;
}
// 술잔 출력하는 함수
int Student::GetGlasses(){
    return glasses;
}
// 한잔씩 마시게 하고, 현재까지 마신 잔 수 출력
void Student::IncGlasses(){
    glasses+=1;
    cout << "have a shot"  << endl;
    cout << name << " has drunk "<< glasses << " glasses\n" << endl;
}
// 객체의 aptNum 벡터에 n1과 n2 push하는 함수
void Student::SetAptNum(int n1, int n2) {
        apt_num.push_back(n1);
        apt_num.push_back(n2);
    }
// AptNum을 출력하는 함수
vector<int> Student::GetAptNum() {
    return apt_num;
}