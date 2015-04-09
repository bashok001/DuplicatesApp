#include "DataStore.h"

void DataStore::save(const std::string& fileName, const std::string& path)
{

	if (store.count(fileName) == 0){

		std::pair<DataStore::PathIter,bool> ret=paths.insert(path);
		ListOfIters newListIter;
		newListIter.push_back(ret.first);
		store[fileName] = newListIter;

	}
	else{

		std::pair<DataStore::PathIter, bool> retIt = paths.insert(path);
		Store::iterator storeIter = store.find(fileName);
		storeIter->second.push_back(retIt.first);
	
	}

};