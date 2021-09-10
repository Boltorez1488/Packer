#include "ProPack.h"

ProPack::ProPack(string Xor_Key, string pack, bool Load)
{
	Key = Xor_Key;
	Main = pack;
	if (Load)
		LoadPack();
}

ProPack::~ProPack()
{
	delete fdd;
}

void ProPack::SetArchivePath(string pack)
{
	Main = pack;
	if (fdd != NULL)
		fdd = new FileSource(Main.c_str(), true);
}

BOOL ProPack::FileExists(string fname)
{
	return access(fname.c_str(), 0) != -1;
}

void ProPack::PackOther(string fname, string fout, int lvl)
{
	CreateDir(fout);
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new ZlibCompressor(new StreamTransformationFilter(e, new FileSink(fout.c_str())), lvl));
}

string ProPack::GetOtherStr(string fname)
{
	string out;
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new StreamTransformationFilter(d, new ZlibDecompressor(new StringSink(out))));
	return out;
}

void ProPack::UnpackOther(string fname)
{
	string unpacked = fname + ".unpacked.txt";
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	FileSource sb(fname.c_str(), true, new StreamTransformationFilter(d, new ZlibDecompressor(new FileSink(unpacked.c_str()))));
}

string ProPack::ReadFile(string fin)
{
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string name = NameDecrypt(p.fname);
		if (!stricmp(fin.data(), name.data()))
		{
			return DecryptUnpack(p.offset_content, p.size);
		}
	}
}

HANDLE ProPack::PushFile(string fin)
{
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string fname = NameDecrypt(p.fname);
		if (!stricmp(fin.data(), fname.data()))
		{
			replace(fname.begin(), fname.end(), '/', '.');
			HANDLE h = CreateNewTempFile(fname.c_str());
			if (h != NULL)
			{
				DWORD dwWritten;
				string out = DecryptUnpack(p.offset_content, p.size);
				WriteFile(h, out.data(), out.size(), &dwWritten, NULL);
				SetFilePointer(h, 0, NULL, FILE_BEGIN);
				return h;
			}
		}
	}
	return NULL;
}

HANDLE ProPack::CreateNewTempFile(LPCTSTR filePath)
{
	return ::CreateFile(
		filePath,
		GENERIC_READ | GENERIC_WRITE, // reading and writing
		FILE_SHARE_READ, // Note: FILE_FLAG_DELETE_ON_CLOSE will also block readers, unless they specify FILE_SHARE_DELETE 
		/*Security:*/NULL,
		CREATE_NEW, // only create if does not exist
		FILE_ATTRIBUTE_TEMPORARY | // optimize access for temporary file
		FILE_FLAG_DELETE_ON_CLOSE, // delete once the last handle has been closed
		NULL);
}

BOOL ProPack::AddFile(string fname, string path)
{
	if (path != "" )
	{
		if (!FileExists(path + "/" + fname))
		{
			cout << path << "/" << fname << " Not Found on disk" << endl;
			return false;
		}
	}
	else
	{
		if (!FileExists(fname))
		{
			cout << fname << " Not Found on disk" << endl;
			return false;
		}
	}


	for (int i = 0; i < uv.size(); i++)
	{
		string fin = NameDecrypt(uv[i].fname);
		if (!stricmp(fin.data(), fname.data()))
		{ 
			cout << "Exists in pak: " << fname << endl;
			return false; 
		}
	}
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string name = NameDecrypt(p.fname);
		if (!stricmp(name.data(), fname.data()))
		{
			cout << "Exists in pak: " << fname << endl;
			return false;
		}
	}

	string fp;
	if (path != "")
	{
		fp = path; fp += "/"; fp += fname;
	}
	else
	{
		fp = fname;
	}

	Unpacked u;
	u.fname = NameEncrypt(fname);
	u.path_content = fp;
	u.name_size = u.fname.size();

//	cout << "Added: " << fname << endl;
	uv.push_back(u);
	return true;
}

BOOL ProPack::AddDirectory(string path)
{
	vector<string> files;

	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);

	SetCurrentDirectory(path.c_str());
	Scan("", &files);
	SetCurrentDirectory(NPath);
	if (files.size() == 0) return false;
	lword count = 0;
	for (int i = 0; i < files.size(); i++)
	{
		count += AddFile(files[i], path);
	}
	return count == 0 ? false : true;
}

BOOL ProPack::AddDirectory(string path, string mask)
{
	vector<string> files;

	TCHAR NPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, NPath);

	SetCurrentDirectory(path.c_str());
	FilterScan("", &files, mask);
	SetCurrentDirectory(NPath);

	if (files.size() == 0) return false;
	lword count = 0;
	for (int i = 0; i < files.size(); i++)
	{
		count += AddFile(files[i], path);
	}
	return count == 0 ? false : true;
}

BOOL ProPack::DelFile(string fin)
{
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string fname = NameDecrypt(p.fname);
		if (!stricmp(fin.data(), fname.data()))
		{
			pv.erase(pv.begin() + i);
			cout << "Deleted: " << fin << endl;
			return true;
		}
	}
	cout << fin << " - not found in archive, use -list" << endl;
	return false;
}

