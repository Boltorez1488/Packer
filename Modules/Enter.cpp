#include "Enter.h"



Enter::Enter()
{
	GetArgs();
}


Enter::~Enter()
{
	for (int i = 0; i < count; ++i)
		delete(args[i]);
	delete(args);
}

void Enter::ClearScr()
{
	system("cls");
}

void Enter::GetArgs()
{
	LPWSTR* lpArgv = CommandLineToArgvW(GetCommandLineW(), &count);
	args = new char*[count];
	for (int i = 0; i < count; ++i)
	{
		int size = wcslen(lpArgv[i]) + 1;
		args[i] = new char[size];
		wcstombs(args[i], lpArgv[i], size);
	}
	LocalFree(lpArgv);
}

#pragma region Paint
void Enter::PaintDak()
{
	cout << "                                       .;;;.." << endl;
	cout << "                                    ;<!!!!!!!!;" << endl;
	cout << "                                 .;!!!!!!!!!!!!>" << endl;
	cout << "                               .<!!!!!!!!!!!!!!!" << endl;
	cout << "                              ;!!!!!!!!!!!!!!!!'" << endl;
	cout << "                            ;!!!!!!!!!!!!!!!!!'" << endl;
	cout << "                           ;!!!!!!!!!!!!!!!''" << endl;
	cout << "                         ,!!!!!!!!!!!!!'` .::" << endl;
	cout << "                  ,;!',;!!!!!!!!!!!'` .::::''  .,,,,." << endl;
	cout << "                 !!!!!!!!!!!!!!!'`.::::' .,ndMMMMMMM," << endl;
	cout << "                !!!!!!!!!!!!!' .::'' .,nMMP""',nn,`\"MMbmnmn, ." << endl;
	cout << "                `!!!!!!!!!!` :'' ,unMMMM\" xdMMMMMMMx`MMn" << endl;
	cout << "             _/  `'!!!!''`  ',udMMMMMM\" nMMMMM ? ? MMMM )MMMnur = " << endl;
	cout << ",.... ......--~   ,       ,nMMMMMMMMMMnMMP\"., ccc, \"M MMMMP' ,," << endl;
	cout << " `--......--   _.'        \" MMP ? ? 4MMMMMP, c$$$$$$$ ).MMMMnmMMM" << endl;
	cout << "     _.-' _..-~            =\"., nmnMMMM.d$$$$$$$$$L MMMMMMMMMP" << endl;
	cout << " .--~_.--~                  '.`\"4MMMM  $$$$$$$$$$$',MMMMMPPMM" << endl;
	cout << "`~~~~                      ,$$$h.`MM   `?$$$$$$$$P dMMMP , P" << endl;
	cout << "                           <$\"\"?$ `\"     $$$$$$$$',MMMP c$" << endl;
	cout << "                           `$c c$h       $$$$$$$',MMMM  $$" << endl;
	cout << "                            $$ $$$       $$$$$$',MMMMM  `?" << endl;
	cout << "                            `$.`$$$c.   z$???"  "',,`\"" << endl;
	cout << "                             3h $$$$$cccccccccc$$$$$$$$$$$=r" << endl;
	cout << "                             `$c`$$$$$$$$$$$$$$$??$$$$F\"$$ \"" << endl;
	cout << "                           ,mr`$c`$$$$$$$$$$$$$$c 3$$$$c$$" << endl;
	cout << "                        ,mMMMM.\"$.`?$$$$$$$$$$$$$$$$$$$$$$h, " << endl;
	cout << ";.   .               .uMMMMMMMM \"$c, `\"$$$$$$$$$$$$$$$$C,, , , cccccc, , .." << endl;
	cout << "!!;,;!!!!> .,,...  ,nMMMMMMMMMMM.`?$c  `\" ? $$$$$$$$$$$$$$$$$$$$$$$$$$$$h." << endl;
	cout << "!!!!!!!!! uMM\" <!!',dMMMMMMMMMMPP\" ?$h.`::..`\"\"???????\"\"\'.. -= = cc, \"?$$P" << endl;
	cout << "!!!!!!!!'.MMP <!',nMMMMMMMMP\" .;    `$$c,`'::::::::::::'.$F" << endl;
	cout << "!!!!!!!! JMP ;! JMMMMMMMP\" .; !!'      \"?$hc,.````````'., $$" << endl;
	cout << "!!!!'''' 4M(;',dMMMP\"\"\", !!!!`;; !!; .   \"?$$$$$?????????\"" << endl;
	cout << "!!! ::. 4b ,MM\" .::: !''`` <!!!!!!!!; " << endl;
	cout << " `!::::.`' 4M':::::'',mdP <!!!!!!!!!!!;" << endl;
	cout << "! :::::: ..  :::::: ""'' <!!!!!!!!!!!!!!;" << endl;
	cout << "!! ::::::.::: .::::: ;!!> <!!!!!!!!!!!!!!!!!;." << endl;
	cout << "!! :::::: `:'::::::!!' <!!!!!!!!!!!!!!!!!!!!!;;." << endl;
	cout << "! ::::::' .::::' ;!' .!!!!!!!!!!!!!!'`!!!!!!!!!!!;." << endl;
	cout << "; `::';!>  ::' ;<!.;!!!!!!!''''!!!!' <!! !!!!!!!!!!!>" << endl;
}
#pragma endregion Pictures

