#include <iostream>
#include "Chat.h"

void Chat::start() 
{
	isChatWork_ = true; // ���� ��� ������ �� ����	
}


void Chat::showLoginMenu() // ����������� ���������� ���� ��������� 
{
	currentUser_ = nullptr;	
	char i;

	do
	{
		cout << "" << endl;
		cout << "�������� �����, ��������������� ������" << endl;
		cout << "1 - �����������" << endl;
		cout << "2 - ����" << endl;
		cout << "0 - �����" << endl;
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
			cout << "����� ����������� ������, ��������� ���� �����" << endl;
			break;

		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu() // ���������� ���������� ���� ����, ����� ����������� ������������
{
	char i;
	cout << "������, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "1 - �������� ��������� " << endl;
		cout << "2 - ��������� ��������� " << endl;
		cout << "3 - �������� ����� ���������� ���� " << endl;
		cout << "0 - �����" << endl;;

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
			cout << "����� ����������� ������, ��������� ���� �����" << endl;
			break;
		}
	}
}

void Chat::showChat() const // ���������� ������������ ���������, ����������� ������������ ��� ����
{
	string who;
	string to;
	cout << "������ ���������" << endl;

	for (auto& mess : messages_)
	{
		// ���������� ���������: �� �������� ������������, ��� ���� � ��� ����
		if (currentUser_->getUserLogin() == mess.getWho() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			who = (currentUser_->getUserLogin() == mess.getWho()) ? "�" : getUserByLogin(mess.getWho())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(����(all))";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "�" : getUserByLogin(mess.getTo())->getUserName();
			}

			cout << "��������� ��: " << who << " ����: " << to << endl;
			cout << "�����: " << mess.getText() << endl;
		}
	}
	cout << "" << endl;
}

void Chat::addMessage() // �������� ���������
{
	string to, text;
	cout << "������� ��� ������������ - ���� ������ ��������, ��� ������� 'all' - ��� �������� ���� ����������: ";
	cin >> to;
	cout << "���������: ";
	cin.ignore();	// ������������ ����� ��������� ����������� �������
	getline(std::cin, text); // ���� ���������� ��������� � ���������

	if (!(to == "all" || getUserByName(to))) // ���� �� ������� ����� ���������� �� �����
	{
		cout << "������������ � ����� ������ �� ������ " << to << endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}

void Chat::showAllUsersName() const //�������� ����� ���������������� �������������
{
	cout << "����� ���������� ���� " << endl;
	for (auto& user : users_)
	{
		cout << " " << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
		{
			cout << "(�)";
			cout << endl;
		}
	}
	cout << "" << endl;
}


void Chat::login() // ����������� � ��� �� ��� ���������� ������ � ������
{
	string login;
	string password;
	char i;

	do
	{
		cout << "�����: ";
		cin >> login;
		cout << "������: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			cout << "������ �����" << endl;
			cout << "������� '0' ����� ����� ��� ������ ������ ����� ��������� ����: ";
			cin >> i;

			if (i == '0')
				break;
		}
	} while (!currentUser_);
}


void Chat::signUp() // ����������� ������������ � ����
{
	string login, password, name;

	cout << "�����: ";
	cin >> login;
	cout << "������: ";
	cin >> password;
	cout << "��� ������������: ";
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
	for (auto& user : users_) // ���� �������� �� ����� ������� �������������
	{
		if (login == user.getUserLogin()) // �������� ���������� ������
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