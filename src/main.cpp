#include <iostream>
#include <string>
#include <vector>
#include "student.h"
#include <algorithm>
#include <random>
using namespace std;

void APT(vector<Student>& students,int &turn);
void ThreeSixNine(vector<Student>& students, int &turn);
void BaskinRobbins31();
void PrintFloorOut(vector<Student>& students, int floor, int &turn);
int FindNameIndex(vector<Student>& students, const string& name);

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
        "players must clap instead of saying the number. input 'C' instead clap\n "
        "For example:\n  "
        "Number 7: 7\n  "
        "Number 13: C\n  "
        "Number 33: CC\n " << endl;
    // BR21게임 설명 출력
    cout << "3. BR21 game: In this game, participants take turns and count sequentially from 1 to 31. On each turn, \n "
        "a player can call out between 1 to 3 consecutive numbers. The player who has to say 31 loses the game.\n" << endl;

    int turn = 0;
    bool game_running=true;
    while(game_running){
        string choice;
        // OO가 좋아하는 랜덤 게임! 무슨 게임! 게임 스타트!
        cout << students[turn].GetName() << "'s favorite random game! Which game! Game start!" << endl;
        // OO의 게임 선택
        cout << students[turn].GetName() << "'s choice: ";
        cin >> choice;

        if (choice == "APT") {
            APT(students, turn);       // 아파트 게임 시작
        } else if (choice == "369") {
            ThreeSixNine(students, turn);    // 369게임 시작
        } else if (choice == "BR31") {
            BaskinRobbins31();       // 베스킨 라빈스 시작
        } else {
            // "병신샷~ 병신샷~ 다시!"라고 하면서 말실수 한 사람이 술 한잔 마시고 다시 게임 골라서 시작.
            cout << "Fool shot! Fool shot! One more time!" << endl;
            students[turn].IncGlasses();
            continue;
        }
    }
    
    return 0;
}

void APT(vector<Student>& students, int &turn){
    int floor;
    cout << "APT~ APT~ APT~ APT~" << endl;      // 인트로 : 아파트~ 아파트~ 아파트~ 아파트~
     do {
        cout << "Which floor?(1 to 20 floors only): "; // 몇층?(1~20층까지)
        cin >> floor;

        // 입력값 검증
        if (floor < 1 || floor > 20) {
            cout << "Please enter a floor between 1 and 20." << endl;
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
        students[i].SetAptNum(numbers[i * 2], numbers[i * 2 + 1]);
    }
    PrintFloorOut(students,floor,turn);
    // 걸린 차례 사람 술 마시기
    students[turn].IncGlasses();


}

// 층 순서대로 출력하며 탈락시키는 함수
void PrintFloorOut(vector<Student>& students, int floor, int &turn) {
    // 층 번호와 학생 이름을 저장할 벡터
    vector<pair<int, string>> floorAssignments;

    // 학생들의 aptNum을 기반으로 floorAssignments를 채움
    for (auto& student : students) {
        // 그 객체의 aptNum을 순회로 각각 push한다. 
        for (int apt : student.GetAptNum()) {
            floorAssignments.push_back({apt, student.GetName()});
        }
    }
    // 층 번호를 기준으로 정렬 (출력을 순서대로 하기 위해)
    // ex) {(1, "Jenny"), (2, "Jisoo"), (3, "Jenny"), (4, "Rose"), (5, "Taeeun")...}
    sort(floorAssignments.begin(), floorAssignments.end());

    // 현재 층수 설정
    int current_floor = 1;
    while (true) {
        // 12층을 초과하더라도 1층에 있던 학생이 13층으로 올라가는 방식
        int index = (current_floor - 1) % 12; // 0부터 시작하는 인덱스
        auto [assignedFloor, name] = floorAssignments[index];

        cout << name << ": " << current_floor << " floor" << endl;

        // 목표 층수에 도달했으면 탈락 처리 후 종료
        if (current_floor == floor) {
            cout << name << " is out of the game" << endl;
            turn = FindNameIndex(students, name);
            return; // 함수 종료
        }

        current_floor++; // 다음 층으로 진행
    }
}
// name에 해당하는 students벡터의 인덱스 값 반환하는 함수 
int FindNameIndex(vector<Student>& students, const string& name) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].GetName() == name) {
            return i; // 찾은 경우 인덱스 반환
        }
    }
    return -1; // 찾지 못한 경우 -1 반환
}

// 369 게임 실행 함수
void ThreeSixNine(vector<Student>& students, int &turn) {
    // 인트로 출력
    cout << "369! 369! 369! 369! (clap input 'C')" << endl;
    // 방향 설정    
    string direction;
    // 방향 입력 (오른쪽이나 왼쪽)
    cout << "Which direction? (right or left): ";
    cin >> direction;
    // 잘못된 방향을 말할 경우 술을 마시고 다시 게임 시작하도록 설정
    if (direction != "right" && direction != "left"){
        cout << "Fool shot! Fool shot! One more time!" << endl;
        // 방향 이상하게 말했으면 술 마시기
        students[turn].IncGlasses();
        return;
    }
    // 게임 시작 숫자 설정
    int current_number = 1;
    while (true) {
        // 현재 차례인 플레이어 출력
        string current_player = students[turn].GetName();
        cout << current_player << "'s turn: ";

        string input;
        cin >> input;

        // 현재 숫자에 3, 6, 9가 몇 번 포함되어 있는지 확인
        int clap_count = 0;
        for (char c : to_string(current_number)) {
            if (c == '3' || c == '6' || c == '9') {
                clap_count++;
            }
        }

        // 박수 또는 숫자 입력 검증
        // 틀린 입력(3,6,9가 포함되어 있는데 C를 안외친 경우, 3,6,9가 포함 안되어있는데, input이 currentNumber가 아닌경우)
        // string생성자로 string(3,'C')면 "CCC"가 출력되도록 한다.
        if ((clap_count > 0 && input != string(clap_count, 'C')) || (clap_count == 0 && input != to_string(current_number))) {
            cout << "Wrong! Fool shot! Fool shot! One more time!" << endl;
            // 걸린 차례 사람 술 마시기
            students[turn].IncGlasses();
            break;
        // 올바른 입력
        } else {
            current_number++; // 다음 숫자로 진행
            // 다음 플레이어로 차례 변경
            // 오른쪽 방향이면 다음 인덱스 사람 차례가 되게 함
            if (direction == "right"){
                turn = (turn + 1) % students.size();
            // 왼쪽 방향이면 이전 인덱스 사람 차례가 되게 함
            }else if(direction == "left"){
                turn = (students.size() + (turn - 1)) % students.size();
            }
            
        }
    }
}
// 아직 구현하지 못했다는 문구 출력
void BaskinRobbins31(){
    cout << "Baskin_Robbins_31 game is not yet implemented." << endl;

}