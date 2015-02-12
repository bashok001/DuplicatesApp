#include <iostream>
#include "FileManager.h"


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
	if( recursiveSearch ) {
		FileManager::filePathSet_.insert( searchPath_ );
	}
}

void FileManager::walkThrough( const String& path,bool recursiveSearch ) {
	if( !recursiveSearch ) {
		FileManager::filePathSet_.insert( path );
	} else {
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

void FileManager::reInitializePatterns() {
	patterns_.erase( patterns_.begin(),patterns_.end() );
	patterns_.push_back( "*.*" );
}

#ifdef TEST_FILEMANAGER
int main() {
	std::cout << "Testing Filemanager initiated";
	return 0;
}
#endif