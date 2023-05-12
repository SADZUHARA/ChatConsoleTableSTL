#include <iostream>
#include "Chat.h"

void Chat::start() 
{
	isChatWork_ = true; // Флаг для выхода из меню	
}


void Chat::showLoginMenu() // Отображение стартового меню программы 
{
	currentUser_ = nullptr;	
	char i;

	do
	{
		cout << "" << endl;
		cout << "Выберите цифру, соответствующей опцией" << endl;
		cout << "1 - Регистрация" << endl;
		cout << "2 - Вход" << endl;
		cout << "0 - Выход" << endl;
		cin >> i;

		switch (i)
		{
		case '1':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case '2':
			login();
			break;

		case '0':
			isChatWork_ = false;
			break;
		default:
			cout << "Введён некоректный символ, повторите ввод снова" << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // отображает внутреннее меню чата, после авторизации пользователя
{
	char i;
	cout << "Привет, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "1 - Показать сообщения " << endl;
		cout << "2 - Отправить сообщение " << endl;
		cout << "3 - Показать имена участников чата " << endl;
		cout << "0 - Выход" << endl;;

		cout << endl
			<< ">> ";
		cin >> i;

		switch (i)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsersName();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "Введён некоректный символ, повторите ввод снова" << endl;
			break;
		}
	}
}

void Chat::showChat() const // показывает отправленные сообщения, конкретному пользователю или всем
{
	string who;
	string to;
	cout << "Список сообщений" << endl;

	for (auto& mess : messages_)
	{
		// Показывает сообщение: от текущего пользователя, для него и для всех
		if (currentUser_->getUserLogin() == mess.getWho() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			who = (currentUser_->getUserLogin() == mess.getWho()) ? "Я" : getUserByLogin(mess.getWho())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(Всем(all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "Я" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "Сообщение от: " << who << " Кому: " << to << endl;
			cout << "Текст: " << mess.getText() << endl;
		}
	}
	cout << "" << endl;
}

void Chat::addMessage() // Создание сообщения
{
	string to, text;
	cout << "Введите имя пользователя - кому хотите написать, или команду 'all' - для отправки всем участникам: ";
	cin >> to;
	cout << "Сообщение: ";
	cin.ignore();	// игнорировать любые введенные посторонние символы
	getline(std::cin, text); // ввод текстового сообщения с пробелами

	if (!(to == "all" || getUserByName(to))) // если не удалось найти получателя по имени
	{
		cout << "Пользователь с таким именем не найден " << to << endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

void Chat::showAllUsersName() const //Показать имена зарегистрированы пользователей
{
	cout << "Имена участников чата " << endl;
	for (auto& user : users_)
	{
		cout << " " << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
		{
			cout << "(Я)";
			cout << endl;
		}
	}
	cout << "" << endl;
}


void Chat::login() // Авторизация в чат по уже созданному логину и паролю
{
	string login;
	string password;
	char i;

	do
	{
		cout << "Логин: ";
		cin >> login;
		cout << "Пароль: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			cout << "Ошибка входа" << endl;
			cout << "Нажмите '0' чтобы выйти или другую кнопку чтобы повторить вход: ";
			cin >> i;

			if (i == '0')
				break;
		}
	} while (!currentUser_);
}


void Chat::signUp() // Регистрация пользователя в чате
{
	string login, password, name;

	cout << "Логин: ";
	cin >> login;
	cout << "Пароль: ";
	cin >> password;
	cout << "Имя пользователя: ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);

}


std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : users_) // цикл проходит по всему массиву пользователей
	{
		if (login == user.getUserLogin()) // проверка совпадения логина
		return std::make_shared<User>(user); 
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getUserName())
		return std::make_shared<User>(user); 
	}
	return nullptr;
}