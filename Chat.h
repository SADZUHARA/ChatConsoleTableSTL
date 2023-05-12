#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
using namespace std;

struct UserLoginExp : public std::exception	//»сключени€
{
	const char* what() const noexcept override { return "ошибка: логин пользовател€ зан€т"; } 
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "ошибка: им€ пользовател€ зан€то"; }
};


class Chat
{
public:
	void start();	// запуск чата
	bool isChatWork() const { return isChatWork_; } // проверка, работает чат или нет (если true - чат работает, если false - нет) 
	void showLoginMenu(); // ќтображение стартового меню программы
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showUserMenu(); // отображает внутреннее меню чата, после авторизации пользовател€
	

private:
	bool isChatWork_ = false; // ‘лаг дл€ выхода из меню 
	void login();	// јвторизаци€ в чат по созданному логину и паролю
	void signUp();	// –егистраци€ пользовател€ в чате 
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;
	std::shared_ptr<User> currentUser_ = nullptr; // показывает текущего пользовател€
	std::vector<User> users_;	// ƒинамический массив (вектор) текущих пользователей 
	std::vector<Message> messages_; // ƒинамический массив (вектор) сообщений
	void showChat() const; // показывает отправленные сообщени€, конкретному пользователю или всем
	void showAllUsersName() const;	// ѕоказывает имена пользователей чата
	void addMessage(); //—оздание сообщени€
	
};