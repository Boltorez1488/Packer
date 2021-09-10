//#include <Windows.h>
//#include "Modules\Enter.h"

//void ShowConsole()
//{
//	if (AllocConsole()) {
//		freopen("CONOUT$", "w", stdout);
//		SetConsoleTitleA("Console");
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//		printf("Dll Succefull Attached!\n");
//		printf("Debug Console Started...\n");
//	}
//}
//
//void Main()
//{
//	Enter e;
//	//e.KeyGenerate();
//	e.Distributor();
//}
//
//BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID)
//{
//	if (dwReason == DLL_PROCESS_ATTACH)
//	{
////		ShowConsole();
//		Main();
//	}
//	return TRUE;
//}

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <iostream>
#include <Windows.h>
#include <modes.h>
#include <md5.h>
#include <files.h>
#include <hex.h>
#include <aes.h>
#include <zlib.h>
#pragma comment(lib, "cryptlib.lib")

using namespace std;
using namespace CryptoPP;
using namespace CryptoPP::Weak;

extern "C" _declspec(dllexport) void Pack(char* fname, char* out_name, BYTE* key_b, size_t key_size)
{
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update(key_b, key_size);
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	FileSource sb(fname, true, new StreamTransformationFilter(e, new FileSink(out_name)));
}

extern "C" _declspec(dllexport) void Unpack(char* fname, char* out_name, BYTE* key_b, size_t key_size)
{
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update(key_b, key_size);
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	FileSource sb(fname, true, new StreamTransformationFilter(d, new FileSink(out_name)));
}