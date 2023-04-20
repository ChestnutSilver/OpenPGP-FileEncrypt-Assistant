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
#define LINE_LEN 100

FileManage::~FileManage()
{

}

void FileManage::SignAndEncryptString(string pwd, string userID, string keyringDir)
{
    OpenPGP pgp;
    MyKeyMgr keymgr;
    int ret_code = 0;
    char command[LINE_LEN];     // user's command
    char mykeyringDir[LINE_LEN];
    char passphrase[LINE_LEN];
    char privateKey[LINE_LEN];
    char recipientKey[LINE_LEN];
    char signerKey[LINE_LEN];

    printf("Keyring Directory: ");
    fgets(mykeyringDir, LINE_LEN, stdin);
    fgets(mykeyringDir, LINE_LEN, stdin);
    mykeyringDir[strlen(mykeyringDir) - 1] = '\0';
    keymgr.LoadKeyring(mykeyringDir);

    printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
    fgets(privateKey, LINE_LEN, stdin);
    privateKey[strlen(privateKey) - 1] = '\0';
    printf("Passphrase: ");
    fgets(passphrase, LINE_LEN, stdin);
    passphrase[strlen(passphrase) - 1] = '\0';
    printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
    fgets(recipientKey, LINE_LEN, stdin);
    recipientKey[strlen(recipientKey) - 1] = '\0';
    printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
    fgets(signerKey, LINE_LEN, stdin);
    signerKey[strlen(signerKey) - 1] = '\0';

    while (1)
    {
        pgp.Reset();

        printf("Please enter the message. When finished enter \":q\" on a line by itself:\n");
        char message[100];
        message[0] = '\0';
        while (fgets(command, LINE_LEN, stdin))
        {
            command[strlen(command) - 1] = '\0';
            if (strcmp(command, ":q") == 0)
                break;
            strcat(message, command);
            strcat(message, "\n");
        }
        pgp.SetInputMessage(message, strlen(message));

        
        if (strlen(privateKey) <= 0)
        {
            printf("Please select a private key.\n");
            break;
        }
        if (strlen(recipientKey) <= 0)
        {
            printf("Please select a recipient key.\n");
            break;
        }
        if (strlen(signerKey) <= 0)
        {
            printf("Please select a signer key.\n");
            break;
        }

        pgp.SetASCIIArmor(true);
        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetRecipientKeyCount(1);
        pgp.SetRecipientKeyKeyring(0, mykeyringDir);
        pgp.SetRecipientKeyUserId(0, recipientKey);
        ret_code = pgp.SignAndEncrypt();
        if (ret_code) goto done;

        if (strlen(pgp.GetOutputFile()) <= 0)
        {
            printf("\nSigned & Encrypted Message:\n");
            char* output;
            int len;
            pgp.GetOutputMessage(output, len);
            printf("%s\n", output);

            output[strlen(output) - 1] = '\0';
            pgp.SetInputMessage(output, strlen(output));

            Output = output;
        }

        //解密
        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetSignerKeyCount(1);
        pgp.SetSignerKeyKeyring(0, mykeyringDir);
        pgp.SetSignerKeyUserId(0, signerKey);
        ret_code = pgp.DecryptAndVerifySignature();
        if (ret_code) goto done;

        ret_code = pgp.DecryptAndVerifySignature();
        if (ret_code) goto done;

        if (strlen(pgp.GetOutputFile()) <= 0)
        {
            printf("\nDecrypted & Verified Message:\n");
            char* output;
            int len;
            pgp.GetOutputMessage(output, len);
            printf("%s\n", output);
        }

        break;
    }

done:
    if (ret_code)     // Got an error.  The user is done.
    {
        printf("\nError: %d", ret_code);
        if (pgp.GetLastError())
        {
            printf(" \"%s\"\n", pgp.GetLastError());
        }
    }

}

