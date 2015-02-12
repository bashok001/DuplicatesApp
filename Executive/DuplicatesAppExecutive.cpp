#include "DuplicatesAppExecutive.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "../DataStore/FileDataStore.h"

int main( int argc,char* argv[] ) {
	std::vector<std::string> args( argv + 1,argv + argc + !argc );
	InputParser ip;
	ip.init( args );
	DuplicatesAppExecutive dupAppExec;
	FileDataStore fds;
	Display display;
	FileManager fm( fds.getFilePathSet() );
	Catalog catalog( fm,fds );
	switch( ip.getRunRequirements().to_ulong() ) {
		case 0:
			dupAppExec.noSwitchCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 1:
			dupAppExec.noSwitchRecursiveCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 2:
			dupAppExec.noRecursiveDuplicateCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 3:
			dupAppExec.recursiveDuplicateCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 4:
			dupAppExec.noSwitchSearchCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 5:
			dupAppExec.recursiveSearchCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 6:
			dupAppExec.noRecursiveSearchDuplicateCall( fds,display,ip,dupAppExec,catalog );
			break;
		case 7:
			dupAppExec.recursiveSearchDuplicateCall( fds,display,ip,dupAppExec,catalog );
			break;
	}
	dupAppExec.refineSearch( catalog );
}

void DuplicatesAppExecutive::refineSearch( Catalog& catalog ) {
	std::string newSearchPhrase;
	std::string newSearchPatterns;
	InputParser ip;
	Display display;
	catalog.getFileManager().reInitializePatterns();

	std::cout << "Enter new search criteria " << "\n";
	std::cout << "------------------------- " << "\n";
	std::cout << "Enter new search phrase (Return key will Exit): ";
	std::getline( std::cin,newSearchPhrase );
	if( newSearchPhrase == "" ) {
		std::cout << "See you Again. Bye!\n";
		exit(0);
	}
	std::cout << "Enter new search pattern(s) (Default: *.*): ";
	std::getline( std::cin,newSearchPatterns );
	std::istringstream buf( newSearchPatterns );
	std::istream_iterator<std::string> beg( buf ),end;
	std::vector<std::string> newPatterns( beg,end );

	for( auto pattern : newPatterns ) {
		catalog.getFileManager().addPattern( pattern );
	}

	display.showSearchResults( newSearchPhrase,catalog.limitedCatalogSearch( newSearchPhrase ) );
	refineSearch( catalog );
}

void DuplicatesAppExecutive::recursiveDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",true,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showDuplicates( catalog.identifyDupFileSet() );
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}


void DuplicatesAppExecutive::noSwitchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",false,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}

void DuplicatesAppExecutive::noSwitchRecursiveCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",true,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}

void DuplicatesAppExecutive::noRecursiveDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",false,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}


void DuplicatesAppExecutive::noSwitchSearchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",false,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSearchResults( ip.getSearchText(),catalog.searchCatalog( ip.getSearchText() ) );
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}

void DuplicatesAppExecutive::recursiveSearchCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",true,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSearchResults( ip.getSearchText(),catalog.searchCatalog( ip.getSearchText() ) );
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}

void DuplicatesAppExecutive::noRecursiveSearchDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",false,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSearchResults( ip.getSearchText(),catalog.searchCatalog( ip.getSearchText() ) );
	display.showDuplicates( catalog.identifyDupFileSet() );
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}

void DuplicatesAppExecutive::recursiveSearchDuplicateCall( FileDataStore fds,Display display,InputParser ip,DuplicatesAppExecutive dupAppExec,Catalog catalog ) {
	FileManager fileManager( ip.getSearchPath(),"*.*",true,fds.getFilePathSet() );
	for( auto pattern : ip.getPatterns() ) {
		fileManager.addPattern( pattern );
	}
	catalog.setCatalog( fds );
	catalog.setFileManager( fileManager );
	catalog.createFileCatalog();
	display.showSearchResults( ip.getSearchText(),catalog.searchCatalog( ip.getSearchText() ) );
	display.showDuplicates( catalog.identifyDupFileSet() );
	display.showSummary( catalog.getCatalog().getFilePathSet().size(),catalog.getCatalog().size() );
}