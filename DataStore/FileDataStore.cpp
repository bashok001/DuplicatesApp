#include "FileDataStore.h"
#include <iostream>


//FileDataStore::ResultList FileDataStore::get(const FileDataStore::FileName& fileName) {
//
//}

//void FileDataStore::put(const FileDataStore::FQPN& fqpn) {
//	FileDataStore::FileName fileName;
//	FileDataStore::FilePath filePath;
//	FileDataStore::fqpnSplitter(fqpn, fileName, filePath);
//	FileDataStore::put(filePath, fileName);
//}

void FileDataStore::put(const FileDataStore::FilePath& filePath, const FileDataStore::FileName& fileName) {
	FileDataStore::FilePathSetInsertReturn fpSetReturn = FileDataStore::filePaths.insert(filePath);

	if (FileDataStore::fileCatalog.count(fileName) > 0) {
		if (fpSetReturn.second == false) {
			std::cout << "Repeated File Encountered in Insertion Process \n";
			std::cout << FileDataStore::fileCatalog.size() << "\n";
		}
		else {
			std::cout << "Condition Two: FileName Found PathName Didnt\n";
			//FileDataStore::FileCatalogIter fileCatalogEntry = FileDataStore::fileCatalog.find(filePath);
			FileDataStore::FilePathSetIterList asd = FileDataStore::fileCatalog[filePath];
			asd.push_back(fpSetReturn.first);
			std::cout << FileDataStore::fileCatalog.size() << "\n";
			//fileCatalogEntry->second;
			/*push_back(fpSetReturn.first); */
		}
	}
	else {
		std::cout << "Condition Three: New File\n";
		FileDataStore::FilePathSetIterList newFilePathsList;
		newFilePathsList.push_back(fpSetReturn.first);
		FileDataStore::fileCatalog.insert(std::pair<FileName, FilePathSetIterList>(fileName, newFilePathsList));
		std::cout << FileDataStore::fileCatalog.size() << "\n";
	}

}

int FileDataStore::size() {
	return FileDataStore::fileCatalog.size();
}

void FileDataStore::flush() {
	FileDataStore::filePaths.clear();
	FileDataStore::fileCatalog.clear();
}

FileDataStore::FileCatalogIter FileDataStore::begin() {
	return FileDataStore::fileCatalog.begin();
}

FileDataStore::FileCatalogIter FileDataStore::end() {
	return FileDataStore::fileCatalog.end();
}

FileDataStore::FilePathSetIter FileDataStore::getFilePathSetIter(const FileDataStore::FilePath& filePath) {
	return FileDataStore::filePaths.find(filePath);
}

//DELETE THIS
void FileDataStore::fullSizeDet() {
	std::cout << "Catalog Size is: " <<FileDataStore::fileCatalog.size() << "\n";
	std::cout << "PathSet Size is: " << FileDataStore::filePaths.size() << "\n";
}

#ifdef TEST_DATASTORE
#define SUCCESS 1
#define FAIL 0
int main() {
	int TEST_SUCCESS = 1;
	
	std::cout << "Testing DataStore Initiated \n";
	FileDataStore fds;
	
	if (fds.size() == 0) {
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	}
	else {
		TEST_SUCCESS = TEST_SUCCESS*FAIL;
	}
	
	fds.put("C", "ASHOK");
	fds.put("C", "ASHOK2");
	fds.put("C", "ASHOK3"); 
	fds.put("C", "ASHOK4"); 
	fds.put("C", "ASHOK4");
	fds.put("C", "ASHOK5");
	fds.put("D", "ASHOK5");

	fds.fullSizeDet();
	if (fds.size() == 5){
		
		TEST_SUCCESS = TEST_SUCCESS*SUCCESS;
	}

	
	std::cout << ((TEST_SUCCESS) ? "All Tests Passed\n" : "Something Failed\n");
	return TEST_SUCCESS;
}
#endif