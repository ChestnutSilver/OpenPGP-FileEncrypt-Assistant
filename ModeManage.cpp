#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "D:/preopengpg/IPWorks OpenPGP 2022 C++ Edition/include/ipworksopenpgp.h"
#pragma comment(lib,"ipworksopenpgp22.lib")

#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;

#include "main.h"
#include "user.h"
#include "ModeManage.h"
#include "FileManage.h"
#include "global.h"

#include <sstream>

ModeManage::~ModeManage()
{

}

int ModeManage::modeInput(Global global, User user)
{
	modeGlobal.pathString = global.pathString;
	modeGlobal.pathStringFile = global.pathStringFile;
	modeGlobal.pathStringKey = global.pathStringKey;
	modeGlobal.pathStringUser = global.pathStringUser;

	while (true)
	{
		WriteLine("ģʽѡ��1->ԭ��չʾ��2->�洢�ļ���3->�����ļ�");
		string mode;
		cin >> mode;
		if (mode == "1")
		{
			WriteLine("ԭ��չʾ");
			WriteLine("������������Ҫ���ܵ����ݣ�������һ������\":wq\"����");
			return 1;
		}
		else if (mode == "2")
		{
			WriteLine("�ļ��洢");
			WriteLine("�洢�ļ��İ�ȫģʽ��1->���û���2->���û�");
			while (true)
			{
				string subMode;
				cin >> subMode;
				if (subMode == "1")
				{
					WriteLine("���û�ģʽ");
					WriteLine("�������ļ�·��");
					return 21;
				}
				else if (subMode == "2")
				{
					WriteLine("���û�ģʽ");

					//user.User_Authorization();

					WriteLine("�������ļ�·��");
					return 22;
				}
				else
				{
					WriteLine("δ֪���������������롣");
				}
			}
		}
		else if (mode == "3")
		{
			WriteLine("�ļ�����");
			WriteLine("�������ļ�·��(��׺Ϊ.gpg)");
			return 3;
		}
		else
		{
			WriteLine("δ֪���������������롣");
		}
	}
}

void ModeManage::modeControl(int mode, User user, string pwd)
{
	if (mode == 1)
	{
		string text = "";
		string input;
		getline(cin, input);
		string next;
		getline(cin, next);
		while (true)
		{
			if (next == ":wq")
			{
				text = text + input;
				break;
			}
			else
			{
				text = text + input + "\r\n";
			}
			input = next;
			getline(cin, next);
		}


		//ǩ�������ַ���
		FileManage fileManage;
		string after_string = fileManage.SignAndEncryptString(text, pwd, user.getUserID(), modeGlobal.pathStringKey);
		WriteLine("The string inputed by the keyboard is: ");
		WriteLine(text);
		WriteLine("Verify by your private key, and then encrypt by your public key, the result string is: ");
		WriteLine(after_string);

		//���ܲ���֤ǩ��
		fileManage.DecryptAndVerifyString(after_string, pwd, user.getUserID());


		WriteLine("--------------");
			
	}
	else if (mode == 21)
	{

	}
	else if (mode == 22)
	{

	}
	else if (mode == 3)
	{

	}
	else
	{
		WriteLine("δ֪����");
	}
}