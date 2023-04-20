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
* 此C++代码使用Windows API检索当前用户的安全标识符（SID），然后使用LookupAccountSid（）获取与该SID关联的用户名和域名，然后将其打印到控制台。
*
* 在C++代码中，szUserName和szDomainName是字符数组，用于存储LookupAccountSid（）函数检索到的用户名和域名。
* 调用LookupAccountSid（）时，函数会将检索到的用户名和域名分别写入szUserName和szDomainName提供的缓冲区。缓冲区的大小分别作为dwUserNameSize和dwDomainNameSize传入。
* 调用LookupAccountSid（）后，szUserName和szDomainName缓冲区用于使用printf（）将当前用户名以“domain\\username”格式打印到控制台。
*
* 在这个修改后的代码中，我们将szUserName和szDomainName的类型更改为wchar_t，这是Windows API函数使用的宽字符类型。
* 我们还将两个缓冲区的大小计算更改为wchar_t，而不是char。
* 最后，我们使用wprintf（）将当前用户名打印到控制台，使用%s格式说明符和宽字符串szDomainName和szUserName。
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
                            //wmic useraccount get name, sid 指令可在cmd窗口查看本机各用户的sid
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


