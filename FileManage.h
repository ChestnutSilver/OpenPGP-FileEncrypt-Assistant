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
#include "KeyManage.h"

class FileManage
{
public:
	~FileManage();
	string SignAndEncryptString(string plainText, string pwd, string userID, string keyringDir);
	void DecryptAndVerifyString(string signedAndEncryptedMessage, string pwd, string userID);

};