#include "FileDataStore.h"
#include <iostream>

FileDataStore::ResultList FileDataStore::get( const FileDataStore::FileName& fileName ) {
	FileDataStore::ResultList resultList;
	std::string fqpn;
	if( FileDataStore::fileCatalog_.count( fileName ) > 0 ) {
		FileDataStore::FilePathSetIterList filePathSetIterList = FileDataStore::fileCatalog_[ fileName ];
		FileDataStore::FilePathSetIter filePathSetIter;
		for( auto filePathSetIter : filePathSetIterList ) {
			fqpn = ( *filePathSetIter ).c_str() + std::string( "\\" ) + fileName;
			resultList.push_back( fqpn );
		}
	}
	return resultList;
}

void FileDataStore::put( const FileDataStore::FilePath& filePath,const FileDataStore::FileName& fileName ) {
	FileDataStore::FilePathSetInsertReturn fpSetReturn = FileDataStore::filePaths_.insert( filePath );
	if( FileDataStore::fileCatalog_.count( fileName ) > 0 ) {
		FileDataStore::FilePathSetIterList& filePathSetIterList = FileDataStore::fileCatalog_[ fileName ];
		if( fpSetReturn.second == false && std::find( filePathSetIterList.begin(),filePathSetIterList.end(),fpSetReturn.first ) != filePathSetIterList.end() ) {
			//TODO: EXCEPTION
			std::cout << "***********EXCEPTION************* \n";
		} else {
			FileDataStore::FilePathSetIterList& filePathSetIterList = FileDataStore::fileCatalog_[ fileName ];
			( filePathSetIterList ).push_back( fpSetReturn.first );
		}
	} else {
		FileDataStore::FilePathSetIterList newFilePathsList;
		newFilePathsList.push_back( fpSetReturn.first );
		FileDataStore::fileCatalog_.insert( std::pair<FileName,FilePathSetIterList>( fileName,newFilePathsList ) );
	}

}

int FileDataStore::size() {
	return FileDataStore::fileCatalog_.size();
}

void FileDataStore::flush() {
	FileDataStore::filePaths_.clear();
	FileDataStore::fileCatalog_.clear();
}

FileDataStore::FileCatalogIter FileDataStore::begin() {
	return FileDataStore::fileCatalog_.begin();
}

FileDataStore::FileCatalogIter FileDataStore::end() {
	return FileDataStore::fileCatalog_.end();
}

FileDataStore::FilePathSetIter FileDataStore::getFilePathSetIter( const FileDataStore::FilePath& filePath ) {
	return FileDataStore::filePaths_.find( filePath );
}

#ifdef TEST_ENV
void FileDataStore::dump() {
	std::cout << "Dumping data from Catalog & Paths list \n";
	for( auto fileCatalogItem : FileDataStore::fileCatalog_ ) {
		std::cout << fileCatalogItem.first << "\t";
		FileDataStore::FilePathSetIterList filePathSetIterList = FileDataStore::fileCatalog_[ fileCatalogItem.first ];

		for( auto filePathList : filePathSetIterList )
			std::cout << ( *filePathList ).c_str() << "\n" << "\t";
		std::cout << "\n";
	}

	std::cout << "\n" << "Dumping data from FilePathSet" << "\n";
	for( auto path : FileDataStore::filePaths_ )
		std::cout << path << "\n";
	
	std::cout << "\n\n\n*****Size of Catalog is: " << fileCatalog_.size() << "\n";
}
#endif

#ifdef TEST_DATASTORE
#define SUCCESS 1
#define FAIL 0
int main() {
	int TEST_SUCCESS = 1;

	std::cout << "Testing DataStore Initiated \n";
	FileDataStore fds;

	if( fds.size() == 0 ) {
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	} else {
		TEST_SUCCESS = TEST_SUCCESS*FAIL;
	}
	fds.put( "C:","ASHOK" );
	fds.put( "C:","ASHOK" );
	fds.put( "E:","ASHOK" );
	fds.put( "D:","ASHOK4" );
	fds.put( "E:","ASHOK4" );
	fds.put( "C:","ASHOK2" );
	fds.put( "C:","ASHOK3" );
	fds.put( "C:","ASHOK5" );
	fds.put( "D:","ASHOK5" );
	fds.put( "E:","ASHOK5" );
	fds.put( "F:","ASHOK5" );
	fds.put( "G:","ASHOK5" );
	if( fds.size() == 5 ) {
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	} else {
		TEST_SUCCESS = TEST_SUCCESS*FAIL;
	}
	std::list < std::string > list = fds.get( "ASHOK5" );
	if( list.size() == 5 ) {
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	} else {
		TEST_SUCCESS = TEST_SUCCESS*FAIL;
	}
	fds.dump();
	fds.flush();
	if( fds.size() == 0 ) {
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	} else {
		TEST_SUCCESS = TEST_SUCCESS*FAIL;
	}
	std::cout << ( ( TEST_SUCCESS ) ? "All Tests Passed\n" : "Something Failed\n" );
	return TEST_SUCCESS;
}
#endif