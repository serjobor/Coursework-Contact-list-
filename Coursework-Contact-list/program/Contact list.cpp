// Проект_по_ОП.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Список контактов

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>  
#include <iomanip> 
#include <windows.h> 
#include <vector> 
#include "InputAndCheck.h"
#include "List.h"
#include <algorithm>

using namespace std;


void littleprint(NOTE* tmp) // Вывод контакта
{
	if (tmp)
		cout << setw(25) << tmp->Name << setw(15) << tmp->Phone << " " << tmp->birthday[0] << "." << tmp->birthday[1] << "." << tmp->birthday[2] << endl;
}

string nameconvert(string name) // Преобразование имени при выводе из файла
{
	for (size_t i = 0; i < name.length(); i++)  // .length()-Возвращает длину строки name
		if (name[i] == ' ')
			name[i] = '.';
	return name;
}

string nameunconvert(string name) // Преобразование имени при вводе в файл
{
	for (size_t i = 0; i < name.length(); i++)
		if (name[i] == '.')
			name[i] = ' ';
	return name;
}

bool namecheck(string name) // Проверка на имя 
{
	if (name.size() == 0) 
	{
		return false;
	}
	int check = 0;
	for (size_t i = 0; i < name.length(); i++)
	{
		// 
		if (int('a') <= int(name[i]) && int(name[i]) <= int('z') ||
			int('A') <= int(name[i]) && int(name[i]) <= int('Z') ||
			int('А') <= int(name[i]) && int(name[i]) <= int('Я') ||
			int('а') <= int(name[i]) && int(name[i]) <= int('я') ||
			int(name[i]) == int(' ') ||
			int(name[i]) == int('ё') ||
			int(name[i]) == int('Ё') ||
			int(name[i]) == int('-'))
		{
			//
		}
		else 
		{
			cout << name[i] << " - Недопустимый символ!" <<endl;
			return false;
		}
	}	
		return true;
}

bool phonecheck(string Phone) // Проверка номера телефона 
{
	if (Phone.length() != 11)
		return false;
	for (size_t i = 0; i < Phone.length(); i++) 
	{
		if (!iswdigit(Phone[i])) // проверка на соответствие знакам (от 0 до 9)
			return false;
	}
	return true;
}

bool phonesamecheck(ListNOTE*& list, string Phone)// Проверка номера телефона в списке
{
	if (list)
	{
		NOTE* tmp = list->Head;
		int count = 0; 
		for (int i = 0; i < list->size; i++) 
		{
			if (Phone == tmp->Phone)
				count++;
			tmp = tmp->next;
		}
		if (count < 1)
			return true;
		else
			return false;
	}
}

bool daycheck(int* BIRTHDAY) // Проверка на дату рождения (День[0] Месяц[1] Год[2])
{
	if (BIRTHDAY[0] < 1 || BIRTHDAY[0] > 31)
		return false;
	if ((BIRTHDAY[1] == 4 || BIRTHDAY[1] == 6 || BIRTHDAY[1] == 9 || BIRTHDAY[1] == 11) && BIRTHDAY[0] > 30 && BIRTHDAY[0] < 1)
		return false;
	if (BIRTHDAY[1] == 2 && BIRTHDAY[0] > 29)
		return false;
	if (BIRTHDAY[1] == 2 && BIRTHDAY[0] == 29) // Проверка на високосный год
	{
		int temp = BIRTHDAY[2] - 1000;
		while (temp > 0)
			temp -= 4;
		if (temp != 0)
			return false;
	}
	return true;
}

