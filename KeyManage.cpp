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


KeyManage::~KeyManage()
{

}

void KeyManage::GenerateKeyPairRSA(string userID, string pwd)
{
	WriteLine("生成用户密钥");
	WriteLine("------------");



}

void KeyManage::ExportPublicKey(string userID, string pwd)
{

}

void KeyManage::ExportPrivateKey(string userID, string pwd)
{

}

void KeyManage::KeyStoreListKeys(string pwd)
{

}