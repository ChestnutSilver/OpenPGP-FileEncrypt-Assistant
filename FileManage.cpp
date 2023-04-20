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

FileManage::~FileManage()
{

}

string FileManage::SignAndEncryptString(string plainText, string pwd, string userID, Global global)
{
	//PGPLib pgp = new PGPLib();
	string filePublicKey = conbineStrings(global.pathStringKey, "public_key_exported.asc");
	string filePrivateKey = conbineStrings(global.pathStringKey, "private_key_exported.asc");


	return "a";
}