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
#include "FileManage.h"
#include "global.h"

class ModeManage
{
private:
	struct ModeGlobal {
		string pathString;
		string pathStringUser;
		string pathStringKey;
		string pathStringFile;
	}modeGlobal;

public:
	~ModeManage();
	int modeInput(Global global, User user);
	void modeControl(int mode, User user, string pwd);
};