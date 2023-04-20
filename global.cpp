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
#include "global.h"

#include <sstream>

string conbineStrings(string left, string right)
{
	std::stringstream ss;
	ss << left << "\\" << right;
	return ss.str();
}

string globalGetUserName()
{
	string username;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		DWORD dwLengthNeeded;
		if (!GetTokenInformation(hToken, TokenUser, NULL, 0, &dwLengthNeeded) && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			PTOKEN_USER pTokenUser = (PTOKEN_USER)GlobalAlloc(GPTR, dwLengthNeeded);
			if (pTokenUser != NULL)
			{
				if (GetTokenInformation(hToken, TokenUser, pTokenUser, dwLengthNeeded, &dwLengthNeeded))
				{
					SID_NAME_USE sidNameUse;

					wchar_t szUserName[256];
					DWORD dwUserNameSize = sizeof(szUserName);
					wchar_t szDomainName[256];

					DWORD dwDomainNameSize = sizeof(szDomainName);
					PSID pSid = pTokenUser->User.Sid;
					if (LookupAccountSid(NULL, pSid, szUserName, &dwUserNameSize, szDomainName, &dwDomainNameSize, &sidNameUse))
					{
						//wprintf(L"Current user: %s\\%s\n", szDomainName, szUserName);
						//printf("Current user: %s\\%s\n", szDomainName, szUserName);

						username = WcharToString(szUserName);
					}
				}
				GlobalFree(pTokenUser);
			}
		}
		CloseHandle(hToken);
	}
	return username;
}

int createDirectoryByString(string path)
{
/*
* 在代码中，我们使用了MultiByteToWideChar函数来将路径参数从std::string类型转换为LPCWSTR类型。
* 该函数接受五个参数：源代码页（这里是CP_ACP，表示使用当前系统的ANSI代码页）、标志（这里是0）、
* 					源字符串的指针、源字符串的长度（这里使用-1表示自动计算）、目标缓冲区的指针和目标缓冲区的大小。
* 我们使用vector来创建一个足够大的缓冲区，并将其传递给MultiByteToWideChar函数。
* 最后，我们使用buffer.data()将缓冲区指针转换为LPCWSTR类型，并将其传递给CreateDirectory函数。

* 需要注意的是，如果您的路径包含非ANSI字符，则需要使用不同的代码页或不同的转换函数进行转换。
* 在这种情况下，建议查阅Windows API文档或相关资料，以了解正确的转换方式。
* 
* 在代码中，我们使用了CreateDirectory函数的返回值来判断目录是否已存在。
* 如果CreateDirectory函数返回0，则检查错误码是否为ERROR_ALREADY_EXISTS或ERROR_PATH_NOT_FOUND。
* 如果错误码为ERROR_ALREADY_EXISTS，则说明目录已经存在，我们继续创建下一级目录。
* 如果错误码为ERROR_PATH_NOT_FOUND，则说明目录不存在，我们先创建该目录，然后继续创建下一级目录。
* 如果CreateDirectory函数成功返回，则将目录路径输出到控制台，并将路径后面添加一个路径分隔符以便于下一级目录的创建。

* 代码暂时没有处理输入路径为空字符串或只包含路径分隔符的情况，可以在后面添加相应的错误处理代码。
*/
	std::string delimiter = "\\";  // 定义路径分隔符
	size_t pos = 0;
	std::string token;
	std::vector<std::string> directories;

	while ((pos = path.find(delimiter)) != std::string::npos) 
	{  // 使用路径分隔符进行分割
		token = path.substr(0, pos);
		directories.push_back(token);
		path.erase(0, pos + delimiter.length());
	}
	directories.push_back(path);  // 将最后一个目录添加到向量中

	std::string current_directory;
	for (const auto& directory : directories) 
	{
		current_directory += directory;
		std::vector<wchar_t> buffer(current_directory.size() + 1);
		MultiByteToWideChar(CP_ACP, 0, current_directory.c_str(), -1, buffer.data(), static_cast<int>(buffer.size()));

		if (CreateDirectory(buffer.data(), NULL) == 0) 
		{
			DWORD error_code = GetLastError();
			if (error_code == ERROR_ALREADY_EXISTS) 
			{  // 目录已存在，继续创建下一级目录
				std::wcout << L"Directory already exists: " << buffer.data() << L"\n";
			}
			else if (error_code == ERROR_PATH_NOT_FOUND) 
			{  // 目录不存在，创建目录并继续创建下一级目录
				if (CreateDirectory(buffer.data(), NULL) == 0) 
				{
					std::cout << "Failed to create directory!\n";
					return 1;
				}
				std::wcout << L"Directory created successfully: " << buffer.data() << L"\n";
			}
			else 
			{
				std::cout << "Failed to create directory!\n";
				return 1;
			}
		}
		else 
		{
			std::wcout << L"Directory created successfully: " << buffer.data() << L"\n";
		}
		current_directory += "\\";
	}
}


Global::Global()
{
	WriteLine("");
	WriteLine("OpenPGP文件管理系统");
	WriteLine("");

	set_baseName();

	WriteLine("应用所创建的文件夹信息：");
	WriteLine(pathString);
	WriteLine(pathStringUser);
	WriteLine(pathStringKey);
	WriteLine(pathStringFile);

	createDirectoryByString(pathString);
	createDirectoryByString(pathStringUser);
	createDirectoryByString(pathStringKey);
	createDirectoryByString(pathStringFile);
}

void Global::set_baseName()
{
	WriteLine("请输入项目文件夹的存放位置，默认：D:\\，输入q可跳过。（各级目录间各用1个斜杠分隔）");
	string basename;
	getline(cin, basename);

	if (basename != "q")
	{
		baseName = basename;
	}
	else
	{
		baseName = "D:";
	}

	pathString = conbineStrings(baseName, folderName);
	pathStringUser = conbineStrings(pathString, globalGetUserName());
	pathStringKey = conbineStrings(pathStringUser, folderName1);
	pathStringFile = conbineStrings(pathStringUser, folderName2);


}

Global::~Global()
{

}