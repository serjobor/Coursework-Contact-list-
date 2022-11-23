#include <iostream>
#include <string>
#include <iomanip>
#include "List.h"
using namespace std;


void AddList(ListNOTE*& list, NOTE*& ya4eeka) // ���������� ������ � ������
{
	if (ya4eeka != NULL) 
	{
		NOTE* newelem = ya4eeka; //��������� ������ ��� ������ �������� ������
		if (!list) 
		{
			list = new ListNOTE;
			list->Head = newelem;
			list->Tail = newelem;
			list->Head->next = NULL;
			list->size = 1; //��� ������ ���������� �������� ����������� ����� ��������� � ������
				return;
		}
		
		NOTE* temp = list->Head; //��������� ������ ��� ������ �������� ������
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newelem;
		list->Tail = newelem;
		list->Tail->next = NULL;
		list->size++; //��� ������ ���������� �������� ����������� ����� ��������� � ������
	}
}
void numbering(ListNOTE*& list) //��������� � �������
{
	NOTE* tmp = list->Head; //��������� �� ������
	int i = 1;
	while (tmp) //���� �� �������� ������� ������� �� ����� ������
	{
		tmp->num = i;
		i++;
		tmp = tmp->next; //���������, ��� ����� ��������� �������
	}
}
void Show(ListNOTE* list) // ������������ ������
{
	if (list->size < 1)
	{
		cout << "������ ����" << endl;
		return;
	}
	numbering(list);
	NOTE* tempHead = list->Head; //��������� �� ������
	while (tempHead) //���� �� �������� ������� ������� �� ����� ������
	{
		cout << tempHead->num << " " << tempHead->Name << setw(15);
		cout << tempHead->Phone << " "; 
		cout << tempHead->birthday[0] << "." << tempHead->birthday[1] << "." <<tempHead->birthday[2] << endl; // ���� ��� ���

		tempHead = tempHead->next; //���������, ��� ����� ��������� �������
	}
	cout << "\n";
}

void Delete(ListNOTE*& list, NOTE* ya4eeka) //�������� �������� ������.................................................................................
{
	if (ya4eeka != NULL) 
	{
		NOTE* tmp = list->Head;
		if (ya4eeka == list->Head) 
		{
			list->Head = list->Head->next;
			list->size--;
			return;
		}
		while (tmp->next != ya4eeka)
		{
			tmp = tmp->next; //���������, ��� ����� ��������� �������
		}
		tmp->next = tmp->next->next;
		list->size--;
	}
}
NOTE* Search_by_Phone(ListNOTE*& list, string Phone) // ����� �� ������
{
	NOTE* tmp = list->Head; //��������� �� ������
	while (tmp) //���� �� �������� ������� ������� �� ����� ������
	{
		if (tmp->Phone == Phone) 
		{
			return tmp;
		}
		tmp = tmp->next; //���������, ��� ����� ��������� �������
	}
	cout << " �� ������� " << endl;
	return NULL;
}
NOTE* Search_by_Name(ListNOTE*& list, string Name) // ����� �� �����
{
	NOTE* tmp = list->Head; //��������� �� ������
	while (tmp) //���� �� �������� ������� ������� �� ����� ������
	{
		if (tmp->Name == Name) 
		{
			return tmp;
		}
		tmp = tmp->next; //���������, ��� ����� ��������� �������
	}
	cout << " �� ������� " << endl;
	return NULL;
}
void Search_by_NameALL(ListNOTE*& list, string Name) // ���� � ������ ��������� ������� ����, �� ��-��� ������� ��
{
	NOTE* tmp = list->Head; //��������� �� ������
	while (tmp) //���� �� �������� ������� ������� �� ����� ������
	{
		if (tmp->Name == Name) 
		{
			cout << setw(25) << tmp->Name << setw(15) << tmp -> Phone << " " << tmp->birthday[0] << "." << tmp->birthday[1] << "." << tmp->birthday[2] << endl;
		}
		tmp = tmp->next; //���������, ��� ����� ��������� �������
	}
}