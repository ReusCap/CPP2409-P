#include <iostream>
#include <string>
#include <vector>
#include "student.h"
#include <algorithm>
#include <random>
#include <stdexcept>
using namespace std;

void APT(vector<Student>& students,int &turn);
void ThreeSixNine(vector<Student>& students, int &turn);
void BaskinRobbins31(vector<Student>& students, int &turn);
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
        Student("Taeeun",4), // 태은
        Student("Misoo",5)  // 미수
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
    // BaskinRobbins31게임 설명 출력
    cout << "3. BaskinRobbins31 game: In this game, participants take turns and count sequentially from 1 to 31. On each turn, \n "
        "a player can call out between 1 to 3 consecutive numbers. Input numbers split based on spaces.\n "
        "The player who has to say number 31 loses the game.\n" << endl;

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
        } else if (choice == "BaskinRobbins31") {
            BaskinRobbins31(students, turn);       // 베스킨 라빈스 시작
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
    
    // 인당 숫자 2개씩 할당 받아야 하니까 학생 수 2배만큼 숫자 vector에 생성
    int size = students.size();
    int numsize = size * 2;
    vector<int> numbers;
    for (int i = 1; i <= numsize; ++i) {
        numbers.push_back(i); // 1부터 numsize만큼 넣는다.
    }
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
        // 예를 들어 학생 6명일 때 12층을 초과하더라도 1층에 있던 학생이 13층으로 올라가는 방식
        int index = (current_floor - 1) % (students.size() * 2); // 0부터 시작하는 인덱스
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
        cout << "Fool shot! Fool shot! Wrong direction! One more time!" << endl;
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
// 베스킨라빈스31게임 구현
void BaskinRobbins31(vector<Student>& students, int &turn){
    // 인트로 출력
    cout << "Baskin Robbins thirty-one! Baskin Robbins thirty-one!" << endl;
    // 방향 설정    
    string direction;
    // 방향 입력 (오른쪽이나 왼쪽)
    cout << "Which direction? (right or left): ";
    cin >> direction;
    // 잘못된 방향을 말할 경우 술을 마시고 다시 게임 시작하도록 설정
    if (direction != "right" && direction != "left"){
        cout << "Fool shot! Fool shot! Wrong direction! One more time!" << endl;
        // 방향 이상하게 말했으면 술 마시기
        students[turn].IncGlasses();
        return;
    }
    
    // 시작 숫자 초기화
    int current_number = 1;

    // while 루프 시작
    while (true) {
        // 현재 플레이어 정보
        string current_player = students[turn].GetName();
        cout << current_player << "'s turn: ";
        // 입력받기
        string input;
        // 한 줄로 입력받기 위해 getline사용
        // \n같은 문자 지우기 위해 ws조건도 추가
        getline(cin >> ws, input);

        // 넘버 벡터 선언
        // 매 while루프마다 numbers 벡터는 초기화됨
        vector<int> numbers;
        string temp = "";

        // try - catch문 사용
        try{
            // iterator 사용
            // ex) "1 2 3"을 ("1", " ", "2", " ", "3")으로 분리
            for (auto it = input.begin(); it != input.end(); ++it) {
                char ch = *it; // iterator가 가리키는 현재 문자

                // ch가 ' '이면 temp에 들어있는 숫자를 numbers 벡터에 push하고 temp를 clear한다.
                if (ch == ' ') {
                    if (!temp.empty()) {
                        numbers.push_back(stoi(temp)); // temp 문자열을 정수로 변환 후 push
                        temp.clear();
                    }
                }
                // ch에 "숫자"가 들어있으면 temp에 추가
                else {
                    temp += ch;
                }
            }
            // 마지막에 남은 숫자 numbers벡터에 push_back해주기
            if (!temp.empty()) {
                // stoi함수로 문자열 int로 바꿔줌
                numbers.push_back(stoi(temp));
            }
            
        // catch 숫자가 아닌 문자열 입력받는 경우
        } catch (const invalid_argument& e) {
            cout << "Fool shot! Fool shot! Invalid input detected!" << endl;
            students[turn].IncGlasses();
            return;

        // catch 범위 초과하는 숫자를 입력한 경우
        } catch (const out_of_range& e) {
            cout << "Fool shot! Fool shot! Number out of range!" << endl;
            students[turn].IncGlasses();
            return;
        }

        // 1 ~ 3개의 숫자만 입력했는지 확인
        // 3개보다 많이 숫자 부를 경우 탈락하고 술마시기
        if (numbers.size() < 1 || numbers.size() > 3) {
            cout << "Fool shot! Fool shot! You can only call 1 to 3 numbers!" << endl;
            // 술 카운트 증가 후 리턴
            students[turn].IncGlasses();
            return;
        }

        // iterator사용
        // numbers 벡터안의 숫자에 순서대로 접근
        for (auto it = numbers.begin(); it != numbers.end(); ++it) {
            int num = *it; // iterator가 가리키는 값을 가져옴

            // 현재 숫자에 대응하는 알맞은 숫자 말 못했으면 탈락시킨다.
            if (num != current_number) {
                cout << "Fool shot! Fool shot! Wrong number!" << endl;
                // 술 카운트 증가 후 리턴
                students[turn].IncGlasses();
                return;
            }

            // 31을 외치게 될 경우 탈락시킨다.
            if (current_number >= 31) {
                cout << endl << "Game over! " << current_player << " lost!" << endl;
                // 술 카운트 증가 후 리턴
                students[turn].IncGlasses();
                return;
            }

            // current_number 증가
            current_number++;
        }

        // 방향에 따라 턴 변경
        // 오른쪽일 경우 백터 인덱스 순서대로
        if (direction == "right") {
            turn = (turn + 1) % students.size();
        // 왼쪽일 경우 벡터 인덱스 반대 순서대로
        } else if (direction == "left") {
            turn = (students.size() + (turn - 1)) % students.size();
        }
    }
}