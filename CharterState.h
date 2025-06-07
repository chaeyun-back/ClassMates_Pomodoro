#pragma once
#include <iostream>
#include <string>
#include "SaveSystem.h"
#include "PointManger.h"

using namespace std;

class Tomato {

private:
	int water; // 수분
	int health; // 건강
	int sunlight; //광합성
	bool Suger; // 엔딩 해금 아이템1(설탕)
	bool Sunglasses; // 엔딩 해금 아이템2(선글라스)
	PointManger* pointManager;


	//string은 상태 결과값 표시 기준 함수
	string standardState(int value) const {
		if (value >= 70) return "양호";
		else if (value >= 40) return "부족";
		else return "위험";
	}

	// 최대치 제한 함수 (100 초과 금지)
	int clampToMax(int value) const {
		return value > 100 ? 100 : value;
	}




public:
	int CareTurn;

	Tomato(PointManger* pm = nullptr, int w = 100, int h = 100, int s = 100, int c = 0, bool item1 = false, bool items2 = false)
		: pointManager(pm), water(w), health(h), sunlight(s), CareTurn(c), Suger(item1), Sunglasses(items2) {
	}

	void resetState() {
		water = 100;
		health = 100;
		sunlight = 100;
		CareTurn = 0;
		Suger = false;
		Sunglasses = false;

	}


	void setWater(int value) //초기 수분 상태 설정
	{
		water = clampToMax(value);
	}

	void setHealth(int value)  //초기 건강 상태 설정
	{
		health = clampToMax(value);
	}

	void setSunlight(int value)  //초기 광합성 상태 설정
	{
		sunlight = clampToMax(value);
	}

	// 상태 증가 함수 
	void addWater(int value)
	{
		if (pointManager && pointManager->nowPt() >= value)
		{
			water = clampToMax(water + value);
			CareTurn++;
		}
		else
		{
			cout << "       포인트가 부족하여 실행할 수 없습니다." << endl;
		}
	}
	void addHealth(int value)
	{
		if (pointManager && pointManager->nowPt() >= value)
		{
			health = clampToMax(health + value);
			CareTurn++;
		}
		else
		{
			cout << "       포인트가 부족하여 실행할 수 없습니다." << endl;
		}
	}
	void addSunlight(int value)
	{
		if (pointManager && pointManager->nowPt() >= value)
		{
			sunlight = clampToMax(sunlight + value);
			CareTurn++;
		}
		else
		{
			cout << "       포인트가 부족하여 실행할 수 없습니다." << endl;
		}
	}



	// 상태 감소 함수
	void minusWater()
	{
		int loss = rand() % 11 + 5; 
		water -= loss;
		if (water < 0) water = 0;
	}
	void minusHealth()
	{
		int loss = rand() % 11 + 5; 
		health -= loss;
		if (health < 0) health = 0;

	}
	void minusSunlight()
	{
		int loss = rand() % 11 + 5; 
		sunlight -= loss;
		if (sunlight < 0) sunlight = 0;
	}

	void TurnSuger(){
		Suger = true;
	}
	void TurnSunglasses() 
	{
		Sunglasses = true;
	}

	// 현재 상태 확인 함수
	int nowWater() const { return water; }
	int nowHealth() const { return health; }
	int nowSunlight() const { return sunlight; }
	int nowCareTurn() const { return CareTurn; }

	//아이템 보유 현황 함수 
	bool hasSuger() const {
		return Suger;
	}
	bool hasSunglasses() const {
		return Sunglasses;
	}
	string invent() const {
		if (Suger && Sunglasses)
		{
			return "       아이템 : 설탕, 선글라스";
		}
		else if (Suger) 
		{
			return "       아이템 : 설탕";
		}
		else if (Sunglasses) 
		{
			return "       아이템 : 선글라스";
		}
		else
		{
			return "       아이템 : 미보유";
		}
	}

