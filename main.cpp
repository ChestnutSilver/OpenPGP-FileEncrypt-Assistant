/**
 * Filename: ISP-03
 * Author: 2053182 �����أ�2052338 ������
 * Date: 2023.04.19
 * Version: 1.3
 * Description: Proj 03--OpenPGP File Encryption
 * References:
 */

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

#include "user.h"
#include "global.h"
#include "KeyManage.h"
#include "ModeManage.h"
#include "sddl.h"
#include <sstream>

//typedef string SecurityIdentifier;

//������ӡ��Ϣ�ĺ��������㲻ͬ�����µ��޸�
void WriteLine(string console)
{
	cout << console << endl;
}

//wchar_t����ת��ΪszDst
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
    //չʾ�ļ��д���
    Global global;

    //�û�����
    User user;
    string userID = user.getUserID();

    //��Կ���ɺ͵���
    KeyManage keyManage;
    //����Ψһ�������û����û����Ͱ�ȫ���к�Ψһ����
    string pwd = ToString(hash<string>{}(user.getUsername()) ^ hash<PVOID>{}(user.getStringSid()));

    keyManage.GenerateKeyPairRSA(userID, pwd);
    keyManage.ExportPublicKey(userID, pwd);
    //keyManage.ExportPrivateKey(userID, passwd);//˽Կ������Ϣ���ܵ���
    keyManage.KeyStoreListKeys(pwd);

    //ģʽѡ��ԭ��չʾ/�洢ģʽ/����ģʽ
    //�û�����
    while (true)
    {
        ModeManage modeManage;
        int Mode = modeManage.modeInput(user);
        modeManage.modeControl(Mode, user, pwd);
        WriteLine("�����ѽ�������q�˳�������������������û�����...");
        string quit;
        cin >> quit;
        if (quit == "q")
            break;
    }

	return 0;
}