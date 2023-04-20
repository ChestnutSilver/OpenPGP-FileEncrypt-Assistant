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
#include "global.h"
#include "FileManage.h"
#include "KeyManage.h"

FileManage::~FileManage()
{

}

string FileManage::SignAndEncryptString(string plainText, string pwd, string userID, string keyringDir)
{
	OpenPGP pgp;
	string filePublicKey = conbineStrings(keyringDir, "public-key-exported.asc");
	string filePrivateKey = conbineStrings(keyringDir, "private-key-exported.asc");

	KeyManage keyManage;
	keyManage.ExportPrivateKey(userID.c_str(), pwd.c_str()); //µ¼³öË½Ô¿

	// sign and encrypt

    pgp.SetASCIIArmor(true);
    pgp.SetKeyCount(1);
    pgp.SetKeyKeyring(0, keyringDir.c_str());
    pgp.SetKeyUserId(0, userID.c_str());
    pgp.SetKeyPassphrase(0, pwd.c_str());
    pgp.SetRecipientKeyCount(1);
    pgp.SetRecipientKeyKeyring(0, keyringDir.c_str());
    pgp.SetRecipientKeyUserId(0, userID.c_str());

    int ret_code = pgp.SignAndEncrypt();
    if (ret_code == 0)
        WriteLine("Sign and encrypt a string successfully!");

    int len;
    char *output;
    pgp.GetOutputMessage(output, len);

    printf("%s\n", output);

    string encryptedAndSignedString = output;

	return encryptedAndSignedString;
}

void FileManage::DecryptAndVerifyString(string signedAndEncryptedMessage, string pwd, string userID)
{

}