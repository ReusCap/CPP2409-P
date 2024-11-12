#include <iostream>
#include <string>
#include <vector>
#include "student.h"
using namespace std;

void APT();
void Three_Six_Nine();
void Baskin_Robbins_31();

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
            APT();   // 아파트 게임 시작
        } else if (choice == "369") {
            Three_Six_Nine(); // 369게임 시작
        } else if (choice == "BR31") {
            Baskin_Robbins_31(); // 베스킨 라빈스 시작
        } else {
            // "병신샷~ 병신샷~ 다시!"라고 하면서 말실수 한 사람이 술 한잔 마시고 다시 게임 골라서 시작.
            cout << "Fool shot! Fool shot! One more time!" << endl;
            students[Turn].inc_glasses();
            continue;
        }
    }
    
    return 0;
}
void APT(){

}
void Three_Six_Nine(){

}
void Baskin_Robbins_31(){

}