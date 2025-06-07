#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "timeset.h"
#include "StartTitle.h"
#include "GameMode.h"
#include "SaveSystem.h"
#include "CharterState.h"
using namespace std;


int main() {

    
    system("mode con cols=100 lines=50"); //콘솔창 화면 크기 조정

    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1; //커서의 사이즈
    cci.bVisible = FALSE; //커서를 숨긴다.
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);



    PointManger PM;                // 공유 인스턴스
    Tomato tomato(&PM);            // Tomato에도 전달
    PlayerData player; // 플레이어 데이터 구조체
    Pomodoro timer(&PM, &tomato, &player); // Pomodoro에도 전달

    bool PlayEx = false; //게임 진행 중이거나 저장된 데이터를 불러오면 ture

    while (true) {
        int menu;

        if (PlayEx) {
            SavedataTitle(); // 플레이 중, 메인 화면 
        }
        else {
            DrawTitle(); // 초기 메인 화면
        }


        cin >> menu;// 메뉴 선택
        system("cls");


        if (menu == 3) {   // 종료 전에 데이터 저장
            player.points = PM.nowPt();
            player.timerCount = timer.getTimerCount();
            tomato.getPlayerData(player); // tomato로부터 최신 데이터 받아오기
            saveData(player);
            cout << "프로그램을 종료합니다." << endl;
            break;
        }
        else if (menu == 2) {
            DataLoading(); // ui 데이터 로딩 화면 출력
            loadData(player);
            tomato.setPlayerData(player);  // tomato에 다시 세팅
            PM.addPt(player.points - PM.nowPt());
            PlayEx = true;
            cin.ignore(); cin.get();
            system("cls");
        }
        else if (menu == 1) {
            ModeStage(); // 타이머, 게임 모드 선택 화면 출력
            int subMenu;
            cin >> subMenu;
            system("cls");

            if (subMenu == 1) {
                char choice;
                PlayEx = true;
                TimerSetStage(); // 타이머 시작 전 설정 ui 화면 출력
                cout << "         시간을 직접 설정하시겠습니까? (직접 설정=y / 기본=n): ";

                while (true) {
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        int focus, rest;
                        cout << "         집중 시간(분): ";
                        cin >> focus;
                        cout << "         휴식 시간(분): ";
                        cin >> rest;
                        timer.setTimes(focus, rest);
                        break;
                    }
                    else if (choice == 'n' || choice == 'N') {
                        break;
                    }
                    else {
                        cout << "         잘못된 입력입니다. y 또는 n을 입력해주세요: ";
                    }
                }

                system("cls");
                timer.start(tomato);

                // 타이머 모드 종료 후

                LoadingStage(); //로딩 ui 화면 출력
                cin.ignore(); cin.get();
                system("cls");
            }
            else if (subMenu == 2) {
                GameInterface(tomato, PM, player); // 게임모드 진입
                PlayEx = true;

                // 게임 모드 종료 후
                LoadingStage(); //로딩 ui 화면 출력
                cin.ignore(); cin.get();
                system("cls");
            }
            else {
                WrongLoadingStage(); //잘못된 입력 로딩 ui 화면 출력 
                cin.ignore(); cin.get();
                system("cls");
            }
        }
        else {
            WrongLoadingStage(); //잘못된 입력 로딩 ui 화면 출력
            cin.ignore(); cin.get();
            system("cls");
        }
    }

    return 0;
}
