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
* �ڴ����У�����ʹ����MultiByteToWideChar��������·��������std::string����ת��ΪLPCWSTR���͡�
* �ú����������������Դ����ҳ��������CP_ACP����ʾʹ�õ�ǰϵͳ��ANSI����ҳ������־��������0����
* 					Դ�ַ�����ָ�롢Դ�ַ����ĳ��ȣ�����ʹ��-1��ʾ�Զ����㣩��Ŀ�껺������ָ���Ŀ�껺�����Ĵ�С��
* ����ʹ��vector������һ���㹻��Ļ������������䴫�ݸ�MultiByteToWideChar������
* �������ʹ��buffer.data()��������ָ��ת��ΪLPCWSTR���ͣ������䴫�ݸ�CreateDirectory������

* ��Ҫע����ǣ��������·��������ANSI�ַ�������Ҫʹ�ò�ͬ�Ĵ���ҳ��ͬ��ת����������ת����
* ����������£��������Windows API�ĵ���������ϣ����˽���ȷ��ת����ʽ��
* 
* �ڴ����У�����ʹ����CreateDirectory�����ķ���ֵ���ж�Ŀ¼�Ƿ��Ѵ��ڡ�
* ���CreateDirectory��������0������������Ƿ�ΪERROR_ALREADY_EXISTS��ERROR_PATH_NOT_FOUND��
* ���������ΪERROR_ALREADY_EXISTS����˵��Ŀ¼�Ѿ����ڣ����Ǽ���������һ��Ŀ¼��
* ���������ΪERROR_PATH_NOT_FOUND����˵��Ŀ¼�����ڣ������ȴ�����Ŀ¼��Ȼ�����������һ��Ŀ¼��
* ���CreateDirectory�����ɹ����أ���Ŀ¼·�����������̨������·���������һ��·���ָ����Ա�����һ��Ŀ¼�Ĵ�����

* ������ʱû�д�������·��Ϊ���ַ�����ֻ����·���ָ���������������ں��������Ӧ�Ĵ�������롣
*/
	std::string delimiter = "\\";  // ����·���ָ���
	size_t pos = 0;
	std::string token;
	std::vector<std::string> directories;

	while ((pos = path.find(delimiter)) != std::string::npos) 
	{  // ʹ��·���ָ������зָ�
		token = path.substr(0, pos);
		directories.push_back(token);
		path.erase(0, pos + delimiter.length());
	}
	directories.push_back(path);  // �����һ��Ŀ¼��ӵ�������

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
			{  // Ŀ¼�Ѵ��ڣ�����������һ��Ŀ¼
				std::wcout << L"Directory already exists: " << buffer.data() << L"\n";
			}
			else if (error_code == ERROR_PATH_NOT_FOUND) 
			{  // Ŀ¼�����ڣ�����Ŀ¼������������һ��Ŀ¼
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
	WriteLine("OpenPGP�ļ�����ϵͳ");
	WriteLine("");

	set_baseName();

	WriteLine("Ӧ�����������ļ�����Ϣ��");
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
	WriteLine("��������Ŀ�ļ��еĴ��λ�ã�Ĭ�ϣ�D:\\������q��������������Ŀ¼�����1��б�ָܷ���");
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