string inputstring(int flag) // Ввод строки
{
	string str;
	getline(cin, str); // Ввод данных с клавиатуры и запись в строку

	if (flag == 1)
		while (!namecheck(str))
		{
			cout << "Некорректный ввод. Пожалуйста, повторите: " << endl;
			getline(cin, str);
		}
	if (flag == 2)
		while (!phonecheck(str))
		{
			cout << "Некорректный ввод. Пожалуйста, повторите: " << endl;
			getline(cin, str);
		}

	int i = str.size();
	while (str[i - 1] == ' ') // является ли символ слева пробелом
	{
		str[i - 1] = '\0'; // конец строки
		i--;
	}
	for (int j = 0; j < i; ++j)///////////////////////////////////////////////////////////////////////////////////////////////////
	{
		while (str[j] == ' ' && str[j + 1] == ' ')
		{
			for (int k = unsigned(j); k < str.size() - 1; ++k)   // unsigned() - содержит только положительные числа
				str[k] = str[k + 1];                             // str.size() - возвращает размер str
			i--;
		}
	}
	if (str[0] == ' ')
	{
		for (int k = 0; k < str.size() - 1; ++k)
			str[k] = str[k + 1];
		i--;
	}
	str.resize(i); //  изменяет размер строки в длинну из i символов  Если меньше - удаляет 
	return str;    //                                                 Если больше - добавляет
}

bool ultimatecheck(NOTE*& tmp, ListNOTE*& list)  //  Окончательная проверка (для вывода данных из файла)
{
	if (!namecheck(tmp->Name) || !phonecheck(tmp->Phone))
	{
		cout << "Номера или Именна контактов не соответсвуют формату" <<endl; 
		return false;
	}
	if (!phonesamecheck(list, tmp->Phone))
	{
		cout << "Номера телефонов повторяются" << endl;
		return false;
	}/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (tmp->birthday[1] < 1 && tmp->birthday[1] > 12 || tmp->birthday[2] < 1900 && tmp->birthday[2] > 2021 || (!daycheck(tmp->birthday)))
	{
		cout << "Даты имеют не верный формат" << endl;
		return false;
	}
		return true;
}

void dobavlenie_elementa_v_spisok(ListNOTE*& list) // Добавление элемента в список
{
	NOTE* newya4eeka = new NOTE;

	cout << "Введите имя контакта:" << endl;
	string name = inputstring(1);
	newya4eeka->Name = name;

	cout << "Введите номер телефона (11 цифр)" << endl;
	string Phone = inputstring(2);

	while (!phonesamecheck(list, Phone))
	{
		cout << "Некорректный ввод(такой номер уже есть в базе). Повторите: " << endl;
		Phone = inputstring(2);
	}
	newya4eeka->Phone = Phone;

	cout << "Введите дату рождения.\nГод (От 1900 до 2021): ";
	newya4eeka->birthday[2] = inputint();

	while (newya4eeka->birthday[2] < 1900 || newya4eeka->birthday[2] > 2021) 
	{
		cout << "Некорректный ввод. Повторите: ";
		newya4eeka->birthday[2] = inputint();
	}

	cout << "Месяц(числом от 1 до 12): ";
	newya4eeka->birthday[1] = inputint();

	while (newya4eeka->birthday[1] < 1 || newya4eeka->birthday[1] > 12)
	{
		cout << "Некорректный ввод. Повторите: ";
		newya4eeka->birthday[1] = inputint();
	}

	cout << "День(числом от 1 до корректного числа в введенном ранее месяце): ";
	newya4eeka->birthday[0] = inputint();

	while (!daycheck(newya4eeka->birthday))
	{
		cout << "Некорректный ввод. Повторите: ";
		newya4eeka->birthday[0] = inputint();
	}

	AddList(list, newya4eeka); // добавление списка
	cout << "Добавлено в список" << endl;
}

int nalichie_imen_v_spiske(ListNOTE*& list, string name) // Проверка на наличие имен в списке
{
	int count = 0;
	NOTE* tmp = list->Head;
	for (int i = 0; i < list->size; i++) 
	{
		if (tmp->Name == name)
			count++;
		tmp = tmp->next;
	}
	return count;
}

