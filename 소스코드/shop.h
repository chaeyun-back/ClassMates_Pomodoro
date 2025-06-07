#pragma once
#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include "PointManger.h"
#include "CharterState.h"

using namespace std;

void ShowShopMenu(PointManger& pm, Tomato& tomato) {
    srand(static_cast<unsigned int>(time(0))); // 난수 시드 설정 (한 번만)

    int choice;
    while (true) {
        system("cls");
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       [ 상점 ]                                                                                    " << endl;
        cout << "                                                                                                   " << endl;
        cout << "            111111111" << endl;
        cout << "             000000000001" << endl;
        cout << "              111111100001" << endl;
        cout << "                     10000111111111111111111111111111111111111111111111111111" << endl;
        cout << "                      10000000000000000000000000000000000000000000000000000000" << endl;
        cout << "                       0000000000000000000000000000000000000000000000000000001" << endl;
        cout << "                       10000          10000              10000          100001" << endl;
        cout << "                        00001          00001             10001          10000" << endl;
        cout << "                        10001          10001             00001          00001" << endl;
        cout << "                        1000011111111110000011111111111110000011111111110000" << endl;
        cout << "                         000000000000000000000000000000000000000000000000001" << endl;
        cout << "                         10000111111111100000111111111110000011111111110000" << endl;
        cout << "                          00001         10001           00001         10001" << endl;
        cout << "                          10001         10000          100001         00001" << endl;
        cout << "                          100001         00001         10000         10000" << endl;
        cout << "                           10000000000000000000000000000000000000000000001" << endl;
        cout << "                           1000000000000000000000000000000000000000000000" << endl;
        cout << "                            1000111111   11111 1 111111  111111   11111" << endl;
        cout << "                            10000" << endl;
        cout << "                            100001" << endl;
        cout << "                             10000000000000000000000000000000000000001" << endl;
        cout << "                              100000000000000000000000000000000000000" << endl;
        cout << "                                  000011 100000        1000011 100001" << endl;
        cout << "                                  00001   10001        100001   10001" << endl;
        cout << "                                  1000000000001         1000000000001" << endl;
        cout << "                                   1100000001            1100000001" << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       1. 비료 (모든 상태가 +50 회복: 낮은 확률) - 500pt" << endl;
        cout << "       2. 설탕 (새로운 엔딩 해금: 1회 구매 가능) - 1000pt" << endl;
        cout << "       3. 선글라스 (새로운 엔딩 해금: 1회 구매 가능) - 1000pt" << endl;
        cout << "       0. 나가기" << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       구매할 아이템 또는 행동을 입력하세요: ";
        
        // 키보드 입력 처리 
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) { // 비료
            if (pm.nowPt() > 500) {
                int chance = rand() % 100; // 0~99
                if (chance < 20) { // 10% 확률 성공
                    tomato.addWater(50);
                    tomato.addHealth(50);
                    tomato.addSunlight(50);
                    cout << "       SYSTEM: 성공! 뽀모도로의 상태가 회복되었습니다. " << endl;
                }
                else {
                    cout << "       SYSTEM: 실패... 뽀모도로의 상태에 변화가 없습니다." << endl;
                }
                pm.minusPt(500);
            }
            else {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
            }
        }
        else if (choice == 2) { // 설탕
            if (tomato.hasSuger()) {
                cout << "       SYSTEM: 이미 설탕을 구매하셨습니다!" << endl;
            }
            else if (pm.nowPt() >= 1000) {
                tomato.TurnSuger();
                pm.minusPt(1000);
            }
            else {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
            }
        }
        else if (choice == 3) { // 선글라스
            if (tomato.hasSunglasses()) {
                cout << "       SYSTEM: 이미 선글라스를 구매하셨습니다!" << endl;
            }
            else if (pm.nowPt() >= 1000) {
                tomato.TurnSunglasses();
                pm.minusPt(1000);
            }
            else {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
            }
        }
        else {
            cout << "       SYSTEM: 잘못된 선택입니다." << endl;
        }

        cin.ignore();
        cin.get();
    }
}

