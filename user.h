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
    vector<string> allUsers;//存授权ID，含当前用户***********
    vector<string> allAuthorizedUsers;
    vector<string> allAuthorizedUersPublicKey;  //所有用户目录文件

public:
    User();
    void currentUserInfo();
    string getUsername();
    PSID getSid();
    LPWSTR getStringSid();
    string getUserID();

    //还有一个获取授权用户的函数，询问是否授权，授权则加进去*************

    vector<string> getAllUsers();//返回所有授权用户，return allusers***********
    ~User();
};

