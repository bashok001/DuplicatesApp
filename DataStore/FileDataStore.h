#ifndef FILEDATASTORE_H
#define FILEDATASTORE_H

#include <string>
#include <map>
#include <list>
#include <set>

class FileDataStore {
	using FilePath = std::string;
	using FileName = std::string;
	using FullyQualifiedFileName = std::string;
	using FQPN = FullyQualifiedFileName;
	using FilePathSet = std::set < FilePath > ;
	using FilePathSetIter = FilePathSet::iterator;
	using FilePathSetIterList = std::list < FilePathSetIter > ;
	using FileCatalog = std::map < FileName, FilePathSetIterList > ;
	using FileCatalogIter = FileCatalog::iterator;
	using ResultList = std::list < FQPN > ;
	using FilePathSetInsertReturn = std::pair < FilePathSetIter, bool > ;
	using FileCatalogInsertReturn = std::pair < FileCatalogIter, bool > ;

public:
	ResultList get(const FileName& fileName);
	void put(const FilePath& filePath, const FileName& fileName);
	int size();
	void flush();
#ifdef TEST_ENV
	void dump();
#endif
	FileCatalogIter begin();
	FileCatalogIter end();

private:
	FileCatalog fileCatalog;
	FilePathSet filePaths;
	FilePathSetIter getFilePathSetIter(const FilePath& filePath);


};
#endif