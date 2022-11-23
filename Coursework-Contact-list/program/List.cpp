#include <iostream>
#include <string>
#include <iomanip>
#include "List.h"
using namespace std;


void AddList(ListNOTE*& list, NOTE*& ya4eeka) // Добавление ячейки в список
{
	if (ya4eeka != NULL) 
	{
		NOTE* newelem = ya4eeka; //Выделение памяти для нового элемента списка
		if (!list) 
		{
			list = new ListNOTE;
			list->Head = newelem;
			list->Tail = newelem;
			list->Head->next = NULL;
			list->size = 1; //При каждом добавлении элемента увеличиваем число элементов в списке
				return;
		}
		
		NOTE* temp = list->Head; //Выделение памяти для нового элемента списка
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newelem;
		list->Tail = newelem;
		list->Tail->next = NULL;
		list->size++; //При каждом добавлении элемента увеличиваем число элементов в списке
	}
}
void numbering(ListNOTE*& list) //Нумерация в консоли
{
	NOTE* tmp = list->Head; //Указываем на голову
	int i = 1;
	while (tmp) //Пока не выполнен признак прохода по всему списку
	{
		tmp->num = i;
		i++;
		tmp = tmp->next; //Указываем, что нужен следующий элемент
	}
}
void Show(ListNOTE* list) // Демонстрация списка
{
	if (list->size < 1)
	{
		cout << "Массив пуст" << endl;
		return;
	}
	numbering(list);
	NOTE* tempHead = list->Head; //Указываем на голову
	while (tempHead) //Пока не выполнен признак прохода по всему списку
	{
		cout << tempHead->num << " " << tempHead->Name << setw(15);
		cout << tempHead->Phone << " "; 
		cout << tempHead->birthday[0] << "." << tempHead->birthday[1] << "." <<tempHead->birthday[2] << endl; // день мес год

		tempHead = tempHead->next; //Указываем, что нужен следующий элемент
	}
	cout << "\n";
}

void Delete(ListNOTE*& list, NOTE* ya4eeka) //Удаление элемента списка.................................................................................
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
			tmp = tmp->next; //Указываем, что нужен следующий элемент
		}
		tmp->next = tmp->next->next;
		list->size--;
	}
}
NOTE* Search_by_Phone(ListNOTE*& list, string Phone) // Поиск по номеру
{
	NOTE* tmp = list->Head; //Указываем на голову
	while (tmp) //Пока не выполнен признак прохода по всему списку
	{
		if (tmp->Phone == Phone) 
		{
			return tmp;
		}
		tmp = tmp->next; //Указываем, что нужен следующий элемент
	}
	cout << " не найдено " << endl;
	return NULL;
}
NOTE* Search_by_Name(ListNOTE*& list, string Name) // Поиск по имени
{
	NOTE* tmp = list->Head; //Указываем на голову
	while (tmp) //Пока не выполнен признак прохода по всему списку
	{
		if (tmp->Name == Name) 
		{
			return tmp;
		}
		tmp = tmp->next; //Указываем, что нужен следующий элемент
	}
	cout << " не найдено " << endl;
	return NULL;
}
void Search_by_NameALL(ListNOTE*& list, string Name) // Если в списке несколько похожих имен, то фу-ция выводит их
{
	NOTE* tmp = list->Head; //Указываем на голову
	while (tmp) //Пока не выполнен признак прохода по всему списку
	{
		if (tmp->Name == Name) 
		{
			cout << setw(25) << tmp->Name << setw(15) << tmp -> Phone << " " << tmp->birthday[0] << "." << tmp->birthday[1] << "." << tmp->birthday[2] << endl;
		}
		tmp = tmp->next; //Указываем, что нужен следующий элемент
	}
}