int nalichie_nomera_telepona_v_spiske(ListNOTE*& list, string Phone) // Проверка на наличие номера тел в списке
{
	NOTE* tmp = list->Head;
	for (int i = 0; i < list->size; i++) 
	{
		if (tmp->Phone == Phone)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

void redactirovanie_elementa_v_spiske(ListNOTE*& list) // редактирование елемента в списке

{
	cout << "Введите имя абонента или номер телефона \n : ";
	string NameOrPhone;
	string Name = "";
	string Phone = "";
	NOTE* tmp = new NOTE;
	getline(cin, NameOrPhone);
	cout << "Проверяю имя ли это?" << endl;
	while (!namecheck(NameOrPhone))
	{
		cout << "Проверяю номер ли это?" << endl;
		if (phonecheck(NameOrPhone)) 
		{
			cout << "Это номер! Ищу в базе: " << endl;
			Phone = NameOrPhone;
			break;
		}
		cout << "Некорректный ввод. Повторите: " << endl;
		getline(cin, NameOrPhone);
	}
	if (Phone == "") //если есть имя
	{
		Name = NameOrPhone;
		cout << "Это имя! Ищу в базе: " << endl;
		if (nalichie_imen_v_spiske(list, Name) < 1)
		{
			cout << "Не найдено: " << endl;
			return;
		}
		else
		{
			//если имя одно
			if (nalichie_imen_v_spiske(list, Name) == 1)
			{
				tmp = Search_by_Name(list, Name);
				littleprint(tmp);
			}
			//если имён много
			else 
			{
				cout << "Найдено несколько людей \n";
				NOTE* tmp = list->Head;
				int q = 0;
				while (tmp) 
				{
					if (tmp->Name == Name)
					{
						cout << q << ' ';
						littleprint(tmp);
						q++;
					}
					tmp = tmp->next;
				}
				cout << "Введите номер телефона: \n";
				getline(cin, Phone);
				while (!phonecheck(Phone) || !Search_by_Phone(list, Phone))
				{
					cout << "Некорректный ввод. Повторите: " <<	endl;
					getline(cin, Phone);
				}
			}
		}
	}

	if (Phone != "") //если есть телефон
	{
		if (!nalichie_nomera_telepona_v_spiske(list, Phone)) 
		{
			cout << "Не найдено: " << endl;
				return;
		}
		else 
		{
			tmp = Search_by_Phone(list, Phone);
			cout << "Найдено " << endl;
			littleprint(tmp);
		}
	}

		cout << "  __________________________________" << endl;
		cout << " |Введите номер команды:           |" << endl;
		cout << " | 1 Редактирования имени абонента |" << endl;
		cout << " | 2 Редактирование номера телефона|" << endl;
		cout << " | 3 Редактирование даты рождения  |" << endl;
		cout << " |_________________________________|" << endl;
		cout << " |Другая цифра - выход             |" << endl;
		cout << " |_________________________________|" << endl;
		cout << " :";

		int menu = inputint();

			switch (menu)
			{
			case 0:
				break;
			case 1:
			{
				cout << "Введите имя абонента: " << endl;
				string nam2 = inputstring(1);
				while (!namecheck(nam2))
				{
					cout << "Некорректный ввод. Повторите: " << endl;
					string nam2 = inputstring(1);
				}
				tmp->Name = nam2;
				cout << "Отредактированно" << endl;
				break;
			}
			case 2:
			{
				cout << "Введите номер телефона " << endl;
				string pho2 = inputstring(2);
				while (!phonesamecheck(list, pho2))
				{
					cout << "Этот номер уже существует. Повторите: " << endl;
					pho2 = inputstring(2);
				}
				tmp->Phone = pho2;
				cout << "Отредактированно" << endl;
				break;
			}
			case 3:
			{
				cout << "Введите дату рождения.\nГод (от 1900 до 2021): ";
				tmp->birthday[2] = inputint();
				while (tmp->birthday[2] < 1900 || tmp->birthday[2] > 2021)
				{
					cout << "Некорректный ввод. Повторите: ";
					tmp->birthday[2] = inputint();
				}
				cout << "Месяц(числом от 1 до 12): ";
				tmp->birthday[1] = inputint();
				while (tmp->birthday[1] < 1 || tmp->birthday[1] > 12)
				{
					cout << "Некорректный ввод. Повторите: ";
					tmp->birthday[1] = inputint();
				}
				cout << "День(числом от 1 до корректного числа в введенном ранее месяце): ";
				tmp->birthday[0] = inputint();
				while (!daycheck(tmp->birthday))
				{
					cout << "Некорректный ввод. Повторите: ";
					tmp->birthday[0] = inputint();
				}
				cout << "Отредактированно" << endl;
			}
			}		
}

void notedelete(ListNOTE*& list) // Удаление контакта по данным
{
	cout << "Введите имя абонента или номер телефона " << endl;
	string NameOrPhone;
	string Phone;
	string name;
	getline(cin, NameOrPhone);
	while (!namecheck(NameOrPhone))
	{
		cout << "Проверяю номер ли это?" << endl;
		if (phonecheck(NameOrPhone)) 
		{
			cout << "Это номер! Ищу в базе: " << endl;
			Phone = NameOrPhone;
			NOTE* tmp = Search_by_Phone(list, Phone);
			if (tmp)
			{
				littleprint(tmp);
				cout << "Удалено" << endl;
				Delete(list, tmp);
			}
			return;
		}
		getline(cin, NameOrPhone);
	}
	name = NameOrPhone;
	if (nalichie_imen_v_spiske(list, name) > 0)
	{
		if (nalichie_imen_v_spiske(list, name) > 1)
		{
			cout << "Абонентов с таким именем найдено несколько. Введите номер телефона(телефон - уникален) : " << std::endl;
				Search_by_NameALL(list, name);
			string Phone;
			getline(cin, Phone);
			while (!phonecheck(Phone))
			{
				cout << "Некорректный ввод. Повторите: " << endl;
				getline(cin, Phone);
			}
			Delete(list, Search_by_Phone(list, Phone));
			return;
		}
		else 
		{
			
			cout << "Удалено" << endl;
			Delete(list, Search_by_Name(list, name));
			return;
		}
	}
	else
	{
		cout << "Этого имени абонента нет." << endl;
	}
}

void fileout(ListNOTE*& list) // сохранить в файл
{
	ofstream fout("database.txt");//////////////////////////////////////////////////////////
	    
		NOTE * tmp = list->Head;
	while (tmp)
	{
		string name = nameconvert(tmp->Name);
		fout << '\n';
		fout << ' ' << name;
		fout << ' ' << tmp->Phone;
		fout << ' ' << tmp->birthday[0];
		fout << ' ' << tmp->birthday[1];
		fout << ' ' << tmp->birthday[2];
		tmp = tmp->next;
	}
	fout.close();
}

void filein(ListNOTE*& list) // загрузить из файла
{
	ifstream fin("database.txt");
	if (!fin.is_open()) 
	{
		cout << "Не удалось открыть файл(возможно файла не существует)." << endl;
	}
	else
	{
		bool flag = true;
		if (list)
			list = NULL;
		while (!fin.eof())  // файл не пуст
		{
			NOTE* tmp = new NOTE;
			string name;
			fin >> name >> tmp->Phone >> tmp->birthday[0] >> tmp->birthday[1] >> tmp -> birthday[2];
			tmp->Name = nameunconvert(name);
			if (!ultimatecheck(tmp, list) || tmp->Name == "")
			{
				cout << "Файл не коректен." << endl;
				list = NULL;
				flag = false; break;
			}
			AddList(list, tmp);
		}
		if (flag)
		{
			cout << "Загрузка завершена!" << endl;
		}
		fin.close();
	}
}

int comp_name(NOTE* num1, NOTE* num2) 
{
	if (num1->Name < num2->Name)
		return true;
	else
		return false;
}

ListNOTE* data_sort_name(ListNOTE*& list) 
{
	cout << "Сортирую" << endl;
	NOTE* tmp = list->Head;
	NOTE* newtmp = list->Head;
	ListNOTE* newlist = NULL;

	vector<NOTE*> v;
	while (tmp)
	{
			v.push_back(tmp);              // Добавление в конец вектора
		tmp = tmp->next;
	}
	
	sort(begin(v), end(v), comp_name);     // сортировка для comp_name.
	                                       // begin(v)-возвращает итератор, который указывает на первый элемент в "v".
	for (int i = 0; i < v.size(); i++)     // end(v)-возвращает итератор, который указывает на конец "v".
	{                                     // v.size()- возращает размер длины вектора "v".
		littleprint(v[i]);                 
	}                                     
	
	cout << endl;
	cout << "Сортировка окончена!" << endl;
	cout << "Сохранить отсортированный вид?" << endl;
	cout << "1 - да сохранить || другое - нет " << endl;
	int x = inputint();
	if (x == 1) 
	{
		for (int i = 0; i < v.size(); i++) 
		{
			v[i]->next = NULL;
			AddList(newlist, v[i]);
		}
		Show(newlist);
		return newlist;
	}
	else 
	{
		return list;
	}
	
}

int comp_phone(NOTE* num1, NOTE* num2)     
{
	if (num1->Phone > num2->Phone)
		return true;
	else
		return false;
}

ListNOTE* data_sort_phone(ListNOTE*& list) 
{
	cout << "Сортирую по убыванию" << endl;
	NOTE* tmp = list->Head;
	NOTE* newtmp = list->Head;
	ListNOTE* newlist = NULL;

	 vector<NOTE*> v;
	while (tmp)
	{
		v.push_back(tmp);
		tmp = tmp->next;
	}
	 
	sort(begin(v), end(v), comp_phone);     // сортировка(в обратном направлении) для comp_name.
											// begin(v)-возвращает итератор, который указывает на первый элемент в "v".
	for (int i = 0; i < v.size(); i++)      // end(v)-возвращает итератор, который указывает на конец "v".
	{                                       // v.size()- возращает размер длины вектора "v".
		littleprint(v[i]);                  
	} 
	

	cout << endl;
	cout << "Сортировка окончена!" << endl;
	cout << "Сохранить отсортированный вид?" << endl;
	cout << "1 - да сохранить || другое - нет " << endl;
	int x = inputint();
	if (x == 1) 
	{
		for (int i = 0; i < v.size(); i++) 
		{
			AddList(newlist, v[i]);
		}
		return newlist;
	}
	else 
	{
		return list;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "rus");	
	system("color 0F");

	ListNOTE* list = NULL;
	
	int menu;
	menu = 1;
	while (menu)
	{
		if (list == NULL) 
		{
			cout << endl;
			cout << "  ____________________________________ " << endl;
			cout << " |Введите номер команды:              |\n";
			cout << " | 1 добавить новый элемент в список. |\n";
			cout << " | 8 загрузить из файла database.     |\n";
			cout << " | 0 выход.                           |\n";
			cout << " |____________________________________| " << endl;
			cout << " : ";
		}
		else
		{
			system("pause");
			system("cls");
			cout << "  ______________________________________" << endl;
			cout << " |Введите номер команды:                |\n";
			cout << " | 1 - добавить новый элемент в список. |\n";
			cout << " | 2 - редактировать.                   |\n";
			cout << " | 3 - удалить элемент из списка.       |\n";
			cout << " | 4 - сортировать.                     |\n";
			cout << " | 5 - поиск.                           |\n";
			cout << " | 6 - вывод на экран.                  |\n";
			cout << " | 7 - сохранить.                       |\n";
			cout << " | 8 - загрузить из файла.              |\n";
			cout << " | 0 - выход.                           |\n";
			cout << " |______________________________________| " << endl;
			cout << " : ";
		}
		menu = inputint();

		if (menu == 0)
			break;

		else if (menu == 1)
			dobavlenie_elementa_v_spisok(list);

		else if (menu == 2 && list)
		{
			Show(list);
			redactirovanie_elementa_v_spiske(list);
		}

		else if (menu == 3 && list)
		{
			if (list) 
			{
				Show(list);
				cout << "_________________________________ "<< endl;
				cout << "|Введите номер команды:          |" << endl;
				cout << "| 1 - Удалить по номеру в списке.|" << endl;
				cout << "| 2 - Удалить по данным.         |" << endl;
				cout << "|________________________________|" << endl;
				cout << "|Другая цифра - выход            |" << endl;
				cout << "|________________________________|" << endl;
				int choice = inputint();

				if (choice == 1)
				{
					cout << "введите номер в списке" << endl;
					int num = 0;
					while (num == 0 || num > list->size)
					{
						cout << "Повторите ввод: ";
						num = inputint();
					}
					NOTE* tmp = list->Head;
					while (tmp->num != num)
					{
						tmp = tmp->next;
					}
					littleprint(tmp);
					cout << "Удалено" << endl;
					Delete(list, tmp);
				}
				else if (choice == 2)
				{
					notedelete(list);
				}
				
			}
		}
		else if (menu == 4 && list)
		{
			cout << "Сортировка:" << endl;
			cout << " _________________________ " << endl;
			cout << "|Введите номер команды:   |" << endl;
			cout << "| 1 - по имени.           |" << endl;
			cout << "| 2 - по номеру телефона. |" << endl;
			cout << "|_________________________|" << endl;
			cout << "|Другая цифра - выход     |" << endl;
			cout << "|_________________________|" << endl;
			int choice = inputint();
			if (choice == 1)
			{
				Show(list);
				list = data_sort_name(list);
			}
			else if (choice == 2)
			{
				Show(list);
				list = data_sort_phone(list);
			}
		}
		
		else if (menu == 5 && list)
		{
			Show(list);
			cout << "Поиск:" << endl;
			cout << " _________________________ " << endl;
			cout << "|Введите номер команды:   |" << endl;
			cout << "| 1 - по номеру телефона. |" << endl;
			cout << "| 2 - по имени.           |" << endl;
			cout << "|_________________________|" << endl;			
			cout << "|Другая цифра - выход     |" << endl;
			cout << "|_________________________|" << endl;
			int choice = inputint();
			if (choice == 1) 
			{
				cout << "(для отмены поиска введите 0)" << endl;
				cout << "Введите телефон: \n";
				string Phone;
				getline(cin, Phone);
				while (!phonecheck(Phone) || phonesamecheck(list, Phone))
				{
					if (Phone == "0")
						break;
					
						cout << "Телефон не найден или некорректен!Проверьте правильность ввода!" << endl;
						cout << "(для выхода введите 0)" << endl;
					getline(cin, Phone);
				}
				if (Phone != "0") 
				{
					NOTE* tmp = Search_by_Phone(list, Phone);
					littleprint(tmp);
				}
			}
			else if (choice == 2)
			{
				cout << "Введите имя: " << endl;
				string name;
				getline(cin, name);
				while (!namecheck(name))
				{
					cout << "Некорректный ввод. Повторите: " << endl;
					getline(cin, name);
				}
				if (nalichie_imen_v_spiske(list, name) < 1) ///
				{
					cout << "Данного контакта НЕТ! \n";
				}
				//если имён много
				else
				{
					if (nalichie_imen_v_spiske(list, name) == 1) ///
					{
						littleprint(Search_by_Name(list, name));
					}
					else
					{
						cout << "Найдено несколько людей \n";
						NOTE* tmp = list->Head;
						int q = 0;
						while (tmp)
						{
							if (tmp->Name == name)
							{
								cout << q << ' ';
								littleprint(tmp);
								q++;
							}
							tmp = tmp->next;
						}
						cout << "Введите телефон \n";
						string Phone;
						getline(cin, Phone);
						while (!phonecheck(Phone))
						{
							getline(cin, Phone);
							cout << "Некорректный ввод. Повторите: " << endl;
						}
						tmp = Search_by_Phone(list, Phone);
						littleprint(tmp);
					}
				}
			}
		}
		else if (menu == 6 && list)
			Show(list);
		else if (menu == 7 && list)
		{
			if (list)
				fileout(list);
			cout << "Сохранено!" << endl;
		}
		else if (menu == 8) 
        {
			int choice = 1;
			if (list) 
			{				
				cout << "Это удалит старую базу! Вы уверены?" << endl;
				cout << "1 - да || 2 - нет\n";
				choice = inputint();
			}
			if (choice == 1)
			{
				filein(list);
			}
			else if (choice == 2);
		}
		else
			cout << "Такого пункта нет в меню" << endl;
	}
	system("pause");
}