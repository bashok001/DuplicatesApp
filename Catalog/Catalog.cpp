//*************************************************************************//
// Catalog.cpp - Implementation for operational support for storage and    //
//				cataloging                                                 //
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
*/

#include <iostream>
#include <fstream>
#include <regex>
#include "Catalog.h"
#include "../FileSystem/FileSystem.h"

// Creates the backing store by storing file names and paths
FileDataStore& Catalog::createFileCatalog() {
	for( auto directory : Catalog::fileManager_.getSearchSpace() ) {
		for( auto pattern : Catalog::fileManager_.getSearchPatterns() ) {
			Catalog::FileList files = FileSystem::Directory::getFiles( directory,pattern );
			for( auto file : files ) {
				fileCatalog_.put( directory,file );
			}
		}
	}
	return fileCatalog_;
}

// Returns the list of duplicate files in the store
FileDataStore::FileCatalog Catalog::identifyDupFileSet() {
	FileDataStore::FileCatalog uniqueFileCatalog;
	for( FileDataStore::FileCatalogIter fci = fileCatalog_.begin(); fci != fileCatalog_.end(); fci++ ) {
		if( ( fci->second ).size() > 1 ) {
			uniqueFileCatalog.insert( std::pair<std::string,FileDataStore::FilePathSetIterList>( fci->first,fci->second ) );
		}
	}
	return uniqueFileCatalog;
}

// Search all the files in the catalog for search phrase
FileDataStore::ResultList Catalog::searchCatalog( const String& searchText ) {
	FileDataStore::ResultList resultList;
	for( FileDataStore::FileCatalogIter fci = fileCatalog_.begin(); fci != fileCatalog_.end(); fci++ ) {
		FileDataStore::ResultList fileList = fileCatalog_.get( fci->first );
		for( auto file : fileList ) {
			FileSystem::File outTestFile( file );
			outTestFile.open( FileSystem::File::in );
			if( outTestFile.isGood() ) {
				size_t pos = outTestFile.readAll().find( searchText );
				if( pos != std::string::npos ) {
					resultList.push_back( file );
				}
			}
		}
	}
	fileManager_.reInitializePatterns();
	return resultList;
}

// Search the files matching a given pattern and containing the search phrase
FileDataStore::ResultList Catalog::limitedCatalogSearch( const String& searchText ) {
	FileDataStore::ResultList resultList; 
	for( auto pattern : Catalog::fileManager_.getSearchPatterns() ) {
		transformToRegex( pattern );
		std::regex patternExpr( pattern );
		for( FileDataStore::FileCatalogIter fci = fileCatalog_.begin(); fci != fileCatalog_.end(); fci++ ) {
			std::string fileName( fci->first );
			if( std::regex_match( fileName,patternExpr ) ) {
				FileDataStore::ResultList fileList = fileCatalog_.get( fci->first );
				for( auto file : fileList ) {
					FileSystem::File outTestFile( file );
					outTestFile.open( FileSystem::File::in );
					if( outTestFile.isGood() ) {
						size_t pos = outTestFile.readAll().find( searchText );
						if( pos != std::string::npos ) {
							resultList.push_back( file );
						}
					}
				}
			}
		}
	}
	fileManager_.reInitializePatterns();
	resultList.sort();
	resultList.unique();
	return resultList;
}

// Transforms given search string pattern to regex pattern
void Catalog::transformToRegex( String& filePattern ) {
	replaceAll( filePattern,"*","(.*)" );
	replaceAll( filePattern,"?","(.?)" );
}

// Replaced 'from' to 'to' in given string, str
void Catalog::replaceAll( std::string& str,const std::string& from,const std::string& to ) {
	if( from.empty() )
		return;
	size_t start_pos = 0;
	while( ( start_pos = str.find( from,start_pos ) ) != std::string::npos ) {
		str.replace( start_pos,from.length(),to );
		start_pos += to.length();
	}
}


//---------------------------TEST STUB--------------------------
#ifdef TEST_CATALOG
#define SUCCESS 1
#define FAIL 0

int main() {
	int TEST_SUCCESS = 1;
	std::cout << "Testing Catalog Initiated \n";
	FileDataStore fds;
	FileManager fileManager( fds.getFilePathSet() );
	fileManager.addPattern( ".*" );
	Catalog catalog( fileManager,fds );

	catalog.createFileCatalog();
	fds.dump();

	for( auto file : catalog.identifyDupFileSet() ) {
		std::cout << " \n \n" << file.first << "\n";
	}

	for( auto file : catalog.searchCatalog( "ashok" ) ) {
		std::cout << " \n \n FileMatch: " << file << "\n";
	}

	fileManager.addPattern( "*.cpp" );

	for( auto file : catalog.limitedCatalogSearch( "ashok" ) ) {
		std::cout << " \n \nNew FileMatch: " << file << "\n";
	}

	fileManager.addPattern( "*.?pp" );
	fileManager.addPattern( "*.h" );

	for( auto file : catalog.limitedCatalogSearch( "ashok" ) ) {
		std::cout << " \n \nSecond New FileMatch: " << file << "\n";
	}
	return 0;
}
#endif