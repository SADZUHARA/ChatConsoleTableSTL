#include "Chat.h"
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	
	cout << "Программа консольный чат." << endl;
	cout <<	"Для продолжения выберите соответсвующий вариант." << endl;

	Chat chat;		//Создаём класс Чат
	chat.start();	//Начало работы
	
	while (chat.isChatWork())	//Цикл работы чата
	{ 
		chat.showLoginMenu(); //Меню регистрации 

		while (chat.getCurrentUser()) 
		{
			chat.showUserMenu(); //Меню пользователя 
		}
	}

	return 0;
}