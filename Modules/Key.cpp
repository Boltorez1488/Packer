#include "Key.h"
#include <io.h>
BOOL Key::FileExists(string fname)
{
	return access(fname.c_str(), 0) != -1;
}

void Key::CreateDir(string file)
{
	char * _path = new char[500];
	_splitpath(file.c_str(), NULL, _path, NULL, NULL);
	CrDir(_path);
	delete[] _path;
}

BOOL Key::CrDir(LPCTSTR sPathTo)
{
	BOOL bRet = sPathTo ? TRUE : FALSE;

	while (bRet && (bRet = CreateDirectory(sPathTo, NULL)) == FALSE)
	{
		__try {
			int k = lstrlen(sPathTo);
			if (k >= MAX_PATH) break;
			LPTSTR   sTemp = LPTSTR(_alloca((k + 1) * sizeof(TCHAR)));
			lstrcpy(sTemp, sPathTo);
			while (k && sTemp[k] != TCHAR('\\') && sTemp[k] != TCHAR('/')) --k;
			if (k <= 0) break;
			sTemp[k] = TCHAR('\0');
			bRet = CrDir(sTemp);
		}
		__except (GetExceptionCode() == STATUS_STACK_OVERFLOW) { break; }
	}
	return bRet;
}

void Validator()
{
	exit(10);
}

Key::Key(string file_key)
{
	_skey = "!@#$%^&*";
	if (file_key != "")
	{
		_KeyForMd = GetKeyFromFile(file_key);
	}
}

Key::~Key()
{
	_skey.clear();
	_KeyForMd.clear();
}

string Key::GetKey()
{
	return _KeyForMd;
}

string Key::GetKeyFromFile(string fname)
{
	string out;
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)_skey.c_str(), _skey.size());
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new StreamTransformationFilter(d, new ZlibDecompressor(new StringSink(out))));
	return out;
}

string Key::random_string(size_t length)
{
	srand(time(0));
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"!@#$%^&*"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}

void Key::GenerateKey(int len)
{
	_KeyForMd = random_string(len);//XOR(random_string(len), _skey);
}

void Key::SetStringKey(string str)
{
	_KeyForMd = str;
}

void Key::SaveToFile(string fname, int zlib_lvl)
{
	CreateDir(fname);
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)_skey.c_str(), _skey.size());
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	StringSource sb(_KeyForMd, true, new ZlibCompressor(new StreamTransformationFilter(e, new FileSink(fname.c_str())), zlib_lvl));
}

void Key::LoadFromFile(string fname)
{
	if (!FileExists(fname))
	{
		CreateThread(0, 0, LPTHREAD_START_ROUTINE(Validator), 0, 0, 0);
		return;
	}
	_KeyForMd = GetKeyFromFile(fname);
}