#pragma once
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#pragma comment(lib, "cryptlib.lib")
#include <Windows.h>

#include <iostream>
#include <modes.h>
#include <md5.h>
#include <files.h>
#include <hex.h>
#include <aes.h>
#include <zlib.h>

using namespace CryptoPP;
using namespace CryptoPP::Weak;
using namespace std;

#include <vector>
#include <io.h>

class ProPack
{
public:
	ProPack(string Xor_Key, string pack, bool Load = false);
	~ProPack();
	void SetArchivePath(string pack);
	BOOL FileExists(string fname);

	void PackOther(string fname, string fout, int lvl = 9);
	string GetOtherStr(string fname);
	void UnpackOther(string fname);

	string ReadFile(string fin);
	HANDLE PushFile(string fin); // Push file in memory and get his header
	HANDLE CreateNewTempFile(LPCTSTR filePath);

	BOOL AddFile(string fin, string path = "");
	BOOL AddDirectory(string path);
	BOOL AddDirectory(string path, string mask);

	BOOL DelFile(string fin);

	BOOL SaveFile(string fin, string path);
	void SaveAllFiles(string path);

	void CreatePack(string packname, int zlib_lvl = 9);
	void Repack(int zlib_lvl = 9);
	void LoadPack();
	void ListFiles();

	string EncryptPack(string in, int zlib_lvl = 9);
	ByteQueue FilePack(const char * fin, FileSink* fs, int zlib_lvl = 9);

	string DecryptUnpack(string in);
	string DecryptUnpack(lword start, lword size);

	string NameEncrypt(string fname);
	string NameDecrypt(string fname);

	inline void GetBytes(FileSource *fs, byte * out, lword size);
	inline void GetBytes(FileSource *fs, string *out, lword size);

	void CreateDir(string file);

private:
	FileSource *fdd = NULL;
	string Main;
	string Key;

	struct Unpacked
	{
		lword size;
		int name_size;
		string fname;
		string path_content;
	};
	struct Packed
	{
		lword size;
		int name_size;
		string fname;
		lword offset_content;
	};

//	Cryptograph cr;
//	ZPacker zp;

	vector<Unpacked> uv;
	vector<Packed> pv;

	ByteQueue inbytes;
	void ByteMove(byte* dest, lword size);
	void ByteMove(string *dest, lword size);

	void Scan(string strPath, vector<string> *strFiles);
	void FilterScan(string dir, vector<string> *out, string filter);
	BOOL CrDir(LPCTSTR sPathTo);
};

