#ifndef DUPLICATESAPPEXECUTIVE_H
#define DUPLICATESAPPEXECUTIVE_H
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
		//Catalog setCatalog( Catalog& catalog ) { catalog_ = catalog; }

	private:
		//Catalog& catalog_;

};
#endif // !DUPLICATESAPPEXECUTIVE_H
