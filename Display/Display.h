#ifndef DISPLAY_H
#define DISPLAY_H
//*************************************************************************//
// Display.h - Provides display options to duplicatesApp                   //
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
*
* Module Operations:
* ==================
*
* The Display class supports display operations needed for DuplicatesApp.
*
* showSummary: Displays a summary of the current run state.
* showDuplicates: Provides display support for displaying duplicates in the app.
* showSearchResults : Displays search results on the console.
*
*/
#include "../DataStore/FileDataStore.h"
#include <string>

class Display {
	public:
		void showSummary( int noOfDirectories,int noOfFiles );
		void showDuplicates( FileDataStore::FileCatalog duplicatesCatalog);
		void showSearchResults( const std::string& searchPhrase, FileDataStore::ResultList searchResults );
	private:

};
#endif