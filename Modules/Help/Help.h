#pragma once
#include <iostream>
using namespace std;

class HelpNow
{
public:
	HelpNow();
	~HelpNow();

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
	void KeySet();

	void OtherPack();
	void OtherRead();
	void OtherUnpack();

	void GenerateReplace();
};

