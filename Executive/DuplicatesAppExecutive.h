#ifndef DUPLICATESAPPEXECUTIVE_H
#define DUPLICATESAPPEXECUTIVE_H
//*************************************************************************//
// DuplicatesAppExecutive.h - Executive for the DuplicatesApp. Orders and  //
//							  Co-ordinates the functionality of all modules//
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
*/
#include "../Catalog/Catalog.h"
#include "../FileManager/FileManager.h"
#include "../Display/Display.h"
#include "../InputParser/InputParser.h"

class DuplicatesAppExecutive {

	public:
		void DuplicatesAppExecutive::refineSearch( Catalog& catalog );
		void DuplicatesAppExecutive::noSwitchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::noSwitchRecursiveCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::noRecursiveDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::recursiveDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec, Catalog fileCatalog );
		void DuplicatesAppExecutive::noSwitchSearchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::recursiveSearchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::noRecursiveSearchDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
		void DuplicatesAppExecutive::recursiveSearchDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog fileCatalog );
	
};
#endif // !DUPLICATESAPPEXECUTIVE_H
