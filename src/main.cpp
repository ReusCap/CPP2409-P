#include <iostream>
#include <string>
#include <vector>
#include "student.h"
#include <algorithm>
#include <random>
using namespace std;

void APT(vector<Student>& students,int &Turn);
void Three_Six_Nine();
void Baskin_Robbins_31();
void printfloor_out(vector<Student>& students, int floor, int &Turn);
int find_nameIndex(vector<Student>& students, const string& name);

int main(){
    // 벡터로 학생 객체를 저장
    // 벡터 인덱스를 자리 배정으로 선정
    vector<Student> students={
        Student("Jenny",3), // 제니
        Student("Lisa",5),  // 리사
        Student("Jisoo",7), // 지수
        Student("Rose",2),  // 로제
        Student("Bruno",3), // 브루노 마스
        Student("Taeeun",4) // 태은
    };
    // 게임 설명 출력
    cout << "\n<Game Select>" << endl;
    // APT게임 설명 출력
    cout << "1. APT game: In this game, everyone placing both hands on top of each other simultaneously,\n "
        "and the host announces a floor number. As players count up from the bottom, they remove \n "
        "their hands one at a time and place them on top. The player whose hand lands on the announced \n "
        "floor number is the \"winner\" (or chosen player) for that round.\n" << endl;
    // 369게임 설명 출력
    cout << "2. 369 game: In this game involves counting up from 1, and whenever a number contains the digits 3, 6, or 9\n "
        "players must clap instead of saying the number.\n "
        "For example:\n  "
        "Number 13: Clap once\n  "
        "Number 33: Clap twice\n " << endl;
    // BR21게임 설명 출력
    cout << "3. BR21 game: In this game, participants take turns and count sequentially from 1 to 31. On each turn, \n "
        "a player can call out between 1 to 3 consecutive numbers. The player who has to say 31 loses the game.\n" << endl;

    int Turn = 0;
    bool game_Running=true;
    while(game_Running){
        string choice;
        // OO가 좋아하는 랜덤 게임! 무슨 게임! 게임 스타트!
        cout << students[Turn].getName() << "'s favorite random game! Which game! Game start!" << endl;
        // OO의 게임 선택
        cout << students[Turn].getName() << "'s choice: ";
        cin >> choice;

        if (choice == "APT") {
            APT(students, Turn);       // 아파트 게임 시작
        } else if (choice == "369") {
            Three_Six_Nine();          // 369게임 시작
        } else if (choice == "BR31") {
            Baskin_Robbins_31();       // 베스킨 라빈스 시작
        } else {
            // "병신샷~ 병신샷~ 다시!"라고 하면서 말실수 한 사람이 술 한잔 마시고 다시 게임 골라서 시작.
            cout << "Fool shot! Fool shot! One more time!" << endl;
            students[Turn].inc_glasses();
            continue;
        }
    }
    
    return 0;
}

void APT(vector<Student>& students, int &Turn){
    int floor;
    cout << "APT~ APT~ APT~ APT~" << endl;      // 인트로 : 아파트~ 아파트~ 아파트~ 아파트~
     do {
        cout << "Which floor?(1 to 20 floors only): "; // 몇층?(1~20층까지)
        cin >> floor;

        // 입력값 검증
        if (floor < 1 || floor > 20) {
            cout << "Invalid input! Please enter a floor between 1 and 20." << endl;
        }
    } while (floor < 1 || floor > 20);

    // 미리 숫자들 생성
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // 난수 생성 엔진 초기화
    // 난수 생성 엔진 객체 g
    random_device rd;
    mt19937 g(rd());
    // algorithm의 shuffle함수로 숫자들 섞어놓는다. 
    shuffle(numbers.begin(), numbers.end(), g);

    // for문과 set_aptNum()함수로 숫자 두개 저장
    // ex) Lisa(2,4), Jenny(1,5) ...
    for (int i = 0; i < students.size(); ++i) {
        students[i].set_aptNum(numbers[i * 2], numbers[i * 2 + 1]);
    }
    printfloor_out(students,floor,Turn);
    students[Turn].inc_glasses();


}

// 층 순서대로 출력하며 탈락시키는 함수
void printfloor_out(vector<Student>& students, int floor, int &Turn) {
    // 층 번호와 학생 이름을 저장할 벡터
    vector<pair<int, string>> floorAssignments;

    // 학생들의 aptNum을 기반으로 floorAssignments를 채움
    for (auto& student : students) {
        // 그 객체의 aptNum을 순회로 각각 push한다. 
        for (int apt : student.getAptNum()) {
            floorAssignments.push_back({apt, student.getName()});
        }
    }
    // 층 번호를 기준으로 정렬 (출력을 순서대로 하기 위해)
    // ex) {(1, "Jenny"), (2, "Jisoo"), (3, "Jenny"), (4, "Rose"), (5, "Taeeun")...}
    sort(floorAssignments.begin(), floorAssignments.end());

    // 현재 층수 설정
    int currentFloor = 1;
    while (true) {
        // 12층을 초과하더라도 1층에 있던 학생이 13층으로 올라가는 방식
        int index = (currentFloor - 1) % 12; // 0부터 시작하는 인덱스
        auto [assignedFloor, name] = floorAssignments[index];

        cout << name << ": " << currentFloor << " floor" << endl;

        // 목표 층수에 도달했으면 탈락 처리 후 종료
        if (currentFloor == floor) {
            cout << name << " is out of the game" << endl;
            Turn = find_nameIndex(students, name);
            return; // 함수 종료
        }

        currentFloor++; // 다음 층으로 진행
    }
}
// name에 해당하는 students벡터의 인덱스 값 반환하는 함수 
int find_nameIndex(vector<Student>& students, const string& name) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getName() == name) {
            return i; // 찾은 경우 인덱스 반환
        }
    }
    return -1; // 찾지 못한 경우 -1 반환
}
// 아래 두 게임은 구현 아직 못했다.
void Three_Six_Nine(){
    cout << "Three_Six_Nine game is not yet implemented." << endl;
}
void Baskin_Robbins_31(){
    cout << "Baskin_Robbins_31 game is not yet implemented." << endl;

}