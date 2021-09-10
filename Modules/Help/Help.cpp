#include "Help.h"

HelpNow::HelpNow()
{
}


HelpNow::~HelpNow()
{
}

void HelpNow::Pack()
{
	cout << "Pack:" << endl << endl;
	cout << "<Input Directory> - Directory for the packing" << endl << endl;
	cout << "<Mask> - Her mask of files, * = All Files" << endl << endl;
	cout << "<Output Archive> - Archive output name" << endl << endl;
	cout << "<Pack Level> - Packing level of the archive" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::Unpack()
{
	cout << "Unpack:" << endl << endl;
	cout << "<Archive> - Archive which is the packed" << endl << endl;
	cout << "<Output Directory> - Directory for the unpack files" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::Add()
{
	cout << "Add:" << endl << endl;
	cout << "<Input File> - The file is added to the archive" << endl << endl;
	cout << "<Archive> - Archive for file uploads" << endl << endl;
	cout << "<Pack Level> - Packing level of the file" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::Add_Dir()
{
	cout << "Add Directory:" << endl << endl;
	cout << "<Input Directory> - Directory for the adding to archive" << endl << endl;
	cout << "<Mask> - Her mask of files, * = All Files" << endl << endl;
	cout << "<Archive> - Archive for dir uploads" << endl << endl;
	cout << "<Pack Level> - Packing level of the dir" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::List()
{
	cout << "List Files:" << endl << endl;
	cout << "<Archive> - Archive for list files" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::Extract()
{
	cout << "Extract One File:" << endl << endl;
	cout << "<Archive> - Archive for extracting file" << endl << endl;
	cout << "<FileName> - Search file in the archive" << endl << endl;
	cout << "<Output Path> - Path for extracting file" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::ExtractFiles()
{
	cout << "Extract Files:" << endl << endl;
	cout << "<Archive> - Archive for extracting files" << endl << endl;
	cout << "<File> - File with the list" << endl << endl;
	cout << "<Output Path> - Path for extracting files" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::Del()
{
	cout << "Delete File:" << endl << endl;
	cout << "<Archive> - Archive for deleting file" << endl << endl;
	cout << "<File Name> - Search file in the archive" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::DelFiles()
{
	cout << "Delete Files:" << endl << endl;
	cout << "<Archive> - Archive for deleting file" << endl << endl;
	cout << "<File> - File with the list" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::KeyLoad()
{
	cout << "Show Key In The File:" << endl << endl;
	cout << "<File> - File with the key" << endl << endl;
}

void HelpNow::KeyGenerate()
{
	cout << "Generate Key:" << endl << endl;
	cout << "<Output> - Saving key this file" << endl << endl;
	cout << "<Length> - Key Length" << endl << endl;
}

void HelpNow::KeySet()
{
	cout << "Setting Key:" << endl << endl;
	cout << "<String> - Encryption string in the key" << endl << endl;
	cout << "<Output> - Saving key this file" << endl << endl;
}

void HelpNow::OtherPack()
{
	cout << "Pack Other File:" << endl << endl;
	cout << "<FileName> - File for pack" << endl << endl;
	cout << "<FileOut> -  Output filename" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::OtherRead()
{
	cout << "Read Other File:" << endl << endl;
	cout << "<FileName> - File for read" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::OtherUnpack()
{
	cout << "Read Other File:" << endl << endl;
	cout << "<FileName> - File for read" << endl << endl;
	cout << "<Key File> - File with the key for the archive" << endl << endl;
}

void HelpNow::GenerateReplace()
{
	cout << "Replace Files for Pack.bin:" << endl << endl;
	cout << "<Dir> - Directory to replace" << endl << endl;
	//cout << "<DataDir> - FileList to dirs" << endl << endl;
	cout << "<OutDir> OutPut file setting" << endl << endl;
}
