#ifndef CATALOG_H
#define CATALOG_H

#include "../DataStore/FileDataStore.h"
#include "../FileManager/FileManager.h"

class Catalog {
	using String = std::string;
	using File = String;
	using FileList = std::vector < File > ;

	public:
	Catalog( FileManager& fileManager,FileDataStore& fileCatalog ) : fileManager_( fileManager ),fileCatalog_( fileCatalog ) {};
	FileDataStore& createFileCatalog();
	FileDataStore::FileCatalog identifyDupFileSet();
	FileDataStore& getCatalog() { return fileCatalog_; };
	FileDataStore::ResultList searchCatalog( const String& searchText );
	FileDataStore::ResultList reSearchCatalog( const String& searchText );
	

	private:
	FileDataStore& fileCatalog_;
	FileManager& fileManager_;
	
	void replaceAll( std::string& str,const std::string& from,const std::string& to );
	void transformToRegex( std::string& filePattern );
	
};
#endif