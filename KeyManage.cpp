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
	WriteLine("生成用户密钥");
	WriteLine("------------");

	string keyFile = conbineStrings(keyGlobal.pathStringKey, "key-store");
	createDirectoryByString(keyFile);

	string keyringDir = keyFile;

	keymgr.LoadKeyring(keyringDir.c_str());
	keymgr.ListKeys();

/*
* 此方法将当前密钥环保存到磁盘。 有两个输出选项。密钥环可以保存到单个密钥文件，也可以保存到目录中。
* 将密钥环保存到设置为路径的目录。该目录必须已存在。
* 该类将在指定目录中创建一个“pubring.gpg”和“secring.gpg”文件。如果文件已存在，它们将被覆盖。
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

	// 新建或覆盖文件public-key-exported.asc，并导出公钥到文件，在filePublicKkey目录下
	keymgr.ExportPublicKey(filePublicKkey.c_str(), asciiArmored);


}

void KeyManage::ExportPrivateKey(string userID, string pwd)
{
	string filePrivateKkey = conbineStrings(keyGlobal.pathStringKey, "private-key-exported.asc");

	// should the exported files be ASCII or binary
	bool asciiArmored = true;

	// 新建或覆盖文件public-key-exported.asc，并导出公钥到文件，在filePublicKkey目录下
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