BOOL ProPack::SaveFile(string fin, string path)
{
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string fname = NameDecrypt(p.fname);
		if (!stricmp(fin.data(), fname.data()))
		{
			string buf = path + "/" + fin;
			CreateDir(buf);

			string out = DecryptUnpack(p.offset_content, p.size);
			
			cout << "Extract: " << buf << endl;
			StringSource st(out, true, new FileSink(buf.c_str()));
			return true;
		}
	}
	cout << fin << " - not found in archive, use -list" << endl;
	return false;
}

void ProPack::SaveAllFiles(string path)
{
	system("cls");
	cout << "Items Count: " << pv.size() << endl;

	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		string fname = NameDecrypt(p.fname);

		string buf = path + "/" + fname;
		CreateDir(buf.c_str());

		cout << "Unpack: " << buf << endl;

		string out = DecryptUnpack(p.offset_content, p.size);

		StringSource st(out, true, new FileSink(buf.c_str()));
	}
}

void ProPack::CreatePack(string packname, int zlib_lvl)
{
	lword count = pv.size() + uv.size();
	CreateDir(packname);

	FileSink* fs = new FileSink(packname.c_str());
	fs->PutModifiable((byte*)&count, sizeof(lword));

	for (int i = 0; i < uv.size(); i++)
	{
		Unpacked u = uv[i];

		system("cls");
		cout << "Packed: " << i + 1 << "/" << uv.size() << endl;
		cout << "Pack: " << NameDecrypt(u.fname) << endl;

		ByteQueue q = FilePack(u.path_content.c_str(), fs, zlib_lvl);
		u.size = q.MaxRetrievable();

		fs->PutModifiable((byte*)&u.size, sizeof(lword));
		fs->PutModifiable((byte*)&u.name_size, sizeof(int));
		fs->PutModifiable((byte*)u.fname.data(), u.fname.size());
		q.TransferAllTo(*fs);
	}
	fs->MessageEnd();
	delete fs;
}

void ProPack::Repack(int zlib_lvl)
{
	if (fdd == NULL)
		fdd = new FileSource(Main.c_str(), true);

	string packname = Main + ".tmp";
	lword count = pv.size() + uv.size();

	FileSink* fs = new FileSink(packname.c_str());
	fs->PutModifiable((byte*)&count, sizeof(lword));

	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];

		system("cls");
		cout << "Repacked: " << i + 1 << "/" << pv.size() << endl;
		cout << "Pack: " << NameDecrypt(p.fname) << endl;

		fs->PutModifiable((byte*)&p.size, sizeof(lword));
		fs->PutModifiable((byte*)&p.name_size, sizeof(int));
		fs->PutModifiable((byte*)p.fname.data(), p.fname.size());
		string ttt;
		fdd->CopyRangeTo(StringSink(ttt), p.offset_content, p.size);

		fs->PutModifiable((byte*)ttt.data(), ttt.size());
	}
	for (int i = 0; i < uv.size(); i++)
	{
		Unpacked u = uv[i];

		system("cls");
		cout << "Packed: " << i + 1 << "/" << uv.size() << endl;
		cout << "Pack: " << NameDecrypt(u.fname) << endl;

		ByteQueue q = FilePack(u.path_content.c_str(), fs, zlib_lvl);
		u.size = q.MaxRetrievable();

		fs->PutModifiable((byte*)&u.size, sizeof(lword));
		fs->PutModifiable((byte*)&u.name_size, sizeof(int));
		fs->PutModifiable((byte*)u.fname.data(), u.fname.size());
		q.TransferAllTo(*fs);
	}
	fs->MessageEnd();
	delete fs;

	delete fdd; fdd = NULL;
	DeleteFileA(Main.c_str());
	MoveFileA(packname.c_str(), Main.c_str());

	system("cls");
	cout << "REPACKED" << endl;
}

void ProPack::LoadPack()
{
	pv.clear();

	lword count = 0;
	lword offset = 0;

	FileSource* fs = new FileSource(Main.c_str(), false);
	GetBytes(fs, (byte*)&count, sizeof(lword)); offset += sizeof(lword);
//	cout << "Count: " << count << endl;

	for (int i = 0; i < count; i++)
	{
		Packed p;
		GetBytes(fs, (byte*)&p.size, sizeof(lword)); offset += sizeof(lword);
		GetBytes(fs, (byte*)&p.name_size, sizeof(int)); offset += sizeof(int);
		GetBytes(fs, &p.fname, p.name_size); offset += p.name_size;
		p.offset_content = offset;
		offset += p.size;
		
		string tmp; fs->Pump(p.size); fs->TransferAllTo(StringSink(tmp)); tmp.clear();

		pv.push_back(p);
	}
	delete fs;
}

void ProPack::ListFiles()
{
	system("cls");
	cout << "====FileList====" << endl;
	for (int i = 0; i < pv.size(); i++)
	{
		Packed p = pv[i];
		cout << NameDecrypt(p.fname) << endl;
	}
	cout << "Items: " << pv.size() << endl;
	cout << "====EndList====" << endl;
}

