#pragma once
#include <iostream>
#include <string>
#include "CharterState.h"
#include "SaveSystem.h"
#include "PointManger.h"
#include "EndAlbum.h"
#include "shop.h"
using namespace std;


void GameInterface(Tomato& tomato, PointManger& PM, PlayerData& player) {

    // 캐릭터 상태 정보 자동 변화 
    auto getStatusText = [](int value) {
        if (value >= 70) return "양호";
        else if (value >= 40) return "부족";
        else return "위험";
    };

    while (true)
    {
        system("cls");

        //  엔딩 조건 체크
        if (tomato.nowCareTurn() >= 20)
        {
             if ((tomato.nowWater() >= 90 && tomato.nowHealth() >= 90 && tomato.nowSunlight() >= 90) && tomato.hasSuger() && tomato.hasSunglasses())
             {
                 player.endingSeen[5] = true;
                 ShowEnding(6); // 
             }

             else if ((tomato.nowWater() >= 90 && tomato.nowHealth() >= 90 && tomato.nowSunlight() >= 90) && tomato.hasSunglasses())
             {
                player.endingSeen[4] = true;
                ShowEnding(5); // 멋쟁이 토마토 엔딩
             }   

            else if ((tomato.nowWater() >= 40 || tomato.nowHealth() >= 40 || tomato.nowSunlight() >=  40) && tomato.hasSuger())
            {
                player.endingSeen[3] = true;
                ShowEnding(4); // 고당도 엔딩
            }

            else if (tomato.nowWater() <= 0 || tomato.nowHealth() <= 0 || tomato.nowSunlight() <= 0)
            {
                player.endingSeen[2] = true;
                ShowEnding(3); // 배드 엔딩
            }
            else if (tomato.nowWater() >= 90 && tomato.nowHealth() >= 90 && tomato.nowSunlight() >= 90)
            {
                player.endingSeen[0] = true;
                ShowEnding(1); // 해피 엔딩
            }
            else if (tomato.nowWater() < 40 || tomato.nowHealth() < 40 || tomato.nowSunlight() < 40)
            {
                player.endingSeen[1] = true;
                ShowEnding(2); // 중간 엔딩
            }

            tomato.resetState(); // 다시 상태 초기화
            break;
        }

        /* 게임 UI 구성 화면 */
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       ["<< tomato.nowGrow()<<"] " << tomato.nowCareTurn() << " 일차                                                                                              " << endl;
        cout << "                                                                                                   " << endl;

        // 캐릭터 아스키 코드 아트 호출
        cout << tomato.getAsciiArt() << endl; // 

        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;

        // 캐릭터(토마토) 상태 현황
        cout << "       수분 : " << tomato.nowWater() << "%(" << getStatusText(tomato.nowWater()) << ")             " << endl;
        cout << "       건강 : " << tomato.nowHealth() << "%(" << getStatusText(tomato.nowHealth()) << ")           " << endl;
        cout << "       광합성 : " << tomato.nowSunlight() << "%(" << getStatusText(tomato.nowSunlight()) << ")     " << endl;

        // 아이템 보유 현황
        cout << tomato.invent()<< endl;
        
        cout << "                                                                                                   " << endl;
        cout << "       [W] 물주기 -50pt [A] 영양제 주기 -150pt [S] 병해충 퇴치 -50pt [D] 일광욕 -100pt" << endl;
        cout << "                                                                                                   " << endl;
        cout << "       보유 포인트: " << PM.nowPt() << endl;
        cout << "                                                                                                   " << endl;
        cout << "       홈 이동: home         육성: 키보드 WASD        상점: shop            도감: album            " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       원하는 행동을 입력하세요:";        
        string key; // 키보드 입력 변수 선언
        cin >> key; // 입력 값


        
        /*  키보드 입력 처리 */
        if (key == "W" || key == "w") // 육성: 물주기
        {
            if (PM.nowPt() >= 50) 
            {
                tomato.addWater(5);
                PM.minusPt(50);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
                cin.ignore(); cin.get();
            }
        }
        else if (key == "A" || key == "a") // 육성: 영양제 주기
        {
            if (PM.nowPt() >= 150)
            {
                tomato.addWater(10);
                PM.minusPt(150);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
                cin.ignore(); cin.get();
            }

        }
        else if (key == "S" || key == "s")// 육성: 병해충 퇴치
        {
            if (PM.nowPt() >= 50)
            {
                tomato.addHealth(5);
                PM.minusPt(50);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
                cin.ignore(); cin.get();
            }


        }
        else if (key == "D" || key == "d") // 육성: 일광욕
        {
            if (PM.nowPt() >= 100)
            {
                tomato.addSunlight(10);
                PM.minusPt(100);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: 포인트가 부족합니다." << endl;
                cin.ignore(); cin.get();
            }
        }
        else if (key == "home" || key == "HOME" || key == "Home") // 홈으로 돌아가기
        { 
            break; 
        } 
        else if (key == "album")
        {
            ShowAlbumMenu(player);

        }
        else if (key == "shop") 
        {
            ShowShopMenu(PM, tomato);
        }

        // * 메뉴 추가 시, else if로 선언하면 됨.
        
    }
    system("cls");

}


