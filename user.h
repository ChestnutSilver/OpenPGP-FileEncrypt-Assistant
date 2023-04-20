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

#include <sstream>
#include "sddl.h"
#include "main.h"

template <typename T>
string ToString(T value) 
{
    stringstream os;
    os << value;
    return os.str();
}


class User
{
private:
    string username;		//�û���
    PSID sid;		//�û���ȫ��ʶ��
    LPWSTR stringSid;  //�û���ȫ��ʶ����LPWSTR��ʽ
    string userID;
    vector<string> allUsers;//����ȨID������ǰ�û�***********
    vector<string> allAuthorizedUsers;
    vector<string> allAuthorizedUersPublicKey;  //�����û�Ŀ¼�ļ�

public:
    User();
    void currentUserInfo();
    string getUsername();
    PSID getSid();
    LPWSTR getStringSid();
    string getUserID();

    //����һ����ȡ��Ȩ�û��ĺ�����ѯ���Ƿ���Ȩ����Ȩ��ӽ�ȥ*************

    vector<string> getAllUsers();//����������Ȩ�û���return allusers***********
    ~User();
};

