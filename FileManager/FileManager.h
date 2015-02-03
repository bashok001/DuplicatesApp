#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include "../DataStore/FileDataStore.h"

class FileManager {
	using FileCatalogIter = FileDataStore::FileCatalogIter;
	using String = std::string;
	using Patterns = std::vector < String > ;
	using Directory = String;
	using File = String;
	using DirectoryList = std::vector < Directory > ;
	using FileList = std::vector < File > ;

	public:
		FileManager( const String& path,const String& filePattern,bool recursiveSearch );

		FileManager( const String& path,const String& filePattern ) {
			FileManager( path,filePattern,false );
		};

		FileManager( const String& path ) {
			FileManager( path,"*.*" );
		};
		
		FileManager() {
			FileManager( ".");
		};

		void addPattern( const String& pattern );
		inline DirectoryList getSearchSpace() { return directoryList_; };
		inline Patterns getSearchPatterns() { return patterns_; };

#ifdef TEST_ENV
		void dump();
#endif

	private:
		Patterns patterns_;
		DirectoryList directoryList_;
		String searchPath_;
		void walkThrough( const String& dirName,bool recursiveSearch );
};

#endif