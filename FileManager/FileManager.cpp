#include "FileManager.h"
#include <iostream>
#include "../FileSystem/FileSystem.h"
#include "../Catalog/Catalog.h"

FileManager::FileManager( const String& path,const String& filePattern,bool recursiveSearch ) {
	searchPath_ = path;
	patterns_.push_back( filePattern );
	walkThrough( path,recursiveSearch );
}

void FileManager::walkThrough( const String& path,bool recursiveSearch ) {
	if( !recursiveSearch ) {
		FileManager::directoryList_.push_back( path );
	} else {
		FileManager::DirectoryList directoryList = FileSystem::Directory::getDirectories( path );
		directoryList.erase( std::find( directoryList.begin(),directoryList.end(),"." ) );
		directoryList.erase( std::find( directoryList.begin(),directoryList.end(),".." ) );

		if( directoryList.size() == 0 ) {
			return;
		}

		for( auto directory : directoryList ) {
			FileManager::directoryList_.push_back( directory );
			walkThrough( directory,true );
		}
	}
}

void FileManager::addPattern( const String& pattern ) {
	if( patterns_.size() == 1 && patterns_[ 0 ] == "*.*" ) {
		patterns_.pop_back();
	}
	patterns_.push_back( pattern );
}

#ifdef TEST_FILEMANAGER
int main() {
	std::cout << "Testing Filemanager initiated";
}
#endif