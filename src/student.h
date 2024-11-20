#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student{
private:
    // 이름
    string name;
    // 주량
    const int tolerance;
    // 마신 술잔 개수
    int glasses;
    // APT게임에서 배정받을 숫자vector
    vector<int> aptNum;

public:
    Student();
    Student(string name, int tolerance);
    string GetName();
    int GetTolerance();
    void inc_glasses();

    void set_aptNum(int n1, int n2);
    vector<int> getAptNum();
    
};