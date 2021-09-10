#pragma once
#include "ProPack.h"
#include "Key.h"
#include "Help\Help.h"
#include "ProPack.h"
#include "../../tinyxml2/tinyxml2.h"
#pragma comment(lib, "tinyxml2.lib")

class Enter
{
public:
	Enter();
	~Enter();
	void ClearScr();
	void Helper();
	void ShelpF(string command);
	void Distributor();

	void Pack();
	void Unpack();
	void Add();
	void Add_Dir();
	void List();
	void Extract();
	void ExtractFiles();
	void Del();
	void DelFiles();

	void KeyLoad();
	void KeyGenerate();
	void KeySave();

	void OtherPack();
	void OtherUnpack();
	void OtherRead();
private:
	HelpNow h;
	string FileKey = "crt.kfs";
	Key k;

	char **args;
	int count;

	void GetArgs();
	void PaintDak();
};

