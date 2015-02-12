#ifndef INPUTPARSER_H
#define INPUTPARSER_H
//*************************************************************************//
// InputParser.h - Provides parsing for input arguments                    //
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
* The InputParse class parses the arguments and stores the options needed for each run.
*
*/
#include <string>
#include <vector>
#include <array>
#include <bitset>
class InputParser {
	using String = std::string;
	using Patterns = std::vector < String > ;
	using Arguments = Patterns;
	using ArgumentsIter = const Patterns::const_iterator;

	public:
		void init( const Arguments& cmdLineArgs );
		void setSearchText( const String& searchText );
		void setSearchPatterns( Patterns patterns );
		String getSearchPath() const;
		String getSearchText() const;
		Patterns getPatterns() const;
		std::bitset<3> getRunRequirements();

	private:
		// run requirements are stored in bit combination. Stored in the format SearchNeeded | ShowDuplicates | Recursive
		// Vary from 000 (Nothing needed) to 111 (Every option needed) for the run
		std::bitset<3> runRequirements_;
		String searchPath_;
		String searchText_;
		Patterns searchPatterns_;

};
#endif