void Enter::Helper()
{
	ClearScr();
	PaintDak();
	cout << "======================================MAIN_FUNCTIONAL======================================" << endl;
	cout << " DEFAULT FILE KEY: " << FileKey << endl;
	cout << " <Key File> - Can be NULL" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl << endl;

	cout << " -pack <Input Directory> <Mask> <Output Archive> <Pack Level> <Key File>" << endl << endl;

	cout << " -unpack <Archive> <Output Directory> <Key File>" << endl << endl;

	cout << " -add <Input File> <Archive> <Pack Level> <Key File>" << endl << endl;

	cout << " -add_dir <Input Directory> <Mask> <Archive> <Pack Level> <Key File>" << endl << endl;

	cout << " -list <Archive> <Key File>" << endl << endl;

	cout << " -extract <Archive> <FileName> <Output Path> <Key File>" << endl << endl;

	cout << " -exfiles <Archive> <File> <Output Path> <Key File>" << endl << endl;

	cout << " -del <Archive> <FileName> <Key File>" << endl << endl;

	cout << " -delfiles <Archive> <File> <Key File>" << endl << endl;

	cout << "###########################################################################################" << endl << endl;

	cout << "======================================KEY_OPERATION======================================" << endl;
	cout << " DEFAULT FILE KEY: " << FileKey << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl << endl;
	cout << " -keyload <File>" << endl << endl;
	cout << " -keygenerate <Length> <Output>" << endl << endl;
	cout << " -keyset <String> <Output>" << endl << endl;
	cout << "##########################################################################################" << endl << endl;

	cout << "======================================OTHER======================================" << endl;
	cout << " DEFAULT FILE KEY: " << FileKey << endl;
	cout << "---------------------------------------------------------------------------------" << endl << endl;
	cout << " -packother <FileName> <FileOut> <Key File>" << endl << endl;
	cout << " -readother <File> <Key File>" << endl << endl;
	cout << " -unpackother <File> <Key File>" << endl << endl;
	cout << "##########################################################################################" << endl << endl;

	cout << "||===================||" << endl;
	cout << "|| -shelpf <command> ||" << endl;
	cout << "||===================||" << endl << endl;
}

void Enter::ShelpF(string command)
{
	PaintDak();
	cout << "===========================================================" << endl << endl;
	if (command == "-pack" || command == "pack")
		h.Pack();
	else if (command == "-unpack" || command == "unpack")
		h.Unpack();
	else if (command == "-add" || command == "add")
		h.Add();
	else if (command == "-add_dir" || command == "add_dir")
		h.Add_Dir();
	else if (command == "-list" || command == "list")
		h.List();
	else if (command == "-extract" || command == "extract")
		h.Extract();
	else if (command == "-exfiles" || command == "exfiles")
		h.ExtractFiles();
	else if (command == "-del" || command == "del")
		h.Del();
	else if (command == "-delfiles" || command == "delfiles")
		h.DelFiles();
	else if (command == "-keyload" || command == "keyload")
		h.KeyLoad();
	else if (command == "-keygenerate" || command == "keygenerate")
		h.KeyGenerate();
	else if (command == "-keyset" || command == "keyset")
		h.KeySet();
	else if (command == "-packother" || command == "packother")
		h.OtherPack();
	else if (command == "-readother" || command == "readother")
		h.OtherRead();
	else if (command == "-unpackother" || command == "unpackother")
		h.OtherUnpack();
	else
		cout << command << " - is unknown" << endl << endl;
	cout << "===========================================================" << endl << endl;
}

