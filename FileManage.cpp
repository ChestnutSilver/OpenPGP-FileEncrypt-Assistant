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

        //½âÃÜ
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

        //½âÃÜ
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