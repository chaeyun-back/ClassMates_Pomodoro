#pragma once

#include <Windows.h>
#undef max   // 매크로 제거
#undef min
#include <iostream>
#include <iomanip> 
#include <string>
#include <thread> //중요. 타이머를 타이머처럼 만들어 줌. 
#include <chrono> //가장 중요. 시간 단위를 나타내고, 시간을 지정하게 해줌
#include <conio.h>
#include <limits>
#include "PointManger.h" // 포인트 헤더 파일
#include "CharterState.h" // 캐릭터 헤더 파일
#include "StartTitle.h" // 화면 UI 출력 헤더 파일
#include "EndAlbum.h" //엔딩 헤더 파일

using namespace std;
using namespace std::chrono;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const WORD DEFAULT_COLOR = 7;     // 기본 흰색
const WORD COLOR_BLUE = 9; // 파란색

class Pomodoro {
private:
    int focusTime;  // 집중 시간 (분)
    int breakTime;  // 휴식 시간 (분)
    int rounds;     // 반복 횟수 (4회)
    int TimerCounter = 0; // 1세트 종료마다 세트 횟수 체크 변수
    PointManger* pointManager;
    Tomato* tomato;
    PlayerData* pdata;

    const string numberFont[11][5] = {//아스키 코드로 시계 숫자 변수
      { "■■■", "■□■", "■□■", "■□■", "■■■" }, // 0
      { "□□■", "□□■", "□□■", "□□■", "□□■" }, // 1
      { "■■■", "□□■", "■■■", "■□□", "■■■" }, // 2
      { "■■■", "□□■", "■■■", "□□■", "■■■" }, // 3
      { "■□■", "■□■", "■■■", "□□■", "□□■" }, // 4
      { "■■■", "■□□", "■■■", "□□■", "■■■" }, // 5
      { "■■■", "■□□", "■■■", "■□■", "■■■" }, // 6
      { "■■■", "□□■", "□□■", "□□■", "□□■" }, // 7
      { "■■■", "■□■", "■■■", "■□■", "■■■" }, // 8
      { "■■■", "■□■", "■■■", "□□■", "■■■" }, // 9
      { "□□□", "□■□", "□□□", "□■□", "□□□" }  // ':'
    };

    
    void gotoXY(int x, int y) { //아스키 코드 시계 위치고정 함수
        COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }


    //아스키 코드로 시계 숫자 출력 함수
    /* 숫자(분:초) 아트를 (x, y) 위치에 출력 – ■만 파란색
       파란색 적용 현재 안됌... 나중에 처리 예정
    */
    void printClock(int m, int s, int x, int y) {
        string t = (m < 10 ? "0" : "") + to_string(m) + ":" +
            (s < 10 ? "0" : "") + to_string(s);

        for (int row = 0; row < 5; ++row) {
            gotoXY(x, y + row);
            for (char c : t) {
                int idx = (c == ':') ? 10 : c - '0';
                for (char ch : numberFont[idx][row]) {
                    WORD col = (ch == '■') ? COLOR_BLUE : DEFAULT_COLOR;
                    SetConsoleTextAttribute(hConsole, col);
                    cout << ch;
                }
                cout << ' ';
            }
        }
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    }

    bool countdown(int minutes, const std::string& label) {
        int totalSeconds = minutes * 60;
        for (int i = totalSeconds; i >= 0; --i) {
            int m = i / 60;
            int s = i % 60;

            gotoXY(8, 2);
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

            /* 초기 UI 출력 멘트
            cout << "\r[" << label << "] 남은 시간: " << endl;
                //<< (m < 10 ? "0" : "") << m << ":"
               // << (s < 10 ? "0" : "") << s << ".";
            */

            printClock(m, s, 33, 4);

            // 일시정지 및 홈 키 감지
            if (_kbhit()) {  // 키가 눌렸는지 확인
                char ch = _getch();
                if (ch == 'p' || ch == 'P') {
                    gotoXY(15, 22);  // 보유 포인트 아래
                    cout << "일시정지됨. 다시 시작하려면 'r'을 누르세요..." << endl;
                    while (true) {
                        if (_kbhit()) {
                            char resumeKey = _getch();
                            if (resumeKey == 'r' || resumeKey == 'R') {
                                cout << "               ▶ 다시 시작합니다." << endl;
                                this_thread::sleep_for(chrono::seconds(2));  // 2초 대기
                                gotoXY(15, 22);
                                cout << string(500, ' '); // 멘트 지우기
                                gotoXY(15, 22);
                                break;
                            }
                        }
                        this_thread::sleep_for(chrono::milliseconds(100)); // CPU 낭비 방지
                    }
                }
                else if (ch == 'h' || ch == 'H') {
                    system("cls");
                    return false;// 홈 이동 처리
                }
                //this_thread::sleep_for(chrono::seconds(1)); // 관리자 확인용(타이머 배속 속도): 본 라인을 주석 처리하고 아래의 플레이어용을 주석을 지우세요.
            }
            this_thread::sleep_for(chrono::seconds(1)); // 플레이어용(타이머 정상 속도)
        }
        return true;
    }


public:
    Pomodoro(PointManger* pm = nullptr, Tomato* tm = nullptr, PlayerData* pd = nullptr)
        : pointManager(pm), tomato(tm), pdata(pd),focusTime(25), breakTime(5), rounds(4) {}//기본 설정 : 25분 집중, 5분 휴식, 4번 반복


    void setTimes(int focus, int rest) { //시간 설정용
        focusTime = focus;
        breakTime = rest;
    }


