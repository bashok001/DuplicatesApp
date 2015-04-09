#include "Catalogue.h"
#include "../FileSystemDemo/FileSystem.h"


Catalogue::Catalogue(){

	dataStore = new DataStore();
	recurse = false;
}

Catalogue::~Catalogue(){

	delete dataStore;
}

void Catalogue::storeFile(std::string path){

	if (patterns.size() == 0){
		addPattern("*.*");
	}
	
	for each (std::string pattern in patterns)
	{

		std::vector<std::string> files = FileSystem::Directory::getFiles(path, pattern);
		for each (std::string file in files)
		{
			dataStore->save(file, path);
		}

	}
	
	if (recurse){

		std::vector<std::string> dirs = FileSystem::Directory::getDirectories(path);
		for each (std::string dir in dirs)
		{
			storeFile(dir);
		}
	}
}

void Catalogue::isRecurse(bool val){
	recurse = val;
}

void Catalogue::addPattern(std::string pattern){

	patterns.push_back(pattern);
}