#pragma once
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

#include "main.h"
#include "user.h"
#include "global.h"

class MyKeyMgr : public KeyMgr
{
public:
	virtual int FireKeyList(KeyMgrKeyListEventParams* e)
	{
		printf("%-58s %-8s %-12s\n", e->UserId, e->KeyId, e->HasSecretKey ? "private" : "");
		return 0;
	}
};

class KeyManage
{
private:
	struct KeyGlobal {
		string pathString;
		string pathStringUser;
		string pathStringKey;
		string pathStringFile;
	}keyGlobal;
	struct KeyUser {
		string userID;
	}keyUser;
	
	MyKeyMgr keymgr;

public:
	~KeyManage();
	void init(Global global, User user);
	void GenerateKeyPairRSA(string userID, string pwd);
	void ExportPublicKey(string userID, string pwd);
	void ExportPrivateKey(string userID, string pwd);
	void KeyStoreListKeys(string pwd);


};
