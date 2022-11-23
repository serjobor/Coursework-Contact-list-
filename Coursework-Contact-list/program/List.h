#pragma once
using namespace std;
//структура ячейки
struct NOTE 
{
	int num;
	string Name;
	string Phone;
	int birthday[3];
	NOTE* next;
};
struct ListNOTE 
{
	NOTE* Head; //Первый элемент
	NOTE* Tail; // последний
	int size;
};

void AddList(ListNOTE*& list, NOTE*& ya4eeka);
void Show(ListNOTE* list);
void Delete(ListNOTE*& list, NOTE* ya4eeka);
NOTE* Search_by_Phone(ListNOTE*& list, string Phone);
NOTE* Search_by_Name(ListNOTE*& list, string Name);
void Search_by_NameALL(ListNOTE*& list, string Name);