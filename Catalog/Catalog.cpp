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
		if( ( fci->second ).size() > 1 ) {
			uniqueFileCatalog.insert( std::pair<std::string,FileDataStore::FilePathSetIterList>( fci->first,fci->second ) );
		}
	}

}