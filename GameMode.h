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

    // ĳ���� ���� ���� �ڵ� ��ȭ 
    auto getStatusText = [](int value) {
        if (value >= 70) return "��ȣ";
        else if (value >= 40) return "����";
        else return "����";
    };

    while (true)
    {
        system("cls");

        //  ���� ���� üũ
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
                ShowEnding(5); // ������ �丶�� ����
             }   

            else if ((tomato.nowWater() >= 40 || tomato.nowHealth() >= 40 || tomato.nowSunlight() >=  40) && tomato.hasSuger())
            {
                player.endingSeen[3] = true;
                ShowEnding(4); // ��絵 ����
            }

            else if (tomato.nowWater() <= 0 || tomato.nowHealth() <= 0 || tomato.nowSunlight() <= 0)
            {
                player.endingSeen[2] = true;
                ShowEnding(3); // ��� ����
            }
            else if (tomato.nowWater() >= 90 && tomato.nowHealth() >= 90 && tomato.nowSunlight() >= 90)
            {
                player.endingSeen[0] = true;
                ShowEnding(1); // ���� ����
            }
            else if (tomato.nowWater() < 40 || tomato.nowHealth() < 40 || tomato.nowSunlight() < 40)
            {
                player.endingSeen[1] = true;
                ShowEnding(2); // �߰� ����
            }

            tomato.resetState(); // �ٽ� ���� �ʱ�ȭ
            break;
        }

        /* ���� UI ���� ȭ�� */
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       ["<< tomato.nowGrow()<<"] " << tomato.nowCareTurn() << " ����                                                                                              " << endl;
        cout << "                                                                                                   " << endl;

        // ĳ���� �ƽ�Ű �ڵ� ��Ʈ ȣ��
        cout << tomato.getAsciiArt() << endl; // 

        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;

        // ĳ����(�丶��) ���� ��Ȳ
        cout << "       ���� : " << tomato.nowWater() << "%(" << getStatusText(tomato.nowWater()) << ")             " << endl;
        cout << "       �ǰ� : " << tomato.nowHealth() << "%(" << getStatusText(tomato.nowHealth()) << ")           " << endl;
        cout << "       ���ռ� : " << tomato.nowSunlight() << "%(" << getStatusText(tomato.nowSunlight()) << ")     " << endl;

        // ������ ���� ��Ȳ
        cout << tomato.invent()<< endl;
        
        cout << "                                                                                                   " << endl;
        cout << "       [W] ���ֱ� -50pt [A] ������ �ֱ� -150pt [S] ������ ��ġ -50pt [D] �ϱ��� -100pt" << endl;
        cout << "                                                                                                   " << endl;
        cout << "       ���� ����Ʈ: " << PM.nowPt() << endl;
        cout << "                                                                                                   " << endl;
        cout << "       Ȩ �̵�: home         ����: Ű���� WASD        ����: shop            ����: album            " << endl;
        cout << "                                                                                                   " << endl;
        cout << "   =============================================================================================   " << endl;
        cout << "                                                                                                   " << endl;
        cout << "       ���ϴ� �ൿ�� �Է��ϼ���:";        
        string key; // Ű���� �Է� ���� ����
        cin >> key; // �Է� ��


        
        /*  Ű���� �Է� ó�� */
        if (key == "W" || key == "w") // ����: ���ֱ�
        {
            if (PM.nowPt() >= 50) 
            {
                tomato.addWater(5);
                PM.minusPt(50);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
                cin.ignore(); cin.get();
            }
        }
        else if (key == "A" || key == "a") // ����: ������ �ֱ�
        {
            if (PM.nowPt() >= 150)
            {
                tomato.addWater(10);
                PM.minusPt(150);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
                cin.ignore(); cin.get();
            }

        }
        else if (key == "S" || key == "s")// ����: ������ ��ġ
        {
            if (PM.nowPt() >= 50)
            {
                tomato.addHealth(5);
                PM.minusPt(50);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
                cin.ignore(); cin.get();
            }


        }
        else if (key == "D" || key == "d") // ����: �ϱ���
        {
            if (PM.nowPt() >= 100)
            {
                tomato.addSunlight(10);
                PM.minusPt(100);
                cin.ignore(); cin.get();
            }
            else
            {
                cout << "       SYSTEM: ����Ʈ�� �����մϴ�." << endl;
                cin.ignore(); cin.get();
            }
        }
        else if (key == "home" || key == "HOME" || key == "Home") // Ȩ���� ���ư���
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

        // * �޴� �߰� ��, else if�� �����ϸ� ��.
        
    }
    system("cls");

}


