#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ipworksopenpgp.h>
#pragma comment(lib,"ipworksopenpgp22.lib")

#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;

#include <functional>
#include "main.h"
#include "user.h"

User::User()
{
    //GetUserName();
/*
* ��C++����ʹ��Windows API������ǰ�û��İ�ȫ��ʶ����SID����Ȼ��ʹ��LookupAccountSid������ȡ���SID�������û�����������Ȼ�����ӡ������̨��
*
* ��C++�����У�szUserName��szDomainName���ַ����飬���ڴ洢LookupAccountSid�����������������û�����������
* ����LookupAccountSid����ʱ�������Ὣ���������û����������ֱ�д��szUserName��szDomainName�ṩ�Ļ��������������Ĵ�С�ֱ���ΪdwUserNameSize��dwDomainNameSize���롣
* ����LookupAccountSid������szUserName��szDomainName����������ʹ��printf��������ǰ�û����ԡ�domain\\username����ʽ��ӡ������̨��
*
* ������޸ĺ�Ĵ����У����ǽ�szUserName��szDomainName�����͸���Ϊwchar_t������Windows API����ʹ�õĿ��ַ����͡�
* ���ǻ��������������Ĵ�С�������Ϊwchar_t��������char��
* �������ʹ��wprintf��������ǰ�û�����ӡ������̨��ʹ��%s��ʽ˵�����Ϳ��ַ���szDomainName��szUserName��
*/
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
                        wprintf(L"Current user: %s\\%s\n", szDomainName, szUserName);
                        //printf("Current user: %s\\%s\n", szDomainName, szUserName);

                        username = WcharToString(szUserName);
                        sid = pSid;
                        if (!ConvertSidToStringSidW(sid, &stringSid))
                        {
                            //wmic useraccount get name, sid ָ�����cmd���ڲ鿴�������û���sid
                            std::cout << "Failed to convert to string: error code " << GetLastError() << std::endl;
                            FreeSid(sid);
                            return;
                        }
                        userID = ToString(hash<LPWSTR>{}(stringSid));

                        currentUserInfo();
                    }
                }
                GlobalFree(pTokenUser);
            }
        }
        CloseHandle(hToken);
    }
}

void User::currentUserInfo()
{
    WriteLine("Current User: ");
    WriteLine(username);
    cout << sid << endl;
    std::wcout << stringSid << std::endl;

    WriteLine(userID);
}

string User::getUsername()
{
    return username;
}

PSID User::getSid()
{
    return sid;
}

LPWSTR User::getStringSid()
{
    return stringSid;
}

string User::getUserID()
{
    return userID;
}

User::~User()
{

}


