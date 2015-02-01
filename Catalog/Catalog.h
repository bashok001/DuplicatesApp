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

	private:
		FileDataStore& fileCatalog_;
		FileManager& fileManager_;
};
#endif