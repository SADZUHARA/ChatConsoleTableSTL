#include "Chat.h"
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	
	cout << "��������� ���������� ���." << endl;
	cout <<	"��� ����������� �������� �������������� �������." << endl;

	Chat chat;		//������ ����� ���
	chat.start();	//������ ������
	
	while (chat.isChatWork())	//���� ������ ����
	{ 
		chat.showLoginMenu(); //���� ����������� 

		while (chat.getCurrentUser()) 
		{
			chat.showUserMenu(); //���� ������������ 
		}
	}

	return 0;
}