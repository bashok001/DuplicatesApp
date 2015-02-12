#include "InputParser.h"
#include <iostream>
#include "../FileSystem/FileSystem.h"
//*************************************************************************//
// InputParser.cpp - Implementation for argument parser                    //
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

// Takes command line arguments in a vector to parse them out and sets the parameters for the run.
// Sets up Search Text, Search Path, Search Patterns and runRequirements bitset
void InputParser::init( const InputParser::Arguments& cmdLineArgs ) {
	runRequirements_.reset();
	if( cmdLineArgs.size() == 0 ) {
		searchPath_ = FileSystem::Directory::getCurrentDirectory();
	} else {
		if( cmdLineArgs[ 0 ].find( "/" ) != std::string::npos ) {
			std::cout << "If you are using relative paths, please use \\ instead of / in the arguments.\n";
			std::cout << "First argument is not a path. Searching in current directory instead.\n";
			searchPath_ = FileSystem::Directory::getCurrentDirectory();
		} else {
			searchPath_ = cmdLineArgs[ 0 ];
		}
		auto recusiveIter = std::find( cmdLineArgs.begin(),cmdLineArgs.end(),"/s" );
		if( recusiveIter != cmdLineArgs.end() ) {
			runRequirements_.flip( 0 );
		}

		auto duplicatesIter = std::find( cmdLineArgs.begin(),cmdLineArgs.end(),"/d" );
		if( duplicatesIter != cmdLineArgs.end() ) {
			runRequirements_.flip( 1 );
		}

		auto searchIter = std::find( cmdLineArgs.begin(),cmdLineArgs.end(),"/f" );
		if( searchIter != cmdLineArgs.end() ) {
			runRequirements_.flip( 2 );
			auto searchTextIter = std::next( searchIter,1 );
			if( searchTextIter == cmdLineArgs.end() ) {
				std::cout << "Search text flag is present but text parameter is not provided. Please provide search text after /f flag. Exiting.\n";
				exit( 1 );
			}
			searchText_ = *searchTextIter;
		}

		for( auto patternIter = cmdLineArgs.begin()+1; patternIter != cmdLineArgs.end(); std::advance( patternIter,1 ) ) {
			if( patternIter != recusiveIter && patternIter != duplicatesIter && patternIter != searchIter ) {
				searchPatterns_.push_back( *patternIter );
				if( runRequirements_[ 2 ] && patternIter == std::next( searchIter,1 ) ) {
					searchPatterns_.pop_back();
				}
			}
		}
	}
}

// Returns search path for the run
InputParser::String InputParser::getSearchPath() const {
	return searchPath_;
}

// Returns search phrase specified for the run
InputParser::String InputParser::getSearchText() const {
	return searchText_;
}

// Returns search patterns specified for the run
InputParser::Patterns InputParser::getPatterns() const {
	return searchPatterns_;
}

// Return the bitmask that represents the options /f /d /s
std::bitset<3> InputParser::getRunRequirements() {
	return runRequirements_;
}

// Setter for search phrase
void InputParser::setSearchText( const String& searchText ) {
	searchText_ = searchText;
}

// Setter for search pattern vector
void InputParser::setSearchPatterns( Patterns patterns ) {
	searchPatterns_.erase( searchPatterns_.begin(),searchPatterns_.end() );
	if( patterns.size() == 0 ) {
		searchPatterns_.push_back( "*.*" );
	} else
		searchPatterns_ = patterns;
}

//-------------------------TEST STUB-------------------------
#ifdef TEST_INPUTPARSER
int main() {
	std::cout << "Testing InputParser Initiated \n";
	return 0;
}
#endif