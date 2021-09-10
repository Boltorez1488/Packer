#pragma once
#include <Windows.h>
#include "Modules/ProPack.h"
#include "Modules\Enter.h"

int argc;
char** argv;

void GetArgs()
{
	LPWSTR* lpArgv = CommandLineToArgvW(GetCommandLineW(), &argc);
	argv = new char*[argc];
	for (int i = 0; i < argc; ++i)
	{
		int size = wcslen(lpArgv[i]) + 1;
		argv[i] = new char[size];
		wcstombs(argv[i], lpArgv[i], size);
	}
	LocalFree(lpArgv);
}
void ClearArgs()
{
	for (int i = 0; i < argc; ++i)
		delete(argv[i]);
	delete(argv);
}

void Packing(string in, string out, string level, string mask = "*", string key = "Join")
{
	ProPack *fs = new ProPack(key, out);
	if (mask == "*")
		fs->AddDirectory(in);
	else
		fs->AddDirectory(in, mask);

	int lvl = atoi(level.c_str());
	fs->CreatePack(out, lvl);
	delete fs;
}

void Unpacking(string arc_name, string out_dir, string key = "Join")
{
	ProPack *fs = new ProPack(key, arc_name);
	fs->LoadPack();
	fs->SaveAllFiles(out_dir);
	delete fs;
}

void AddFile(string in, string out, string level, string key = "Join")
{
	ProPack *fs = new ProPack(key, out);
	if (fs->FileExists(out)) fs->LoadPack();

	if (fs->AddFile(in))
	{
		int lvl = atoi(level.c_str());
		if (fs->FileExists(out))
		{
			fs->Repack(out, lvl);
		}	
		else
			fs->CreatePack(out, lvl);
	}
	delete fs;
}

void AddFiles(string in, string out, string level, string mask = "*", string key = "Join")
{
	ProPack *fs = new ProPack(key, out);
	if (fs->FileExists(out)) fs->LoadPack();

	if (mask == "*")
	{
		if (fs->AddDirectory(in))
		{
			int lvl = atoi(level.c_str());
			if (fs->FileExists(out))
			{
				fs->Repack(out, lvl);
			}
			else
				fs->CreatePack(out, lvl);
		}
	}
	else
	{
		if (fs->AddDirectory(in, mask))
		{
			int lvl = atoi(level.c_str());
			if (fs->FileExists(out))
			{
				fs->Repack(out, lvl);
			}
			else
				fs->CreatePack(out, lvl);
		}
	}


	delete fs;
}

void ListFiles(string in, string key = "Join")
{
	ProPack *fs = new ProPack(key, in);
	fs->LoadPack();
	fs->ListFiles();
	delete fs;
}

void ExtractFile(string in, string file, string path, string key = "Join")
{
	ProPack *fs = new ProPack(key, in);
	fs->LoadPack();
	fs->SaveFile(file, path);
	delete fs;
}

void ExtractFiles(string in, string filelist, string path, string key = "Join")
{
	ProPack *fs = new ProPack(key, in);
	fs->LoadPack();
	string s;
	ifstream file(filelist);
	while (getline(file, s))
	{ 
		fs->SaveFile(s, path);
	}
	file.close();
	delete fs;
}

void _DeleteFile(string in, string level, string file, string key = "Join")
{
	ProPack *fs = new ProPack(key, in);
	fs->LoadPack();
	if (fs->DelFile(file))
	{
		int lvl = atoi(level.c_str());
		fs->Repack(in, lvl);
	}
	delete fs;
}
void _DeleteFiles(string in, string level, string filelist, string key = "Join")
{
	ProPack *fs = new ProPack(key, in);
	fs->LoadPack();
	lword count = 0;
	string s;

	ifstream file(filelist);
	while (getline(file, s))
	{
		if(fs->DelFile(s)) count++;
	}
	file.close();
	int lvl = atoi(level.c_str());
	if(count != 0)
		fs->Repack(in, lvl);
	delete fs;
}


void Help2()
{
	system("cls");
	cout << "====USAGE====" << endl;
	cout << "-pack <Input Directory> <Mask> <Output File> <Pack Level> <Key - You can not specify>" << endl;
	cout << "-unpack <Input Archive> <Output Directory> <Key - You can not specify>" << endl;
	cout << "-add <Input File> <Archive - It's Loading Archive> <Pack Level> <Key - You can not specify>" << endl;
	cout << "-add_dir <Input Directory> <Mask> <Output File - It's Loading Archive> <Pack Level> <Key - You can not specify>" << endl;
	cout << "-list <Input Archive> <Key - You can not specify>" << endl;
	cout << "-extract <Input Archive> <FileName> <Output Path> <Key - You can not specify>" << endl;
	cout << "-exfiles <Input Archive> <Input FileList Txt> <Output Path> <Key - You can not specify>" << endl;
	cout << "-del <Input Archive> <Zlib Level Repack> <FileName> <Output Path> <Key - You can not specify>" << endl;
	cout << "-delfiles <Input Archive> <Zlib Level Repack> <Input FileList Txt> <Key - You can not specify>" << endl;
	cout << "====USAGE====" << endl;
}

struct test
{
	int s;
	string t;
};

void Sk()
{
	FileSink fsd("tatp.txt");
	//FileSource *fd = new FileSource("./ttt.txt", false, new FileSink("tata.txt"));
	FileSource fd("./ttt.txt", false, new Redirector(fsd));
//	fd.Attach(new Redirector(fsd));
	fd.TransferAllTo(fsd);
	fd.Pump(1);
	cout << "Skip: " << fd.Skip(2) << endl;
	fd.PumpAll();
	//delete fd;
	system("pause");
	exit(0x0);
}

