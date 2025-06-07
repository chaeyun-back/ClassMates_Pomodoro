#pragma once
#include <iostream>

using namespace std;


class  PointManger{
private:
	int points;

public:

	// 플레이 초기 보유 포인트 설정
	PointManger() : points(100) {}

	// 포인트 증가 함수 (int는 증가량 설정)
	void addPt(int amount) {
		points += amount;
		cout <<"      SYSTEM: " << amount << "포인트를 획득했습니다. " << endl;
		//cout << "      현재 포인트 : " << points << endl;
	}

	// 포인트 감소 함수 (int는 감소량 설정)
	void minusPt(int amount) {
			points -= amount;
			cout << "       SYSTEM: " << amount << "포인트를 사용했습니다." << endl;
			cout << "       현재 포인트: " << points << endl;

	}

	// 현재 포인트 확인
	int nowPt() const {
		return points;
	}
};

