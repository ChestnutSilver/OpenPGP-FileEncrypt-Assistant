/**
 * Filename: ISP-03
 * Author: 2053182 王润霖，2052338 鲍宇轩
 * Date: 2023.04.20
 * Version: 1.4
 * Description: Proj 03--OpenPGP File Encryption
 * References:
 */

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

#include "user.h"
#include "global.h"
#include "KeyManage.h"
#include "ModeManage.h"
#include "sddl.h"
#include <sstream>

//typedef string SecurityIdentifier;

//用来打印信息的函数，方便不同环境下的修改
void WriteLine(string console)
{
	cout << console << endl;
}

//wchar_t变量转换为szDst
string WcharToString(wchar_t wText[])
{
    std::string szDst;
    DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
    char* psText;
    psText = new char[dwNum];
    WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
    szDst = psText;
    delete[]psText;

    return szDst;
}


int main()
{
    //展示文件夹创建
    Global global;

    //用户创建
    User user;
    string userID = user.getUserID();

    //密钥生成和导出

    KeyManage keyManage; 
    keyManage.init(global, user);

    //密码唯一，且由用户的用户名和安全序列号唯一生成
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    keyManage.ExportPrivateKey(userID, pwd);//私钥敏感信息不能导出
    keyManage.KeyStoreListKeys(pwd);

    //模式选择：原理展示/存储模式/调阅模式
    //用户界面
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(global, user);
        modeManage.modeControl(Mode, user, pwd);
        WriteLine("程序已结束，按q退出，按其他任意键返回用户界面...");
        string quit;
        cin >> quit;
        if (quit == "q")
            break;
    }

	return 0;
}