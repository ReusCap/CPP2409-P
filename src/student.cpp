#include "student.h"

Student::Student()
    : name(""), glasses(0), tolerance(0) {}
Student::Student(string name, int tolerance)
    : name(name), glasses(0), tolerance(tolerance) {}
string Student::getName(){
    return name;
}
int Student::getTolerance(){
    return glasses;
}
