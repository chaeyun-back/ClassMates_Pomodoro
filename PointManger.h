#pragma once
#include <iostream>

using namespace std;


class  PointManger{
private:
	int points;

public:

	// �÷��� �ʱ� ���� ����Ʈ ����
	PointManger() : points(100) {}

	// ����Ʈ ���� �Լ� (int�� ������ ����)
	void addPt(int amount) {
		points += amount;
		cout <<"      SYSTEM: " << amount << "����Ʈ�� ȹ���߽��ϴ�. " << endl;
		//cout << "      ���� ����Ʈ : " << points << endl;
	}

	// ����Ʈ ���� �Լ� (int�� ���ҷ� ����)
	void minusPt(int amount) {
			points -= amount;
			cout << "       SYSTEM: " << amount << "����Ʈ�� ����߽��ϴ�." << endl;
			cout << "       ���� ����Ʈ: " << points << endl;

	}

	// ���� ����Ʈ Ȯ��
	int nowPt() const {
		return points;
	}
};

