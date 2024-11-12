#include <iostream>
#include <string>
using namespace std;

class Student{
private:
    // 이름
    string name;
    // 주량
    const int tolerance;
    // 마신 술잔 개수
    int glasses;
public:
    Student();
    Student(string name, int tolerance);
    string getName();
    int getTolerance();
    void inc_glasses();
    
};