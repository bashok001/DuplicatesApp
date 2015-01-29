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
	using FilePathSetIterList = std::list<FilePathSetIter>;
	using FileCatalog = std::map < FileName, FilePathSetIterList >;
	using FileCatalogIter = FileCatalog::iterator;
	using ResultList = std::list < FQPN >;
	using FilePathSetInsertReturn = std::pair<FilePathSetIter, bool>;
	using FileCatalogInsertReturn = std::pair <FileCatalogIter , bool> ;

	public:
		ResultList get(const FileName& fileName);
		void put(const FQPN& fqpn);
		void put(const FilePath& filePath, const FileName& fileName);
		int size();
		void flush();
		
		FileCatalogIter begin();
		FileCatalogIter end();
	
		//DELETE THIS API CALL
		void fullSizeDet();
	private:
		FileCatalog fileCatalog;
		FilePathSet filePaths;
		FilePathSetIter getFilePathSetIter(const FilePath& filePath);
		void fqpnSplitter(const FQPN& fqpn, const FilePath& filePath, const FileName& fileName);

};
#endif