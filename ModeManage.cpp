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
		WriteLine("模式选择：1->原理展示，2->存储文件，3->调阅文件");
		string mode;
		getline(cin, mode);
		if (mode == "1")
		{
			WriteLine("原理展示");
			return 1;
		}
		else if (mode == "2")
		{
			WriteLine("文件存储");
			WriteLine("存储文件的安全模式：1->单用户，2->多用户");
			while (true)
			{
				string subMode;
				cin >> subMode;
				if (subMode == "1")
				{
					WriteLine("单用户模式");
					WriteLine("请输入文件路径");
					return 21;
				}
				else if (subMode == "2")
				{
					WriteLine("多用户模式");

					//user.User_Authorization();

					WriteLine("请输入文件路径");
					return 22;
				}
				else
				{
					WriteLine("未知参数，请重新输入。");
				}
			}
		}
		else if (mode == "3")
		{
			WriteLine("文件调阅");
			WriteLine("请输入文件路径(后缀为.gpg)");
			return 3;
		}
		else
		{
			WriteLine("未知参数，请重新输入。");
		}
	}
}

void ModeManage::modeControl(int mode, User user, string pwd)
{
	if (mode == 1)
	{
		//签名加密字符串
		FileManage fileManage;
		fileManage.SignAndEncryptString(pwd, user.getUserID(), modeGlobal.pathStringKey);

		//解密并验证签名
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
					WriteLine(("文件存储成功，并由用户 " + user.getUsername() + " 签名。"));
					WriteLine(("签名的加密文件，存储在: "));
					WriteLine(outputFile);

					WriteLine("Success 2-1: 单用户模式下，用户能够对文件加密并存储，并通过签名真实性认证，并且能够解密文件！");
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
				WriteLine("文件不存在，请重新输入文件路径");
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
					WriteLine(("文件存储成功，并由用户 " + user.getUsername() + " 签名。"));
					WriteLine(("签名的加密文件，存储在: "));
					WriteLine(outputFile);

					WriteLine("Success 2-2: 多用户模式下，A用户能够对文件加密、签名并存储，并且B用户能够进行真实性认证，并解密文件！");
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
				WriteLine("文件不存在，请重新输入文件路径");
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
			WriteLine("Success 3: 单用户与多用户模式下，A、B用户能够解密自己拥有调阅权限的文件！");
		}
	}
	else
	{
		WriteLine("未知错误。");
	}
}