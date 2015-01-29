#ifndef FILEDATASTORE_H
#define FILEDATASTORE_H

#include <string>
#include <map>
#include <list>
#include <set>

class FileDataStore {
	using FilePath = std::string;
	using FileName = std::string;
	using FilePathSet = std::set < FilePath > ;
	using FilePathSetIter = FilePathSet::iterator;
	using FilePathSetIterList = std::list<FilePathSetIter>;
	using FileCatalog = std::map < FileName, FilePathSetIterList >;
	using FileCatalogIter = FileCatalog::iterator;
	
	public:

	private:
		FileCatalog fileCatalog;
		FilePathSet filePaths;

};
#endif