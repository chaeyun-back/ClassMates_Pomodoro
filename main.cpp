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

    
    system("mode con cols=100 lines=50"); //�ܼ�â ȭ�� ũ�� ����

    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1; //Ŀ���� ������
    cci.bVisible = FALSE; //Ŀ���� �����.
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);



    PointManger PM;                // ���� �ν��Ͻ�
    Tomato tomato(&PM);            // Tomato���� ����
    PlayerData player; // �÷��̾� ������ ����ü
    Pomodoro timer(&PM, &tomato, &player); // Pomodoro���� ����

    bool PlayEx = false; //���� ���� ���̰ų� ����� �����͸� �ҷ����� ture

    while (true) {
        int menu;

        if (PlayEx) {
            SavedataTitle(); // �÷��� ��, ���� ȭ�� 
        }
        else {
            DrawTitle(); // �ʱ� ���� ȭ��
        }


        cin >> menu;// �޴� ����
        system("cls");


        if (menu == 3) {   // ���� ���� ������ ����
            player.points = PM.nowPt();
            player.timerCount = timer.getTimerCount();
            tomato.getPlayerData(player); // tomato�κ��� �ֽ� ������ �޾ƿ���
            saveData(player);
            cout << "���α׷��� �����մϴ�." << endl;
            break;
        }
        else if (menu == 2) {
            DataLoading(); // ui ������ �ε� ȭ�� ���
            loadData(player);
            tomato.setPlayerData(player);  // tomato�� �ٽ� ����
            PM.addPt(player.points - PM.nowPt());
            PlayEx = true;
            cin.ignore(); cin.get();
            system("cls");
        }
        else if (menu == 1) {
            ModeStage(); // Ÿ�̸�, ���� ��� ���� ȭ�� ���
            int subMenu;
            cin >> subMenu;
            system("cls");

            if (subMenu == 1) {
                char choice;
                PlayEx = true;
                TimerSetStage(); // Ÿ�̸� ���� �� ���� ui ȭ�� ���
                cout << "         �ð��� ���� �����Ͻðڽ��ϱ�? (���� ����=y / �⺻=n): ";

                while (true) {
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        int focus, rest;
                        cout << "         ���� �ð�(��): ";
                        cin >> focus;
                        cout << "         �޽� �ð�(��): ";
                        cin >> rest;
                        timer.setTimes(focus, rest);
                        break;
                    }
                    else if (choice == 'n' || choice == 'N') {
                        break;
                    }
                    else {
                        cout << "         �߸��� �Է��Դϴ�. y �Ǵ� n�� �Է����ּ���: ";
                    }
                }

                system("cls");
                timer.start(tomato);

                // Ÿ�̸� ��� ���� ��

                LoadingStage(); //�ε� ui ȭ�� ���
                cin.ignore(); cin.get();
                system("cls");
            }
            else if (subMenu == 2) {
                GameInterface(tomato, PM, player); // ���Ӹ�� ����
                PlayEx = true;

                // ���� ��� ���� ��
                LoadingStage(); //�ε� ui ȭ�� ���
                cin.ignore(); cin.get();
                system("cls");
            }
            else {
                WrongLoadingStage(); //�߸��� �Է� �ε� ui ȭ�� ��� 
                cin.ignore(); cin.get();
                system("cls");
            }
        }
        else {
            WrongLoadingStage(); //�߸��� �Է� �ε� ui ȭ�� ���
            cin.ignore(); cin.get();
            system("cls");
        }
    }

    return 0;
}
