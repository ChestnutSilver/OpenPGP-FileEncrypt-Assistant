#ifndef FILEMANAGE_H
#define FILEMANAGE_H

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
#include <io.h>//*********
using namespace std;

#include "main.h"
#include "KeyManage.h"
#include "mainwindow.h"

class FileManage
{
private:
    char* Output;

public:
    struct ModeUserIDPwd {
        string modeUserID;
        string modePwd;
    }modeUserIDPwd;

public:
    ~FileManage();
    void SignAndEncryptString(string pwd, string userID, string keyringDir);
    void DecryptAndVerifyString(string signedAndEncryptedMessage, string pwd, string userID);
    string SignAndEncryptSingle(string pwd, string filePath, string userID, string pathStringFile, string keyringDir);
    string SignAndEncryptMultiple(string pwd, string filePath, string userID, string pathStringFile, string keyringDir);
    //string SignAndEncryptMultiple(string pwd, string filePath, vector<string> allUsers, string userID, string pathStringFile, string keyringDir);
    bool VerifySingle(string pwd, string filePath, string userID, string pathStringFile, string keyringDir);
    bool Verify(string pwd, string filePath, string userID, string pathStringFile, string keyringDir);
    //bool Verify(string pwd, string filePath, vector<string> allUsers, string userID, string pathStringFile, string keyringDir);
};
#endif // FILEMANAGE_H
