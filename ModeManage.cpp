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
		getline(cin, mode);
		if (mode == "1")
		{
			WriteLine("ԭ��չʾ");
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
		//ǩ�������ַ���
		FileManage fileManage;
		fileManage.SignAndEncryptString(pwd, user.getUserID(), modeGlobal.pathStringKey);

		//���ܲ���֤ǩ��
		//fileManage.DecryptAndVerifyString("a", pwd, user.getUserID());

		WriteLine("--------------");
			
	}
	else if (mode == 21)
	{
		string filePath;
		getline(cin, filePath);
		while (true)
		{
			if (!_access(filePath.c_str(), 0))
			{
				FileManage fileManage;
				string outputFile = fileManage.SignAndEncryptSingle(pwd, filePath, user.getUserID(), modeGlobal.pathStringFile, modeGlobal.pathStringKey);
				bool check = fileManage.VerifySingle(fileManage.modeUserIDPwd.modePwd, outputFile, fileManage.modeUserIDPwd.modeUserID, modeGlobal.pathStringFile, modeGlobal.pathStringKey);
				//bool check = fileManage.VerifySingle(pwd, outputFile, user.getUserID(), modeGlobal.pathStringFile, modeGlobal.pathStringKey);
				if (check)
				{
					WriteLine(("�ļ��洢�ɹ��������û� " + user.getUsername() + " ǩ����"));
					WriteLine(("ǩ���ļ����ļ����洢��: "));
					WriteLine(outputFile);

					WriteLine("Success 2-1: ���û�ģʽ�£��û��ܹ����ļ����ܲ��洢����ͨ��ǩ����ʵ����֤�������ܹ������ļ���");
				}
				else
				{
					//cleardeletfile outputfile
					WriteLine("21-test-exp2");
				}
				WriteLine("--------------");
				break;
			}
			else
			{
				WriteLine("�ļ������ڣ������������ļ�·��");
				getline(cin, filePath);
			}
		}
	}
	else if (mode == 22)
	{
		string filePath;
		getline(cin, filePath);
		while (true)
		{
			if (!_access(filePath.c_str(), 0))
			{
				FileManage fileManage;
				string outputFile = fileManage.SignAndEncryptMultiple(pwd, filePath, user.getUserID(), modeGlobal.pathStringFile, modeGlobal.pathStringKey);
				bool check = fileManage.Verify(fileManage.modeUserIDPwd.modePwd, outputFile, fileManage.modeUserIDPwd.modeUserID, modeGlobal.pathStringFile, modeGlobal.pathStringKey);
				if (check)
				{
					WriteLine(("�ļ��洢�ɹ��������û� " + user.getUsername() + " ǩ����"));
					WriteLine(("ǩ���ļ����ļ����洢��: "));
					WriteLine(outputFile);

					WriteLine("Success 2-2: ���û�ģʽ�£�A�û��ܹ����ļ����ܡ�ǩ�����洢������B�û��ܹ�������ʵ����֤���������ļ���");
				}
				else
				{
					//cleardeletfile outputfile
					WriteLine("21-test-exp2");
				}
				WriteLine("--------------");
				break;
			}
			else
			{
				WriteLine("�ļ������ڣ������������ļ�·��");
				getline(cin, filePath);
			}
		}
	}
	else if (mode == 3)
	{
		FileManage fileManage;
		string outputFile;
		getline(cin, outputFile);
		bool check = fileManage.Verify(fileManage.modeUserIDPwd.modePwd, outputFile, fileManage.modeUserIDPwd.modeUserID, modeGlobal.pathStringFile, modeGlobal.pathStringKey);

		if (check)
		{
			WriteLine("Success 3: ���û�����û�ģʽ�£�A��B�û��ܹ������Լ�ӵ�е���Ȩ�޵��ļ���");
		}
	}
	else
	{
		WriteLine("δ֪����");
	}
}