#ifndef CATALOG_H
#define CATALOG_H
//*************************************************************************//
// Catalog.h - Provides operational support for storage and cataloging     //
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
* The Catalog class provides operations needed to cataloging data into the FileDataStore
*
* Constructor of this object takes an instance of fileManager and fileDataStore. 
* 
* createFileCatalog: Creates the backing store by storing file names and paths.
* identifyDupFileSet: Returns the list of duplicate files in the store
* searchCatalog : Search all the files in the catalog for search phrase
* limitedCatalogSearch: Search the files matching a given pattern and containing the search phrase.
* 
* Getters and Setters to the backing store and file manager wrapper.
*
*/

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
	FileDataStore::ResultList searchCatalog( const String& searchText );
	FileDataStore::ResultList limitedCatalogSearch( const String& searchText );
	
	FileDataStore& getCatalog() { return fileCatalog_; };
	FileManager& getFileManager() { return fileManager_; };
	void setCatalog( FileDataStore& fileCatalog ) { fileCatalog_ = fileCatalog; };
	void setFileManager( FileManager& fileManager ) { fileManager_ = fileManager; };

	private:
	FileDataStore& fileCatalog_;
	FileManager& fileManager_;	
	void replaceAll( std::string& str,const std::string& from,const std::string& to );
	void transformToRegex( std::string& filePattern );
	
};
#endif