void Enter::Distributor()
{
	ClearScr();
	if (count < 2)
	{
		cout << "Use -help to see the list of commands" << endl;
		return;
	}

	string main = args[1];
	if (main == "-shelpf" || main == "shelpf")
	{
		string command = args[2];
		ShelpF(command);
	}
	else if (main == "-help" || main == "help")
	{
		Helper();
	}
	else if (main == "-pack" || main == "pack")
		Pack();
	else if (main == "-unpack" || main == "unpack")
		Unpack();
	else if (main == "-add" || main == "add")
		Add();
	else if (main == "-add_dir" || main == "add_dir")
		Add_Dir();
	else if (main == "-list" || main == "list")
		List();
	else if (main == "-extract" || main == "extract")
		Extract();
	else if (main == "-exfiles" || main == "exfiles")
		ExtractFiles();
	else if (main == "-del" || main == "del")
		Del();
	else if (main == "-delfiles" || main == "delfiles")
		DelFiles();
	else if (main == "-keyload" || main == "keyload")
		KeyLoad();
	else if (main == "-keygenerate" || main == "keygenerate")
		KeyGenerate();
	else if (main == "-keyset" || main == "keyset")
		KeySave();
	else if (main == "-packother" || main == "packother")
		OtherPack();
	else if (main == "-readother" || main == "readother")
		OtherRead();
	else if (main == "-unpackother" || main == "unpackother")
		OtherUnpack();
	else
		cout << main << " - is unknown" << endl << endl;
}

