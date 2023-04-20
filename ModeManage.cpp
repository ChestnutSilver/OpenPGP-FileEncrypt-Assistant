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
		cin >> mode;
		if (mode == "1")
		{
			WriteLine("原理展示");
			WriteLine("请任意输入想要加密的内容，以另起一行输入\":wq\"结束");
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


		//签名加密字符串
		FileManage fileManage;
		string after_string = fileManage.SignAndEncryptString(text, pwd, user.getUserID(), modeGlobal.pathStringKey);
		WriteLine("The string inputed by the keyboard is: ");
		WriteLine(text);
		WriteLine("Verify by your private key, and then encrypt by your public key, the result string is: ");
		WriteLine(after_string);

		//解密并验证签名
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
		WriteLine("未知错误。");
	}
}