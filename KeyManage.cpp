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
#include "global.h"


KeyManage::~KeyManage()
{

}

void KeyManage::init(Global global, User user)
{
	keyGlobal = global;
	keyUser = user;
}


void KeyManage::GenerateKeyPairRSA(string userID, string pwd)
{
	WriteLine("�����û���Կ");
	WriteLine("------------");

	string keyFile = conbineStrings(keyGlobal.pathStringKey, "key-store");
	createDirectoryByString(keyFile);

	string keyringDir = keyFile;

	keymgr.LoadKeyring(keyringDir.c_str());
	keymgr.ListKeys();

/*
* �˷�������ǰ��Կ�����浽���̡� ���������ѡ���Կ�����Ա��浽������Կ�ļ���Ҳ���Ա��浽Ŀ¼�С�
* ����Կ�����浽����Ϊ·����Ŀ¼����Ŀ¼�����Ѵ��ڡ�
* ���ཫ��ָ��Ŀ¼�д���һ����pubring.gpg���͡�secring.gpg���ļ�������ļ��Ѵ��ڣ����ǽ������ǡ�
* KeyringPath.
*/
	int ret_code = keymgr.CreateKey(userID.c_str(), pwd.c_str());

	if (ret_code == 0)
		cout << "Key has been generated! The UserID is: " << userID << ", The pwd is: " << pwd << endl;

	int save_code = keymgr.SaveKeyring(keyringDir.c_str());
	if (save_code == 0)
		cout << "Key has been saved at: " << keyringDir << endl;


}

void KeyManage::ExportPublicKey(string userID, string pwd)
{
	string filePublicKkey = conbineStrings(keyGlobal.pathStringKey, "public-key-exported.asc");

	// should the exported files be ASCII or binary
	bool asciiArmored = true;

	// �½��򸲸��ļ�public-key-exported.asc����������Կ���ļ�����filePublicKkeyĿ¼��
	keymgr.ExportPublicKey(filePublicKkey.c_str(), asciiArmored);


}

void KeyManage::ExportPrivateKey(string userID, string pwd)
{
	string filePrivateKkey = conbineStrings(keyGlobal.pathStringKey, "private-key-exported.asc");

	// should the exported files be ASCII or binary
	bool asciiArmored = true;

	// �½��򸲸��ļ�public-key-exported.asc����������Կ���ļ�����filePublicKkeyĿ¼��
	keymgr.ExportSecretKey(filePrivateKkey.c_str(), asciiArmored);


}

void KeyManage::KeyStoreListKeys(string pwd)
{
	string keyFile = conbineStrings(keyGlobal.pathStringKey, "key-store");
	string keyringDir = keyFile;

	WriteLine("Listing Keys...");
	WriteLine("User Id------Key Id------Private Key");

	keymgr.LoadKeyring(keyringDir.c_str());
	keymgr.ListKeys();

}