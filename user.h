#ifndef USER_H
#define USER_H

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgp.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qipworksopenpgpkey.h"
#include "D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\qopenpgp.h"

#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib\\ipworksopenpgp22.lib")
#pragma comment(lib,"D:\\preopengpg\\IPWorks-OpenPGP-2022-C++-Edition-2\\lib64\\ipworksopenpgp22.lib")

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



#endif // USER_H

