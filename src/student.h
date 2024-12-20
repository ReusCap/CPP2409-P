#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student{
// 멤버 변수들 private으로 설정
private:
    // 이름
    string name;
    // 주량
    const int tolerance;
    // 마신 술잔 개수
    int glasses;
    // APT게임에서 배정받을 숫자vector
    vector<int> apt_num;

// 멤버 함수들은 public으로 설정
public:
    // 생성자
    Student();
    // 생성자
    Student(string name, int tolerance);
    
    // 이름 출력하는 함수
    string GetName();
    // 주량 출력하는 함수
    int GetTolerance();
    // 술잔 출력하는 함수
    int GetGlasses();
    // 한잔씩 마시게 하고, 현재까지 마신 잔 수 출력
    void IncGlasses();
    // 객체의 aptNum 벡터에 n1과 n2 push하는 함수
    void SetAptNum(int n1, int n2);
    // AptNum을 출력하는 함수
    vector<int> GetAptNum();
    
};