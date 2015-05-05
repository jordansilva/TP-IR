//
//  main.cpp
//  ir
//
//  Created by Jordan Silva on 08/04/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include "util/SortFile.h"
#include "index/Indexer.h"
#include "search/Searcher.h"

#define DIRECTORY "/home/jordan/documents/ir/irCollection"
#define MAPFILE "index.txt"
#define OUTPUT_DIRECTORY "./output/"

using namespace std;
using namespace boost;

const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

int main(int argc, const char * argv[]) {

	clock_t start = clock();
	cout << currentDateTime() << endl;

	cout << "Indexer 0.1" << endl;
	cout << "@author jordansilva" << endl;
	cout << "index <directory> <index> [output] \t\t -initializes the indexing of the collection"
			<< end;
	cout
			<< "search [directory] [inverted-index] [vocabulary] [documents] \t\t -initializes the search program"
			<< end;

	string command;
	string directory;
	string index;
	string extra1;
	string extra2;
	while (command != "EXIT") {
		cin << command << directory << index << extra1 << extra2;
		boost::trim(command);
		boost::trim(directory);
		boost::trim(index);
		boost::trim(extra1);
		boost::trim(extra2);
		if (command == "index") {
			if (index.empty())
				index = MAPFILE;

			if (extra1.empty())
				extra1 = OUTPUT_DIRECTORY;

			Indexer indexer(directory, index, extra1);
			SortFile sort(extra1, "file.index");
		}
		if (command == "search") {
			if (directory.empty())
				extra1 = OUTPUT_DIRECTORY;
			if ()

		}
	}

	//index


	//external sort


	//merge vocabulary
	SortFile::mergeVocabulary("file.terms", "seek.terms", OUTPUT_DIRECTORY);

	//	Searcher s(OUTPUT_DIRECTORY, "inverted.index", "vocabulary.terms", "file.documents");
	//	string query;
	//	cout << "Welcome to IR Search by Jordan Silva." << endl;
	//	cout << "To search more than one term, use AND or OR to concatenate them in the query." << endl;
	//	cout << "Query example: 'Jordan AND Silva OR UFMG'" << endl;
	//	cout << "This query will be search Jordan and Silva intersection, and will group with the UFMG results." << endl;
	//	//cout << "Or you can type 'EXIT' to quit also.";
	//	do {
	//		cout << "What you would like to search? (Or type 'EXIT' to quit)" << endl;
	//		cin >> query;
	//
	//		if (query == "EXIT")
	//			break;
	//
	//		vector<string> results = s.search(query);
	//		for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it)
	//		    cout << *it << endl;
	//	} while (query != "EXIT");


	//mergeSeek();

	//	string query;
	//	cin >> query;

	//	if (query != null && query.length() > 0)
	//	{
	//		search(query);
	//	}
	//search();
	//cin;
	//Count time
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "All files was indexed. Time elapsed: " << elapsed_secs << endl;
	cout << currentDateTime() << endl;
	cout << "All files was indexed" << endl;

	//Read index
	//	WriterHelper wHelper("./output/_merged414.index", false);
	//	while (wHelper.HasNext()) {
	//		IndexTerm i = wHelper.ReadIndex();
	//		cout << i.print() << endl;
	//	}

	//Read vocabulary
	//	while (wHelper.HasNext()) {
	//		wHelper.Read(&term);
	//		break;
	//		wHelper.Read(&id);
	//		cout << "term: " << term << " | id: " << id << endl;
	//	}

	return 0;
}

