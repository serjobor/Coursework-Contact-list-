#pragma once

#include <iostream>
using namespace std;

int inputint()//�������� �� ������������� ������
{
	int x; int i = 0;
	cin >> x;
	while (cin.fail() || cin.get() != '\n')
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "��������� ����: ";
		cin >> x;
	}
	return x;
}