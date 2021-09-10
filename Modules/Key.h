#pragma once
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <Windows.h>
#include <iostream>
#include <md5.h>
#include <aes.h>
#include <zlib.h>
#include <modes.h>
#include <files.h>
#include <time.h>

using namespace CryptoPP;
using namespace CryptoPP::Weak;
using namespace std;

class Key
{
public:
	Key(string file_key = "");
	~Key();
	string GetKey();
	string GetKeyFromFile(string fname);

	string random_string(size_t length = 5);
	void GenerateKey(int len = 5);
	void SetStringKey(string str);

	void SaveToFile(string fname, int zlib_lvl = 9);
	void LoadFromFile(string fname);

private:
	string _skey;
	string _KeyForMd;

	BOOL FileExists(string fname);
	void CreateDir(string file);
	BOOL CrDir(LPCTSTR sPathTo);
};

