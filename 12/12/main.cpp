#include "heap.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <regex>
using namespace std;
regex checknum("[\\-]?[0-9]+");
heap::CMP cmpAAA(void* a1, void* a2)  //������� ���������
{
#define A1 ((AAA*)a1)
#define A2 ((AAA*)a2)
	heap::CMP
		rc = heap::EQUAL;
	if (A1->x > A2->x)
		rc = heap::GREAT;
	else
		if (A2->x > A1->x)
			rc = heap::LESS;
	return rc;
#undef A2
#undef A1 
}
//-------------------------------
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int k, choice;
	string b;
	heap::Heap h1 = heap::create(100, cmpAAA);
	for (;;)
	{
		cout << "1 - ����� ���� �� �����\n";
		cout << "2 - �������� �������\n";
		cout << "3 - ������� ������������ �������\n";
		cout << "4 - ������� ����������� �������\n";
		cout << "5 - ������� ������� �� ������\n";
		cout << "6 - ������� �������������� ���� � ���������� � ��������\n";
		cout << "0 - �����\n";
		cout << "�������� �����\n";
		getline(cin, b);
		while (b.length() != 1) {
			cout << "������������ ����\n";
			getline(cin, b);
		}
		choice = b[0];
		switch (choice)
		{
		case '0':  exit(0);
		case '1': {
			h1.scan(0);
			break;
		}
		case '2': {	AAA* a = new AAA;
			cout << "������� ����\n";
			getline(cin, b);
			while (!regex_match(b, checknum)) {
				cout << "������������ ����\n";
				getline(cin, b);
			}
			k = stoi(b);
			a->x = k;
			h1.insert(a, k);
			break;
		}
		case '3': {
			h1.extractMax();
			break;
		}
		case '4': {
			heap::Heap h3 = heap::create(100, cmpAAA);
			h1.extractMin(h3, h1);
			h1 = h3;
			break;
		}
		case '5': {
			int n;
			cout << "������� ����� ��������, ������� ������ �������\n";
			getline(cin, b);
			while (!regex_match(b, checknum)) {
				cout << "������������ ����\n";
				getline(cin, b);
			}
			n = stoi(b);
			h1.extractI(n);
			break;
		}
		case '6': {
			cout << "�� ������� ����� ����������� ���� ���. ��� ������ ����� ������� �������������� ����\n";
			int choice2;
			heap::Heap h2 = heap::create(30, cmpAAA);
			for (;;)
			{
				cout << "1 - ����� ���� �� �����\n";
				cout << "2 - �������� �������\n";
				cout << "3 - ������� ������������ �������\n";
				cout << "4 - ������� ����������� �������\n";
				cout << "5 - ������� ������� �� ������\n";
				cout << "6 - ���������� ���� � ��������� � ������� ����\n";
				cout << "�������� �����\n";
				getline(cin, b);
				while (b.length() != 1) {
					cout << "������������ ����\n";
					getline(cin, b);
				}
				choice2 = b[0];
				switch (choice2)
				{
				case '1': {
					h2.scan(0);
					break;
				}
				case '2': {	AAA* a = new AAA;
					cout << "������� ����\n";
					getline(cin, b);
					while (!regex_match(b, checknum)) {
						cout << "������������ ����\n";
						getline(cin, b);
					}
					k = stoi(b);
					a->x = k;
					h2.insert(a, k);
					break;
				}
				case '3': {
					h2.extractMax();
					break;
				}
				case '4': {
					heap::Heap h3 = heap::create(100, cmpAAA);
					h2.extractMin(h3, h2);
					h2 = h3;
					break;
				}
				case '5': {
					int n;
					cout << "������� ����� ��������, ������� ������ �������\n";
					getline(cin, b);
					while (!regex_match(b, checknum)) {
						cout << "������������ ����\n";
						getline(cin, b);
					}
					n = stoi(b);
					h2.extractI(n);
					break;
				}
				case '6': {
					h1.unionHeap(h2, h1);
					break;
				}
				default: {
					cout << "������������ ����\n";
				}
				}
				if (choice2 == '6') {
					break;
				}
			}
			break;
		}
		default:  cout << "\n������� �������� �������!\n";
		}
	} return 0;
}
