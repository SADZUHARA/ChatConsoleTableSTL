#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
#include "User.h"
using namespace std;

struct UserLoginExp : public std::exception	//����������
{
	const char* what() const noexcept override { return "������: ����� ������������ �����"; } 
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "������: ��� ������������ ������"; }
};


class Chat
{
public:
	void start();	// ������ ����
	bool isChatWork() const { return isChatWork_; } // ��������, �������� ��� ��� ��� (���� true - ��� ��������, ���� false - ���) 
	void showLoginMenu(); // ����������� ���������� ���� ���������
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showUserMenu(); // ���������� ���������� ���� ����, ����� ����������� ������������
	

private:
	bool isChatWork_ = false; // ���� ��� ������ �� ���� 
	void login();	// ����������� � ��� �� ���������� ������ � ������
	void signUp();	// ����������� ������������ � ���� 
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;
	std::shared_ptr<User> currentUser_ = nullptr; // ���������� �������� ������������
	std::vector<User> users_;	// ������������ ������ (������) ������� ������������� 
	std::vector<Message> messages_; // ������������ ������ (������) ���������
	void showChat() const; // ���������� ������������ ���������, ����������� ������������ ��� ����
	void showAllUsersName() const;	// ���������� ����� ������������� ����
	void addMessage(); //�������� ���������
	
};