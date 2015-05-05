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
#include "src/util/SortFile.h"
#include "src/index/Indexer.h"
#include "src/search/Searcher.h"

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

void instructions() {
	cout << "Indexer 0.1" << endl;
	cout << "@author jordansilva" << endl;
	cout << "index <directory> <index> [output] \t -initializes the index" << endl;
	cout << "search [directory] [inverted-index] [vocabulary] [documents] \t -initializes the search program" << endl;
	cout << "EXIT \t -to exit program" << endl << endl << endl;
}

int main(int argc, const char * argv[]) {

	string args;
	string command[5];
	int i = 0;
	string token = "";
	do {
		instructions();
		getline(cin, args);
		command[0] = "";
		char_separator<char> sep(" ");
		tokenizer<char_separator<char> > tokens(args, sep);
		i = 0;
		token.clear();
		for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
			token = it.current_token();
			boost::trim(token);
			command[i] = "";
			command[i] = token;
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
			cout << "\n\n======================" << endl;
			cout << "Welcome to IR Search by Jordan Silva." << endl;
			cout << "To search more than one term, use AND or OR to concatenate them in the query." << endl;
			cout << "Query example: 'Jordan AND Silva OR UFMG'" << endl;
			cout << "This query will be search Jordan and Silva intersection, and will group with the UFMG results." << endl;
			cout << "======================" << endl;
			//cout << "Or you can type 'EXIT' to quit also.";

			clock_t start = clock();
			clock_t end;
			do {
				query = "";
				cout << "\n\nWhat you would like to search? (Or type 'EXIT' to quit)" << endl;
				getline(cin, query);
				if (query == "EXIT")
					break;

				start = clock();
				vector<string> results = s.search(query);
				if (results.size() > 0) {
					int size = 10;
					if (results.size() < 10)
						size = results.size();


					end = clock();
					double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;

					cout << results.size() << " documents were found.\n" << endl;
					cout << "This query took " << elapsed_secs << " seconds to run." << endl;
					cout << "Top " << size << " documents" << endl;
					cout << "================" << endl;
					for (int i = 0; i < size; i++)
						cout << results[i] << endl;

					//All documents
					//for (std::vector<string>::iterator it = results.begin(); it != results.end(); ++it)
					//	cout << *it << endl;
				}
				else
					cout << "\nNo results! :(" << endl;
			} while (query != "EXIT");
		} else if (command[0] == "EXIT")
			break;
		else
			cout << "Unknown command" << endl;
	} while (command[0] == "EXIT");

	return 0;
}