void Menu()
{
	Enter e; e.Distributor();
	
	system("pause");
	exit(0x0);
	//Sk();
	//
	//test t;
	//t.s = 25;
	//t.t = "test";

	//FileSink fs("test.txt");
	//fs.PutModifiable((byte*)&t.s, sizeof(int));
	//fs.PutModifiable((byte*)&t.t, 4);
	//fs.MessageEnd();

	//FileSink f("tes.txt");
	//FileSource fd("test.txt", true, &f);
	//f.PutModifiable((byte*)" 25", 3);
	//f.MessageEnd();
	//FileSink fsd("tatp.txt");
	//FileSource fd("ttt.txt", false);

	//string tmp;
	//fd.Attach(new Redirector(fsd));
	////fd.Skip(4);
	////fd.Pump(2);
	////fd.Attach(new Redirector(fsd));
	//cout << "Skip: " << fd.Skip(2) << endl;
	//fd.PumpAll();
	//system("pause");

	//fd.TransferAllTo(StringSink(tmp));
	////fd.Pump(4);

	////int p; string st = "....";
	////ifstream f("test.txt", ios::app | ios::binary);
	////f.seekg(0, ios::beg);
	////f.read((char*)&p, sizeof(int));
	////f.read((char*)&st, 4);
	////
	////cout << p << endl << st << endl;
	//system("pause");
	////f.Skip(2);
	////f.PutModifiable((byte*)" 25", 4);
	//return;
	try 
	{
		system("cls");
		if (argc == 1)
		{
			cout << "Use -help to list commands" << endl;
			return;
		}
		string command = argv[1];
		if (command == "pack" || command == "-pack")
		{
			string input_dir, mask, arc_name, level, key;
			input_dir = argv[2];
			mask = argv[3];
			arc_name = argv[4];
			level = argv[5];
			if (argc > 5)
			{
				key = argv[6];
				Packing(input_dir, arc_name, level, mask, key);
			}
			else
				Packing(arc_name, input_dir, level, mask);
			system("cls");
			cout << "PACKED" << endl;

		}
		else if (command == "unpack" || command == "-unpack")
		{
			string arc_name, out_dir, key;
			arc_name = argv[2];
			out_dir = argv[3];
			if (argc > 3)
			{
				key = argv[4];
				Unpacking(arc_name, out_dir, key);
			}
			else
				Unpacking(arc_name, out_dir);
		//	system("cls");
			cout << "UNPACKED" << endl;

		}
		else if (command == "add" || command == "-add")
		{
			string arc_name, input_dir, level, key;
			input_dir = argv[2];
			arc_name = argv[3];
			level = argv[4];
			if (argc > 4)
			{
				key = argv[5];
				AddFile(input_dir, arc_name, level, key);
			}
			else
				AddFile(input_dir, arc_name, level);
			//system("cls");
			//cout << "ADDED" << endl;

		}
		else if (command == "add_dir" || command == "-add_dir")
		{
			string arc_name, input_dir, mask, level, key;
			input_dir = argv[2];
			mask = argv[3];
			arc_name = argv[4];
			level = argv[5];
			if (argc > 5)
			{
				key = argv[6];
				AddFiles(input_dir, arc_name, level, mask, key);
			}
			else
				AddFiles(input_dir, arc_name, level, mask);
			//system("cls");
			//cout << "ADDED" << endl;

		}
		else if (command == "list" || command == "-list")
		{
			string arc_name, key;
			arc_name = argv[2];

			if (argc > 2)
			{
				key = argv[3];
				ListFiles(arc_name, key);
			}
			else
				ListFiles(arc_name);

		}
		else if (command == "extract" || command == "-extract")
		{
			string arc_name, file, path, key;

			arc_name = argv[2];
			file = argv[3];
			path = argv[4];
			if (argc > 4)
			{
				key = argv[5];
				ExtractFile(arc_name, file, path, key);
			}
			else
				ExtractFile(arc_name, file, path);

		}
		else if (command == "exfiles" || command == "-exfiles")
		{
			string arc_name, filelist, path, key;

			arc_name = argv[2];
			filelist = argv[3];
			path = argv[4];
			if (argc > 4)
			{
				key = argv[5];
				ExtractFiles(arc_name, filelist, path, key);
			}
			else
				ExtractFiles(arc_name, filelist, path);

		}
		else if (command == "del" || command == "-del")
		{
			string arc_name, file, path, key;

			arc_name = argv[2];
			file = argv[3];
			path = argv[4];
			if (argc > 4)
			{
				key = argv[5];
				_DeleteFile(arc_name, file, path, key);
			}
			else
				_DeleteFile(arc_name, file, path);

		}
		else if (command == "delfiles" || command == "-delfiles")
		{
			string arc_name, level, filelist, key;

			arc_name = argv[2];
			level = argv[3];
			filelist = argv[4];
			if (argc > 4)
			{
				key = argv[5];
				_DeleteFiles(arc_name, level, filelist, key);
			}
			else
				_DeleteFiles(arc_name, level, filelist);

		}
		else if (command == "help" || command == "-help")
			Help2();
	}
	catch (const exception &e)
	{
		cout << endl << "Exception: " << e.what() << endl;
	}
}

void Main()
{
	GetArgs();
	Menu();
	ClearArgs();
//	system("pause");

	//ProPack *fs = new ProPack("123");
	////	fs.AddFile("Container.dll");
	////	fs.AddFile("Container.pdb");
	//fs->AddDirectory("Bin");

	//fs->CreatePack("archive.txt", 9);
	//fs->LoadPack("archive.txt");

	//string f;
	//fs->ReadFile("Container.dll", &f);

	//fs->SaveAllFiles("Out");
	//delete fs;

//	system("Pause");
}