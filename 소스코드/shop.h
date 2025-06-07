#pragma once
#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include "PointManger.h"
#include "CharterState.h"

using namespace std;

void ShowShopMenu(PointManger& pm, Tomato& tomato) {
    srand(static_cast<unsigned int>(time(0))); // ���� �õ� ���� (�� ����)

    int choice;
    while (true) {
        system("cls");
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       [ ���� ]                                                                                    " << endl;
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
        cout << "       1. ��� (��� ���°� +50 ȸ��: ���� Ȯ��) - 500pt" << endl;
        cout << "       2. ���� (���ο� ���� �ر�: 1ȸ ���� ����) - 1000pt" << endl;
        cout << "       3. ���۶� (���ο� ���� �ر�: 1ȸ ���� ����) - 1000pt" << endl;
        cout << "       0. ������" << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       ������ ������ �Ǵ� �ൿ�� �Է��ϼ���: ";
        
        // Ű���� �Է� ó�� 
        cin >> choice;
        if (choice == 0) break;

        if (choice == 1) { // ���
            if (pm.nowPt() > 500) {
                int chance = rand() % 100; // 0~99
                if (chance < 20) { // 10% Ȯ�� ����
                    tomato.addWater(50);
                    tomato.addHealth(50);
                    tomato.addSunlight(50);
                    cout << "       SYSTEM: ����! �Ǹ𵵷��� ���°� ȸ���Ǿ����ϴ�. " << endl;
                }
                else {
                    cout << "       SYSTEM: ����... �Ǹ𵵷��� ���¿� ��ȭ�� �����ϴ�." << endl;
                }
                pm.minusPt(500);
            }
            else {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
            }
        }
        else if (choice == 2) { // ����
            if (tomato.hasSuger()) {
                cout << "       SYSTEM: �̹� ������ �����ϼ̽��ϴ�!" << endl;
            }
            else if (pm.nowPt() >= 1000) {
                tomato.TurnSuger();
                pm.minusPt(1000);
            }
            else {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
            }
        }
        else if (choice == 3) { // ���۶�
            if (tomato.hasSunglasses()) {
                cout << "       SYSTEM: �̹� ���۶󽺸� �����ϼ̽��ϴ�!" << endl;
            }
            else if (pm.nowPt() >= 1000) {
                tomato.TurnSunglasses();
                pm.minusPt(1000);
            }
            else {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
            }
        }
        else {
            cout << "       SYSTEM: �߸��� �����Դϴ�." << endl;
        }

        cin.ignore();
        cin.get();
    }
}

