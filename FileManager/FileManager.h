#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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