string ProPack::EncryptPack(string in, int zlib_lvl)
{
	string out;
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	StringSource sb(in, true, new ZlibCompressor(new StreamTransformationFilter(e, new StringSink(out)), zlib_lvl));
	return out;
}

ByteQueue ProPack::FilePack(const char * fin, FileSink* fs, int zlib_lvl)
{
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Encryption e(key, sizeof(key), iv);
	ByteQueue q;

	FileSource sb(fin, true, new ZlibCompressor(new StreamTransformationFilter(e, new Redirector(q)), zlib_lvl));
	return q;
}

string ProPack::DecryptUnpack(string in)
{
	string out;
	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);
	StringSource sb(in, true, new StreamTransformationFilter(d, new ZlibDecompressor(new StringSink(out))));
	return out;
}

string ProPack::DecryptUnpack(lword start, lword size)
{
	if (fdd == NULL)
	{
		fdd = new FileSource(Main.c_str(), true);
	}
	FileSource *fs = fdd;

	byte key[AES::BLOCKSIZE];
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x00, AES::BLOCKSIZE);

	MD5 hash;
	hash.Update((byte*)Key.c_str(), Key.size());
	hash.Final(key);

	CFB_Mode< AES >::Decryption d(key, sizeof(key), iv);

	string ttt;	string out;
	fs->CopyRangeTo(StringSink(ttt), start, size);
	StringSource(ttt, true, new StreamTransformationFilter(d, new ZlibDecompressor(new StringSink(out))));

	return out;
}

string ProPack::NameEncrypt(string fname)
{
	return EncryptPack(fname);
}

string ProPack::NameDecrypt(string fname)
{
	return DecryptUnpack(fname);
}

inline void ProPack::GetBytes(FileSource * fs, byte * out, lword size)
{
	string tmp;
	fs->Pump(size);
	fs->TransferAllTo(StringSink(tmp));
	memcpy(out, tmp.data(), size);
}

inline void ProPack::GetBytes(FileSource * fs, string * out, lword size)
{
	fs->Pump(size);
	fs->TransferAllTo(StringSink(*out));
}

void ProPack::CreateDir(string file)
{
	char * _path = new char[500];
	_splitpath(file.c_str(), NULL, _path, NULL, NULL);
	CrDir(_path);
	delete[] _path;
}

void ProPack::ByteMove(byte * dest, lword size)
{
	string in;
	inbytes.TransferTo(StringSink(in), size);
	memcpy(dest, in.data(), in.size());
}

void ProPack::ByteMove(string *dest, lword size)
{
	inbytes.TransferTo(StringSink(*dest), size);
}

void ProPack::Scan(string strPath, vector<string>* strFiles)
{
	WIN32_FIND_DATA fd; HANDLE handle;
	string strSpec;
	if (strPath != "")
		strSpec = strPath + "/*.*";
	else
		strSpec = "*.*";
	handle = FindFirstFile(strSpec.c_str(), &fd);
	if (handle == INVALID_HANDLE_VALUE)
		return;
	do {
		strSpec = fd.cFileName;
		if (strSpec != "." && strSpec != "..")
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				if (strPath != "")
					strSpec = strPath + "/" + strSpec;
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					Scan(strSpec, strFiles);
				}
				else {
					if (fd.nFileSizeLow != 0 || fd.nFileSizeHigh != 0) {
						strFiles->push_back(strSpec);
					}
				}
			}
		}
	} while (FindNextFile(handle, &fd));
	FindClose(handle);
}

void ProPack::FilterScan(string dir, vector<string>* out, string filter)
{
	WIN32_FIND_DATA fd; HANDLE handle;
	string strSpec;

	char seps[] = "|";
	char *token;
	token = strtok(&filter[0], seps);
	while (token != NULL)
	{
		string str = token;
		if (dir != "")
			strSpec = dir + "/" + str;
		else
			strSpec = str;
		handle = FindFirstFile(strSpec.c_str(), &fd);
		if (handle != INVALID_HANDLE_VALUE)
			do {
				strSpec = fd.cFileName;
				if (strSpec != "." && strSpec != "..")
				{
					if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
					{
						if (dir != "")
							strSpec = dir + "/" + strSpec;
						if (fd.nFileSizeLow != 0 || fd.nFileSizeHigh != 0) {
							out->push_back(strSpec);
						}
					}
				}
			} while (FindNextFile(handle, &fd));
			FindClose(handle);
			token = strtok(NULL, seps);
	}

	if (dir != "")
		strSpec = dir + "/*.*";
	else
		strSpec = "*.*";
	handle = FindFirstFile(strSpec.c_str(), &fd);
	if (handle == INVALID_HANDLE_VALUE)
		return;
	do {
		strSpec = fd.cFileName;
		if (strSpec != "." && strSpec != "..")
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				if (dir != "")
					strSpec = dir + "/" + strSpec;
				if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					FilterScan(strSpec, out, filter);
				}
			}
		}
	} while (FindNextFile(handle, &fd));
	FindClose(handle);
}

BOOL ProPack::CrDir(LPCTSTR sPathTo)
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
