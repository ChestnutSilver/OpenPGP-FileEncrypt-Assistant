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
    string username;		//用户名
    PSID sid;		//用户安全标识符
    LPWSTR stringSid;  //用户安全标识符，LPWSTR格式
    string userID;
    vector<string> allAuthorizedUsers;
    vector<string> allAuthorizedUersPublicKey;  //所有用户目录文件

public:
    User();
    void currentUserInfo();
    string getUsername();
    PSID getSid();
    LPWSTR getStringSid();
    string getUserID();
    ~User();
};

