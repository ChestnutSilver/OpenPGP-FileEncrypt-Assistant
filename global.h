#pragma once
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
#include "user.h"

#include <sstream>

string conbineStrings(string left, string right);
int createDirectoryByString(string path);

class Global
{
private:
	User EnvironmentUser;
public:
	string baseName = "D:\\";
	string folderName = "OpenPGP_File_Manage_show";
	string folderName1 = "Key";
	string folderName2 = "File";

	string pathString;
	string pathStringUser;
	string pathStringKey;
	string pathStringFile;

public:
	Global();
	void set_baseName();
	~Global();
};