	//육성 턴 증가에 따른 성장 단계
	string nowGrow() const {
		if (CareTurn < 4) 
		{
			return "씨앗";
			
		}
		else if (CareTurn < 10)
		{
			return "새싹";
		}
		else if (CareTurn < 16)
		{
			return "성장기";
		}
		else if (CareTurn < 20)
		{
			return "열매";
		}
		else if (CareTurn == 20)
		{
			return "엔딩";
		}
		
	}



	// 캐릭터 아스키 코드 아트
	string getAsciiArt() const
	{
		if (CareTurn < 4)
		{
			return R"(
                      111111111111111                       
                    10              101                    
                  10                  10                    
                1000                  1000                  
                10      101     101     00                  
              1110     10001   10001    0011                
            111100      101     101     001111              
            11  1011                   100   11             
                1001                  10001                
           1111111110000000000000000001111111111            
           1111111111000000000000000011111111111            
              111111111000000000000111111111                
              111111111111111111111111111111                
              111111111111111111111111111111               
              111111111111111111111111111111                
              111111111111111111111111111111                
              111111111111111111111111111111                
               1111111111111111111111111111                
                  1111111111111111111111                                                      
			)";
		}

		else if (CareTurn < 10)
		{
			return R"(
                         111111 1111111                        
                           111111111                           
                              111                              
                         11111000011111                        
                        11           101                        
                     1101              101                      
                    1011   11     11   1100                     
                    101   1001   1001    00                     
                   1001    00 111 00     1001                   
                 111 00        1         00 111                 
                1111100011111111111111110001111                 
                0011111111111111111111111111111                 
                   01                      01                   
                   01                      01                   
                   01                      01                   
                   01                      01                   
                   01                      01                   
                   001                    001                   
                    111111111111111111111111   
			)";
		}

		else if (CareTurn < 16)
		{
			return R"(
                                        1111111
                                       1111  111
                               1111   111     111    111
                            111111111111      10111111111
                            11     111111     101      111
                             111     111001111101       11
                             111     1001111111111   1111
                           111111111111          11111111111
                          1111    11001  1    1   101111111111
                         111       101  101  101  111       111
                         1111     1101   1    1   101      111
                           11111111001           111111111111
                              111111111111   111111  11111
                             111      100111110111      11
                             11      1111     11111     11
                             11111111101      11111111 111
                              1111111111      111  111111
                                       1111  111
                                         111111
			)";
		}

		else if (CareTurn < 20)
		{
			return R"(
                           111                            
                       11  111  11                        
                    11111111111111111                     
                  111               111                   
                 10                   01                  
                1       11     11       1                 
                0      1001   1001      0                 
                0       00     00       0                 
              110          111          011               
            111 1           1           1 111             
           100   10                   01   000            
            11    100               001     1             
                    10100111111100101                     
                    10             01                     
                    10             01                     
                   1001           1001                    
                 1111111          1111111  
			)";
		}
	} 

	// 엔딩 조건 확인 함수 추가
	bool isDead() const {
		return water <= 0 || health <= 0 || sunlight <= 0;
	}

	bool isHappyEnding() const {
		return water >= 90 && health >= 90 && sunlight >= 90;
	}

	bool isBitterEnding() const {
		return (water < 40 || health < 40 || sunlight < 40) && !isDead();
	}


		// 플레이어 데이터 저장 
		void setPlayerData(const PlayerData& data) {
			water = data.pet.water;
			health = data.pet.health;
			sunlight = data.pet.sunlight;
			CareTurn = data.careTurn;
			Suger = data.hasSuger;
			Sunglasses = data.hasSunglasses;
		}

		void getPlayerData(PlayerData& data) const {
			data.pet.water = water;
			data.pet.health = health;
			data.pet.sunlight = sunlight;
			data.careTurn = CareTurn;
			data.hasSuger = Suger;
			data.hasSunglasses = Sunglasses;
		}
};

