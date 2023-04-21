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
using namespace std;

#include "main.h"
#include "global.h"
#include "FileManage.h"
#include "KeyManage.h"
#include "mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QStack>
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

    string mykeyringdir="D:\\OpenPGP_File_Manage_show\\lenovo\\Key\\key-store";
    string aid="516";
    string apwd="561";

    strcpy(mykeyringDir,mykeyringdir.c_str());
    strcpy(passphrase,apwd.c_str());
    strcpy(privateKey,aid.c_str());
    strcpy(recipientKey,aid.c_str());
    strcpy(signerKey,aid.c_str());


/*
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
*/
    while (1)
    {
        pgp.Reset();

        printf("Please enter the message. When finished enter \":q\" on a line by itself:\n");
        char message[100];
        string msg;
        msg="6464848";
        strcpy(message,msg.c_str());
        /*
        message[0] = '\0';
        while (fgets(command, LINE_LEN, stdin))
        {
            command[strlen(command) - 1] = '\0';
            if (strcmp(command, ":q") == 0)
                break;
            strcat(message, command);
            strcat(message, "\n");
        }
        */
        pgp.SetInputMessage(message);


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
        pgp.SetOutputFile("D:\\OpenPGP_File_Manage_show\\lenovo\\File\\text4.gpg");
        ret_code = pgp.SignAndEncrypt();
        if (ret_code) goto done;

        //if (strlen(pgp.GetOutputFile()) <= 0)
        {
            printf("\nSigned & Encrypted Message:\n");
            //char* output;
            //int len;


            pgp.GetOutputMessage();
            //printf("%s\n", output);

            //output[strlen(output) - 1] = '\0';
            //pgp.SetInputMessage(output);

            //Output = output;
        }
/*
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

        //if (strlen(pgp.GetOutputFile()) <= 0)
        {
            printf("\nDecrypted & Verified Message:\n");
            char* output;
            int len;
            pgp.GetOutputMessage();
            printf("%s\n", output);
        }
*/
        break;
    }

done:
    if (ret_code)     // Got an error.  The user is done.
    {
        printf("\nError: %d", ret_code);
        //if (pgp.GetLastError())
        //{
        //    printf(" \"%s\"\n", pgp.GetLastError());
        //}
    }

}