void Enter::Pack()
{
	string dir, mask, archive, level, key;
	if (count == 6)
	{
		dir = args[2];
		mask = args[3];
		archive = args[4];
		level = args[5];
		key = FileKey;
	}
	else if(count == 7)
	{
		dir = args[2];
		mask = args[3];
		archive = args[4];
		level = args[5];
		key = args[6];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}
	
	try 
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive);
		if (mask == "*")
			pak->AddDirectory(dir);
		else
			pak->AddDirectory(dir, mask);
		int lvl = atoi(level.c_str());
		pak->CreatePack(archive, lvl);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::Unpack()
{
	string archive, outpath, key;
	if (count == 4)
	{
		archive = args[2];
		outpath = args[3];
		key = FileKey;
	}
	else if (count == 5)
	{
		archive = args[2];
		outpath = args[3];
		key = args[4];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);
		pak->SaveAllFiles(outpath);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::Add()
{
	string file, archive, level, key;
	if (count == 5)
	{
		file = args[2];
		archive = args[3];
		level = args[4];
		key = FileKey;
	}
	else if (count == 6)
	{
		file = args[2];
		archive = args[3];
		level = args[4];
		key = args[5];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);
		pak->AddFile(file);
		int lvl = atoi(level.c_str());
		pak->Repack(lvl);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::Add_Dir()
{
	string dir, mask, archive, level, key;
	if (count == 6)
	{
		dir = args[2];
		mask = args[3];
		archive = args[4];
		level = args[5];
		key = FileKey;
	}
	else if (count == 7)
	{
		dir = args[2];
		mask = args[3];
		archive = args[4];
		level = args[5];
		key = args[6];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive);
		if (!pak->FileExists(archive))
		{
			cout << "Archive not found" << endl; 
			return;
		}
		pak->LoadPack();

		if (mask == "*")
		{
			if (pak->AddDirectory(dir))
			{
				int lvl = atoi(level.c_str());
				pak->Repack(lvl);
			}
		}
		else
		{
			if (pak->AddDirectory(dir, mask))
			{
				int lvl = atoi(level.c_str());
				pak->Repack(lvl);
			}
		}
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::List()
{
	string archive, key;
	if (count == 3)
	{
		archive = args[2];
		key = FileKey;
	}
	else if (count == 4)
	{
		archive = args[2];
		key = args[3];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);
		pak->ListFiles();
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::Extract()
{
	string archive, fname, outpath, key;
	if (count == 5)
	{
		archive = args[2];
		fname = args[3];
		outpath = args[4];
		key = FileKey;
	}
	else if (count == 6)
	{
		archive = args[2];
		fname = args[3];
		outpath = args[4];
		key = args[5];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);
		pak->SaveFile(fname, outpath);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::ExtractFiles()
{
	string archive, flist, outpath, key;
	if (count == 5)
	{
		archive = args[2];
		flist = args[3];
		outpath = args[4];
		key = FileKey;
	}
	else if (count == 6)
	{
		archive = args[2];
		flist = args[3];
		outpath = args[4];
		key = args[5];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);

		string s;
		ifstream file(flist);
		while (getline(file, s))
		{
			pak->SaveFile(s, outpath);
		}
		file.close();
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::Del()
{
	string archive, fname, key;
	if (count == 4)
	{
		archive = args[2];
		fname = args[3];
		key = FileKey;
	}
	else if (count == 5)
	{
		archive = args[2];
		fname = args[3];
		key = args[4];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);
		pak->DelFile(fname);
		pak->Repack();
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::DelFiles()
{
	string archive, flist, key;
	if (count == 4)
	{
		archive = args[2];
		flist = args[3];
		key = FileKey;
	}
	else if (count == 5)
	{
		archive = args[2];
		flist = args[3];
		key = args[4];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), archive, true);

		string s;
		ifstream file(flist);
		while (getline(file, s))
		{
			pak->DelFile(s);
		}
		file.close();
		pak->Repack();
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::KeyLoad()
{
	string file;
	if (count == 2)
	{
		file = FileKey;
	}
	else if(count == 3)
	{
		file = args[2];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}
	try
	{
		cout << "Key: " << k.GetKeyFromFile(file) << endl;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}

}

void Enter::KeyGenerate()
{
	string  len, file;
	if (count == 3)
	{
		len = args[2];
		file = FileKey;
	}
	else if (count == 4)
	{
		len = args[2];
		file = args[3];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		int leng = atoi(len.c_str());
		k.GenerateKey(leng);

		cout << "Key: " << k.GetKey() << endl;
		k.SaveToFile(file);
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::KeySave()
{
	string  str, file;
	if (count == 3)
	{
		str = args[2];
		file = FileKey;
	}
	else if (count == 4)
	{
		str = args[2];
		file = args[3];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		k.SetStringKey(str);
		cout << "Key: " << k.GetKey() << endl;
		k.SaveToFile(file);
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::OtherPack()
{
	string fname, fout, level, key;
	if (count == 5)
	{
		fname = args[2];
		fout = args[3];
		level = args[4];
		key = FileKey;
	}
	else if (count == 6)
	{
		fname = args[2];
		fout = args[3];
		level = args[4];
		key = args[5];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), "null");
		int lvl = atoi(level.c_str());
		pak->PackOther(fname, fout, lvl);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::OtherUnpack()
{
	string fname, key;
	if (count == 3)
	{
		fname = args[2];
		key = FileKey;
	}
	else if (count == 4)
	{
		fname = args[2];
		key = args[3];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), "null");
		pak->UnpackOther(fname);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void Enter::OtherRead()
{
	string fname, key;
	if (count == 3)
	{
		fname = args[2];
		key = FileKey;
	}
	else if (count == 4)
	{
		fname = args[2];
		key = args[3];
	}
	else
	{
		cout << "Error command" << endl;
		return;
	}

	try
	{
		ProPack * pak = new ProPack(k.GetKeyFromFile(key), "null");
		cout << "Data: " << pak->GetOtherStr(fname);
		delete pak;
	}
	catch (const exception &e)
	{
		cout << e.what() << endl;
	}
}

void FilterScan(string dir, vector<string>* out, string filter)
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

BOOL CrDir(LPCTSTR sPathTo)
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