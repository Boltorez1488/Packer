#pragma once
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

__declspec(dllexport) void Pack(string fname, string out_name, BYTE* key_b, size_t key_size)
{
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update(key_b, key_size);
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new StreamTransformationFilter(e, new FileSink(out_name.c_str())));
}

__declspec(dllexport) void Unpack(string fname, string out_name, BYTE* key_b, size_t key_size)
{
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update(key_b, key_size);
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new StreamTransformationFilter(d, new FileSink(out_name.c_str())));
}