void FileManage::DecryptAndVerifyString(string signedAndEncryptedMessage, string pwd, string userID)
{
    OpenPGP pgp;
    MyKeyMgr keymgr;
    int ret_code = 0;
    char command[LINE_LEN];     // user's command
    char mykeyringDir[LINE_LEN];
    char passphrase[LINE_LEN];
    char privateKey[LINE_LEN];
    char recipientKey[LINE_LEN];
    char signerKey[LINE_LEN];

    printf("Keyring Directory: ");
    fgets(mykeyringDir, LINE_LEN, stdin);
    mykeyringDir[strlen(mykeyringDir) - 1] = '\0';
    keymgr.LoadKeyring(mykeyringDir);

    printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
    fgets(privateKey, LINE_LEN, stdin);
    privateKey[strlen(privateKey) - 1] = '\0';
    printf("Passphrase: ");
    fgets(passphrase, LINE_LEN, stdin);
    passphrase[strlen(passphrase) - 1] = '\0';
    printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
    fgets(recipientKey, LINE_LEN, stdin);
    recipientKey[strlen(recipientKey) - 1] = '\0';
    printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
    fgets(signerKey, LINE_LEN, stdin);
    signerKey[strlen(signerKey) - 1] = '\0';

    while (1)
    {
        if (strlen(privateKey) <= 0)
        {
            printf("Please select a private key.\n");
            break;
        }

        Output[strlen(Output) - 1] = '\0';
        pgp.SetInputMessage(Output, strlen(Output));

        //解密
        pgp.SetKeyCount(1);
        pgp.SetKeyKeyring(0, mykeyringDir);
        pgp.SetKeyUserId(0, privateKey);
        pgp.SetKeyPassphrase(0, passphrase);
        pgp.SetSignerKeyCount(1);
        pgp.SetSignerKeyKeyring(0, mykeyringDir);
        pgp.SetSignerKeyUserId(0, signerKey);
        ret_code = pgp.DecryptAndVerifySignature();
        if (ret_code) goto done;

        if (strlen(pgp.GetOutputFile()) <= 0)
        {
            printf("\nDecrypted & Verified Message:\n");
            char* output;
            int len;
            pgp.GetOutputMessage(output, len);
            printf("%s\n", output);
        }
    }

done:
    if (ret_code)     // Got an error.  The user is done.
    {
        printf("\nError: %d", ret_code);
        if (pgp.GetLastError())
        {
            printf(" \"%s\"\n", pgp.GetLastError());
        }
    }

    fprintf(stderr, "\npress <return> to continue...\n");
    getchar();
    exit(ret_code);
}


string FileManage::SignAndEncryptSingle(string pwd, string filePath, string userID, string pathStringFile, string keyringDir)
{
    keyringDir = conbineStrings(keyringDir, "key-store");

    string newFile = ToString(userID) + "Encrypted.gpg"; //生成文件名为 userID + Encrypted.gpg
    string outputFile = conbineStrings(pathStringFile, newFile);

    char passphrase[LINE_LEN];
    char privateKey[LINE_LEN];
    char recipientKey[LINE_LEN];
    char signerKey[LINE_LEN];

    printf("\nPrivate Key User Id (Used to sign outgoing messages and decrypt incoming messages): ");
    fgets(privateKey, LINE_LEN, stdin);
    privateKey[strlen(privateKey) - 1] = '\0';
    printf("Passphrase: ");
    fgets(passphrase, LINE_LEN, stdin);
    passphrase[strlen(passphrase) - 1] = '\0';
    printf("Recipient Key User Id (Used to encrypt outgoing messages): ");
    fgets(recipientKey, LINE_LEN, stdin);
    recipientKey[strlen(recipientKey) - 1] = '\0';
    printf("Signer Key User Id (Used to verify the signature of an incoming message): ");
    fgets(signerKey, LINE_LEN, stdin);
    signerKey[strlen(signerKey) - 1] = '\0';

    modeUserIDPwd.modeUserID = privateKey;
    modeUserIDPwd.modePwd = passphrase;

    OpenPGP pgp;
    pgp.SetInputFile(filePath.c_str());
    pgp.SetOutputFile(outputFile.c_str());

    pgp.SetASCIIArmor(true);
    pgp.SetOverwrite(true);//覆盖写
    pgp.SetKeyCount(1);
    pgp.SetKeyKeyring(0, keyringDir.c_str());
    pgp.SetKeyUserId(0, privateKey);
    pgp.SetKeyPassphrase(0, passphrase);
    pgp.SetRecipientKeyCount(1);
    pgp.SetRecipientKeyKeyring(0, keyringDir.c_str());
    pgp.SetRecipientKeyUserId(0, recipientKey);

    int ret_code = pgp.SignAndEncrypt();
    cout << ret_code << endl;
    if (ret_code)     // Got an error.  The user is done.
    {
        printf("\nError: %d", ret_code);
        if (pgp.GetLastError())
        {
            printf(" \"%s\"\n", pgp.GetLastError());
        }
    }

    return outputFile;
}

