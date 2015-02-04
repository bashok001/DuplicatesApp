#include <iostream>
#include "FileManager.h"
#include "../FileSystem/FileSystem.h"

FileManager::FileManager( const String& path,const String& filePattern,bool recursiveSearch ) {
#ifdef TEST_ENV
	std::cout << "FileManager walkthru with " << path << " and " << filePattern << " and " << recursiveSearch << "\n";
#endif

	searchPath_ = path;
	patterns_.push_back( filePattern );
	walkThrough( path,recursiveSearch);
	if( recursiveSearch ) {
		FileManager::directoryList_.push_back( path );
	}
#ifdef TEST_ENV
	for( auto path : directoryList_ )
		std::cout << "From directory list " << path << "\n";
#endif

}

void FileManager::walkThrough( const String& path,bool recursiveSearch) {
	if( !recursiveSearch ) {
		FileManager::directoryList_.push_back( path );
	} else {
		std::cout << "Path being Explored: ************* " << path << "\n";
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
			FileManager::directoryList_.push_back( FileSystem::Path::getFullFileSpec( directory ) );
			std::cout << "Pushed " << directory << " into directoryList \n";
			walkThrough( FileSystem::Path::getFullFileSpec( directory ),true );
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