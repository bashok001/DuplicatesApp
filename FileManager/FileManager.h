#ifndef FILEMANAGER_H
#define FILEMANAGER_H
//*************************************************************************//
// FileManager.h - Provides operations wrapper on FileSystem in formats    //
//					needed by this app                                     //
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
* The FileManager class provides a wrapper around filesystem operations and work with communication between datastore, catalog and filesystem
* It also provides contextual storage for search patterns, directories identified for analysis and searchpath
*
*/

#include <vector>
#include "../DataStore/FileDataStore.h"
#include "../FileSystem/FileSystem.h"

class FileManager {
	using FileCatalogIter = FileDataStore::FileCatalogIter;
	using String = std::string;
	using Patterns = std::vector < String > ;
	using Directory = String;
	using File = String;
	using DirectoryList = std::vector < Directory > ;
	using FileList = std::vector < File > ;

	public:
	FileManager( const String& path,const String& filePattern,bool recursiveSearch,FileDataStore::FilePathSet filePathSet );

	FileManager( const String& path,const String& filePattern,FileDataStore::FilePathSet filePathSet ) :FileManager( path,filePattern,false,filePathSet ) {};

	FileManager( const String& path,FileDataStore::FilePathSet filePathSet ) :FileManager( path,"*.*",filePathSet ) {};

	FileManager( FileDataStore::FilePathSet  filePathSet ) :FileManager( FileSystem::Directory::getCurrentDirectory(),filePathSet ) {};

	void addPattern( const String& pattern );
	inline FileDataStore::FilePathSet getSearchSpace() { return filePathSet_; };
	inline Patterns getSearchPatterns() { return patterns_; };
	void FileManager::reInitializePatterns();

#ifdef TEST_ENV
	void dump();
#endif

	private:
	Patterns patterns_;
	FileDataStore::FilePathSet filePathSet_;
	String searchPath_;
	void walkThrough( const String& dirName,bool recursiveSearch );
};

#endif