string FileManage::SignAndEncryptMultiple(string pwd, string filePath, vector<string> allUsers, string userID, string pathStringFile, string keyringDir)
{
    //待加密文件名
    //string fileName = filePath.substr(filePath.find_last_of("\\"));//取文件名不确定是否可行
    //加密后文件名
    //string newFile = fileName + ".gpg";//生成文件名为源文件名加gpg后缀
    //加密后文件路径
    //string outputFile = conbineStrings(pathStringFile, newFile);


    //fileName = "D:\\masm\\222.asm";
    //newFile = "222.gpg";
    //outputFile = "D:\\masm\\222.gpg";

    OpenPGP pgp;

    char command[LINE_LEN];
    printf("Input File: ");
    fgets(command, LINE_LEN, stdin);
    command[strlen(command) - 1] = '\0';
    pgp.SetInputFile(command);

    printf("Output File: ");
    fgets(command, LINE_LEN, stdin);
    command[strlen(command) - 1] = '\0';
    pgp.SetOutputFile(command);

    //pgp.SetInputFile(fileName.c_str());
    //pgp.SetOutputFile(outputFile.c_str());

    pgp.SetASCIIArmor(true);
    pgp.SetOverwrite(true);//覆盖写
    pgp.SetKeyPassphrase(0, pwd.c_str());

    pgp.SetKeyCount(1);
    pgp.SetKeyKeyring(0, keyringDir.c_str());
    pgp.SetKeyUserId(0, userID.c_str());

    int count = allUsers.size();//假设存的id
    pgp.SetRecipientKeyCount(count);
    pgp.SetRecipientKeyKeyring(0, keyringDir.c_str());
    for (int i = 0; i < count; i++)
        pgp.SetRecipientKeyUserId(0, allUsers[i].c_str());


    int ret_code = pgp.SignAndEncrypt();

    return "A";
}

bool FileManage::VerifySingle(string pwd, string filePath, string userID, string pathStringFile, string keyringDir)
{
    keyringDir = conbineStrings(keyringDir, "key-store");

    string tempFile = conbineStrings(pathStringFile, "temp.txt");

    OpenPGP pgp;
    pgp.SetOverwrite(1);
    pgp.SetInputFile(filePath.c_str());
    pgp.SetOutputFile(tempFile.c_str());

    pgp.SetKeyCount(1);
    pgp.SetKeyKeyring(0, keyringDir.c_str());
    pgp.SetKeyUserId(0, userID.c_str());
    pgp.SetKeyPassphrase(0, pwd.c_str());
    pgp.SetSignerKeyCount(1);
    pgp.SetSignerKeyKeyring(0, keyringDir.c_str());
    pgp.SetSignerKeyUserId(0, userID.c_str());
    int ret_code = pgp.DecryptAndVerifySignature();
    //deletetempfile
    if (ret_code)
    {
        return false;
    }
    else
    {
        WriteLine("身份验证成功");
        return true;
    }
}

bool FileManage::Verify(string pwd, string filePath, vector<string> allUsers, string userID, string pathStringFile, string keyringDir)
{
    return true;
}