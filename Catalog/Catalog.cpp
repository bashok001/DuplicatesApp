#include <iostream>
#include <fstream>
#include "Catalog.h"
#include "../FileSystem/FileSystem.h"

FileDataStore& Catalog::createFileCatalog() {
	for( auto directory : Catalog::fileManager_.getSearchSpace() ) {
		for( auto pattern : Catalog::fileManager_.getSearchPatterns() ) {
			Catalog::FileList files = FileSystem::Directory::getFiles( directory,pattern );
			for( auto file : files )
				fileCatalog_.put( directory,file );
		}
	}
	return fileCatalog_;
}

FileDataStore::FileCatalog Catalog::identifyDupFileSet() {
	FileDataStore::FileCatalog uniqueFileCatalog;
	for( FileDataStore::FileCatalogIter fci = fileCatalog_.begin(); fci != fileCatalog_.end(); fci++ ) {
		if( ( fci->second ).size() > 1 )
			uniqueFileCatalog.insert( std::pair<std::string,FileDataStore::FilePathSetIterList>( fci->first,fci->second ) );
	}
	return uniqueFileCatalog;
}

FileDataStore::ResultList Catalog::searchCatalog( const String& searchText ) {
	FileDataStore::ResultList resultList;
	for( FileDataStore::FileCatalogIter fci = fileCatalog_.begin(); fci != fileCatalog_.end(); fci++ ) {
		FileDataStore::ResultList fileList = fileCatalog_.get( fci->first );
		for( auto file : fileList ) {
			FileSystem::File outTestFile( file );
			outTestFile.open( FileSystem::File::in );
			if( outTestFile.isGood() ) {
				size_t pos=outTestFile.readAll().find( searchText );
				if( pos != std::string::npos )
					resultList.push_back(file);
			}
			
		}
	}
	return resultList;
}

#ifdef TEST_CATALOG
#define SUCCESS 1
#define FAIL 0

int main() {
	int TEST_SUCCESS = 1;
	std::cout << "Testing Catalog Initiated \n";
	FileDataStore fds;
	//FileManager fileManager( fds.getFilePathSet() );
	FileManager fileManager( "","",true,fds.getFilePathSet() );
	fileManager.addPattern( ".tlog" );
	
	Catalog catalog( fileManager,fds );

	catalog.createFileCatalog();
	fds.dump();
	
	for( auto file : catalog.identifyDupFileSet() ) {
		std::cout << " \n \n" << file.first << "\n";
	}

	for( auto file : catalog.searchCatalog("ashok") ) {
		std::cout << " \n \n" << file << "\n";
	}

	return 0;
}
#endif