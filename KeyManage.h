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

class KeyManage
{
public:
	~KeyManage();
	void GenerateKeyPairRSA(string userID, string pwd);
	void ExportPublicKey(string userID, string pwd);
	void ExportPrivateKey(string userID, string pwd);
	void KeyStoreListKeys(string pwd);


};
