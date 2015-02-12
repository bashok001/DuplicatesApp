//*************************************************************************//
// FileManager.cpp - Implementation of wrapper on Filesystem for Duplicates//
//					 App												   //
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
#include "FileManager.h"

// Construtor that initiates the operations of FileManager: Stores all the contextual information for this run along with identified set of directories
// that are going to be analysed.
FileManager::FileManager( const String& path,const String& filePattern,bool recursiveSearch,FileDataStore::FilePathSet filePathSet ) {
	filePathSet_ = filePathSet;
	searchPath_ = path;
	if( searchPath_ == "" ) {
		searchPath_ = FileSystem::Directory::getCurrentDirectory();
	}
	if( filePattern == "" ) {
		patterns_.push_back( "*.*" );
	} else {
		patterns_.push_back( filePattern );
	}
	walkThrough( searchPath_,recursiveSearch );
}

// Recursively (Depending on bool recursiveSearch param) walks through directories and creates the search space
void FileManager::walkThrough( const String& path,bool recursiveSearch ) {
	FileManager::filePathSet_.insert( FileSystem::Path::getFullFileSpec( path ) );
	if( recursiveSearch ) {
		FileManager::DirectoryList directoryList = FileSystem::Directory::getDirectories( path );
		if( std::find( directoryList.begin(),directoryList.end(),"." ) != directoryList.end() ) {
			directoryList.erase( std::find( directoryList.begin(),directoryList.end(),"." ) );
		}
		if( std::find( directoryList.begin(),directoryList.end(),".." ) != directoryList.end() ) {
			directoryList.erase( std::find( directoryList.begin(),directoryList.end(),".." ) );
		}
		if( directoryList.size() == 0 ) {
			return;
		}
		for( auto directory : directoryList ) {
			FileSystem::Directory::setCurrentDirectory( path );
			FileManager::filePathSet_.insert( FileSystem::Path::getFullFileSpec( directory ) );
			walkThrough( FileSystem::Path::getFullFileSpec( directory ),true );
		}
	}
}

// Stores the pattern information in a vector
void FileManager::addPattern( const String& pattern ) {
	if( patterns_.size() == 1 && patterns_[ 0 ] == "*.*" ) {
		patterns_.pop_back();
	}
	if( pattern.find( "." ) == 0 ) {
		patterns_.push_back( "*" + pattern );
	} else {
		patterns_.push_back( pattern );
	}
}

// Reinitialize all the parameters
void FileManager::reInitializePatterns() {
	patterns_.erase( patterns_.begin(),patterns_.end() );
	patterns_.push_back( "*.*" );
}


//-----------------------------------TEST STUB--------------------
#ifdef TEST_FILEMANAGER
int main() {
	std::cout << "Testing Filemanager initiated";
	return 0;
}
#endif