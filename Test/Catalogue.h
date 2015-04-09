#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "DataStore.h"

class Catalogue
{

public:
	DataStore *dataStore;
	bool  recurse;
	std::vector<std::string> patterns;

public:
	Catalogue();
	~Catalogue();
	void storeFile(std::string path);
	void isRecurse(bool val);
	void addPattern(std::string pattern);
};


#endif