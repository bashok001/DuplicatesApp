#include "Display.h"
#include "iostream"
//*************************************************************************//
// Display.cpp - Implementation for display operations.                    //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// copyleft © Ashok Bommisetti, 2015                                       //
// No guarantees on anything; But free to modify, copy and distribute      //
// ----------------------------------------------------------------------- //
// Author:      Ashok Bommisetti							               //
// First Published (mm-dd-yyyy): 02-11-2015 			                   //
//*************************************************************************//

/*
* This is a part of Duplicates App, designed and developed to search and find duplicate files in the system.
*/

// Displays a short summary of the current run.
void Display::showSummary( int noOfDirectories,int noOfFiles ) {
	std::cout << "\n" << noOfFiles << " file(s) are found in " << noOfDirectories << " director(ies) for this run. \n";
}

// Provides display support for displaying duplicates in the search result
void Display::showDuplicates( FileDataStore::FileCatalog duplicatesCatalog ) {
	std::cout << "The Duplicate Entries: \n";
	std::cout << "---------------------- \n";
	if( duplicatesCatalog.size() > 0 ) {
		for( auto dupCatalogEntry : duplicatesCatalog ) {
			std::cout << dupCatalogEntry.first << "\n";
			for( auto filePath : dupCatalogEntry.second ) {
				std::cout << "\t" << *filePath << "\n";
			}
		}
	} else {
		std::cout << "No duplicate files found. \n";
	}
}

// Displays search results on the console
void Display::showSearchResults( const std::string& searchPhrase,FileDataStore::ResultList searchResults ) {
	if( searchResults.size() > 0 ) {
		std::cout << searchPhrase << " is found in: \n";
		for( auto searchResult : searchResults ) {
			std::cout << "\t" << searchResult << "\n";
		}
	} else {
		std::cout << searchPhrase << " is not found in the search space.\n";
	}
}

//-------------------<TEST STUB>---------------------
#ifdef TEST_DISPLAY
int main() {
	std::cout << "Testing Display Initiated \n";
	return 0;
}
#endif