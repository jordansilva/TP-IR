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

	cout << "Indexer 0.1" << endl;
	cout << "@author jordansilva" << endl;
	cout << "index <directory> <index> [output] \t -initializes the index" << endl;
	cout << "search [directory] [inverted-index] [vocabulary] [documents] \t -initializes the search program" << endl;
	cout << "EXIT \t -to exit program" << endl << endl << endl;

	string args;
	string command[5];
	int i = 0;
	string token = "";
	while (args != "EXIT") {
		getline(cin, args);
		char_separator<char> sep(" ");
		tokenizer<char_separator<char> > tokens(args, sep);
		i = 0;
		token.clear();
		for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
			token = it.current_token();
			boost::trim(token);
			command[i] = "";
			command[i] = token;
			cout << token << endl;
			i++;
		}

		if (command[0] == "index") {
			if (command[2].empty())
				command[2] = MAPFILE;

			if (command[3].empty())
				command[3] = OUTPUT_DIRECTORY;

			//indexer
			clock_t start = clock();
			Indexer indexer(command[1], command[2], command[3]);
			clock_t end = clock();
			double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
			cout << "Indexer finish. Time elapsed: " << elapsed_secs << endl;

			//external sort
			start = clock();
			SortFile sort(command[3], "file.index");
			end = clock();
			elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
			cout << "Sort finish. Time elapsed: " << elapsed_secs << endl;
			//merge vocabulary
			start = clock();
			SortFile::mergeVocabulary("file.terms", "seek.terms", command[3]);
			end = clock();
			elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
			cout << "Merge finish. Time elapsed: " << elapsed_secs << endl;

		} else if (command[0] == "search") {
			if (command[1].empty())
				command[1] = OUTPUT_DIRECTORY;
			if (command[2].empty())
				command[2] = "inverted.index";
			if (command[3].empty())
				command[3] = "vocabulary.terms";
			if (command[4].empty())
				command[4] = "file.documents";

			Searcher s(command[1], command[2], command[3], command[4]);

			string query;
			cout << "Welcome to IR Search by Jordan Silva." << endl;
			cout << "To search more than one term, use AND or OR to concatenate them in the query." << endl;
			cout << "Query example: 'Jordan AND Silva OR UFMG'" << endl;
			cout << "This query will be search Jordan and Silva intersection, and will group with the UFMG results." << endl;
			//cout << "Or you can type 'EXIT' to quit also.";
			do {
				cout << "What you would like to search? (Or type 'EXIT' to quit)" << endl;
				cin >> query;

				if (query == "EXIT")
					break;

				vector<string> results = s.search(query);
				for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it)
					cout << *it << endl;
			} while (query != "EXIT");
		} else if (command[0] == "EXIT")
			break;
		else
			cout << "Unknown command" << endl;
	}

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
//	clock_t end = clock();
//	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
//	cout << "All files was indexed. Time elapsed: " << elapsed_secs << endl;
//	cout << currentDateTime() << endl;
//	cout << "All files was indexed" << endl;

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

