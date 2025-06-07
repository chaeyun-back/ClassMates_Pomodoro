#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

struct PomodoroPet {
    int water = 50;
    int health = 50;
    int sunlight = 50;
};

struct PlayerData {
    int points = 0;
    PomodoroPet pet;
    int timerCount = 0;
    int careTurn = 0;
    bool endingSeen[6] = { false, false, false, false, false, false };
    bool hasSuger = false;
    bool hasSunglasses = false;

};

inline void saveData(const PlayerData& data, const std::string& filename = "userdata.txt") {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << data.points << "\n";
        outFile << data.pet.water << "\n";
        outFile << data.pet.health << "\n";
        outFile << data.pet.sunlight << "\n";
        outFile << data.timerCount << "\n";
        outFile << data.careTurn << "\n";
        outFile << data.hasSuger << "\n";
        outFile << data.hasSunglasses << "\n";

        for (int i = 0; i < 6; ++i)
            outFile << data.endingSeen[i] << "\n";
        outFile.close();
        std::cout << "데이터가 저장되었습니다.\n";
    }
    else {
        std::cerr << "데이터 저장을 실패하였습니다..\n";
    }
}

inline bool loadData(PlayerData& data, const std::string& filename = "userdata.txt") {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> data.points;
        inFile >> data.pet.water;
        inFile >> data.pet.health;
        inFile >> data.pet.sunlight;
        inFile >> data.timerCount;
        inFile >> data.careTurn;
        inFile >> data.hasSuger;
        inFile >> data.hasSunglasses;

        for (int i = 0; i < 6; ++i)
            inFile >> data.endingSeen[i];
        inFile.close();
        return true;
    }
    else {
        std::cerr << "저장된 파일이 없어 새 데이터로 시작합니다.\n";
        return false;
    }
}

