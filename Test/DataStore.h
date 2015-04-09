#ifndef DATASTORE_H
#define DATASTORE_H

#include <set>
#include <list>
#include <map>
#include <string>
#include <vector>

class DataStore{

	public:
		DataStore(){};
		~DataStore(){};
		using Path = std::string;
		using Paths = std::set < Path >;
		using PathIter = Paths::iterator;
		using ListOfIters = std::list < PathIter >;
		using File = std::string;
		using Store = std::map < File, ListOfIters >;
		using iterator = Store::iterator;

		void save(const std::string& fileName, const std::string& path);
		iterator begin(){ return store.begin(); }
		iterator end(){ return store.end(); }
		void save(const std::string& filespec);

	private:
		Store store;
		Paths paths;

	};

#endif