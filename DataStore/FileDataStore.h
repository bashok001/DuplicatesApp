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
	using ResultList = std::list < FQPN > ;
	using FilePathSetInsertReturn = std::pair < FilePathSetIter,bool > ;

	public:
		using FilePathSetIterList = std::list < FilePathSetIter > ;
		using FileCatalog = std::map < FileName,FilePathSetIterList > ;
		using FileCatalogIter = FileCatalog::iterator;
		using FileCatalogInsertReturn = std::pair < FileCatalogIter,bool > ;

		ResultList get( const FileName& fileName );
		void put( const FilePath& filePath,const FileName& fileName );
		int size();
		void flush();

#ifdef TEST_ENV
		void dump();
#endif
		FileCatalogIter begin();
		FileCatalogIter end();

	private:
		FileCatalog fileCatalog_;
		FilePathSet filePaths_;
		FilePathSetIter getFilePathSetIter( const FilePath& filePath );
};
#endif