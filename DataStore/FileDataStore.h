#ifndef FILEDATASTORE_H
#define FILEDATASTORE_H
//*************************************************************************//
// FileDataStore.h - Provides storage and cataloging options               //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyleft © Ashok Bommisetti, 2015                                       //
// No guarantees on anything; But free to modify, copy and distribute      //
// ----------------------------------------------------------------------- //
// Author:      Ashok Bommisetti							               //
// First Published (mm-dd-yyyy): 02-11-2015 			                   //
//*************************************************************************//

/*
* This is a part of Duplicates App, designed and developed to search and find duplicate files in the system.
*
* Module Operations:
* ==================
* 
* The FileDataStore class supports storage for filenames and file paths. 
*
* get: To lookup all the files in the store with the specified name
* put: To store file name and multiple file paths where the file can be found along with preserving the relationship between the two.
* getFilePathSet : Provides access to directories in the store
* size: Provides infomation about the size of store 
* flush: Flush the store and start brand new.
* begin() and end() : Provide access to the actual datastructure of the store. Use begin and end to iterate through the store.
* dump(): This API is available only in test environment. This will display the entire store information on the console.
*
*/
#include <string>
#include <map>
#include <list>
#include <set>

class FileDataStore {
	using FilePath = std::string;
	using FileName = std::string;
	using FullyQualifiedFileName = std::string;
	using FQPN = FullyQualifiedFileName;

	public:
		using FilePathSet = std::set < FilePath >;
		using FilePathSetIter = FilePathSet::iterator;
		using FilePathSetInsertReturn = std::pair < FilePathSetIter,bool >;
		using FilePathSetIterList = std::list < FilePathSetIter > ;
		using FileCatalog = std::map < FileName,FilePathSetIterList > ;
		using FileCatalogIter = FileCatalog::iterator;
		using FileCatalogInsertReturn = std::pair < FileCatalogIter,bool > ;
		using ResultList = std::list < FQPN >;

		ResultList get( const FileName& fileName );
		void put( const FilePath& filePath,const FileName& fileName );
		FilePathSet getFilePathSet() { return filePaths_; };
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