    void start(Tomato&tomato) { //시작
        system("cls");
        for (int i = 1; i <= rounds; ++i) {

            cout << "   =============================================================================================   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                      [ 현재:" << i << "번 / " << rounds << " ] 집중 시간" << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "   =============================================================================================   " << endl;
            cout << "                                                                                                   " << endl;
            cout << "               [P] 일시정지              [R] 재시작              [H] 홈으로 돌아가기               " << endl;
            cout << "                                                                                                   " << endl;
            cout << "               보유 포인트 : "<<(pointManager?pointManager->nowPt():0)<<"";
            cout << "                                                                                                   " << endl;// 멘트 출력용 빈 줄
            cout << "                                                                                                   " << endl;
            cout << "   =============================================================================================   " << endl;
            
            if (!countdown(focusTime, "집중!")) {     
                LoadingStage();                        
                cin.ignore(); cin.get();
                system("cls");
                return;
            }

            system("cls");



            if (i < rounds) {

                cout << "   =============================================================================================   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                      [ 현재:" << i << "번 / " << rounds << " ] 휴식 시간" << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "   =============================================================================================   " << endl;
                cout << "                                                                                                   " << endl;
                cout << "               [P] 일시정지              [R] 재시작              [H] 홈으로 돌아가기               " << endl;
                cout << "                                                                                                   " << endl;
                cout << "               보유 포인트 : " << (pointManager ? pointManager->nowPt() : 0) << "";
                cout << "                                                                                                   " << endl;
                cout << "                                                                                                   " << endl;// 멘트 출력용 빈 줄
                cout << "   =============================================================================================   " << endl;


                if (!countdown(breakTime, "휴식..")) { 
                    LoadingStage();
                    cin.ignore(); cin.get();
                    system("cls");
                    return;
                }

                system("cls");

            }
        }


        /*1세트(집중모드+휴식모드 4회 완료) 달성 시, timer 화면 출력 및 정보 */
        
        //타이머 총 횟수 증가
        TimerCounter++;

        //기존의 상태치 변수 선언
        int waterBefore = tomato.nowWater();
        int healthBefore = tomato.nowHealth();
        int sunlightBefore = tomato.nowSunlight();

        //상태 랜덤 감소 함수
        tomato.minusWater();
        tomato.minusHealth();
        tomato.minusSunlight();

        // 엔딩 3: 배드 엔드 (엔딩 기준: 상태치 하나라도 0이 되면 엔딩 3)
        if (tomato.nowWater() == 0 || tomato.nowHealth() == 0 || tomato.nowSunlight() == 0) {
            if (pdata) pdata->endingSeen[2] = true;   // 엔딩3 해금
            ShowEnding(3);
            tomato.resetState();
            cin.ignore();  cin.get();
            system("cls");
            return;   // 홈으로 복귀
        }

        // 상태 감소치 변수
        int waterLoss = waterBefore - tomato.nowWater();
        int healthLoss = healthBefore - tomato.nowHealth();
        int sunlightLoss = sunlightBefore - tomato.nowSunlight();

        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "             10000000001 101                                   101      101" << endl;
        cout << "                 100     111                                   101      101" << endl;
        cout << "                 101     111  1111111111111   1111111          101      101   11111011" << endl;
        cout << "                 101     101  101  1001  101 101   110         101      101  10011111001" << endl;
        cout << "                 101     101  101  101   10110011111101        101      101  101     101" << endl;
        cout << "                 101     101  101  101   101 101                101    1001  101     101" << endl;
        cout << "                 101     101  101  101   101  10000111           11000001    1001110011" << endl;
        cout << "                                                                             101" << endl;
        cout << "                                                                             01" << endl;
        cout << "                                                                                                   " << endl;
        cout << "  101    101                              1000011111    101         1001        101        1001" << endl;
        cout << "   101  101                               101    1101               1001        101   101  1001" << endl;
        cout << "    101001     1100011   101   101        101      101  101   1000111001        101 11001111001" << endl;
        cout << "     100      101   101  101   101        101      101  101  101    1001        101   101  1001" << endl;
        cout << "     101     101     101 101   101        101      101  101 101     1001        101   101  1001" << endl;
        cout << "     101      101111101   001 100         10111111011   101  1011 110001        101   101    " << endl;
        cout << "     111       1110111     11011          11111111      111   1100111111        111   111  1001" << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "      모든 셋트를 성공적으로 완료하셨습니다! 수고하셨습니다!" << endl;
        cout << "      총 수행한 세트: " << TimerCounter << endl;
        cout << "                                                                                                   " << endl;
        
        // 세트 완료 후, 포인트 획득 
        if (pointManager) pointManager->addPt(100);
        
        cout << "      보유 포인트 : " << (pointManager ? pointManager->nowPt() : 0) << "";
        cout << "                                                                                                   " << endl;
        cout << "      SYSTEM: 뽀모도로의 상태: 수분 - "<< waterLoss<< " 건강 - "<< healthLoss<<" 광합성 - "<< sunlightLoss << endl;
        cout << "                                                                                                   " << endl;
        cout << "              데이터를 확인했으면 Enter 키를 눌러 주세요...";
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // std:: 붙이기!
        cin.get();
       

        system("cls");

    }

    int getTimerCount() const { return TimerCounter; }
    void setTimerCount(int count);

};

// 현재 타이머 횟수 함수
inline void Pomodoro::setTimerCount(int count) {
    TimerCounter = count;
}
