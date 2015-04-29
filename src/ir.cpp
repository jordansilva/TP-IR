//
//  main.cpp
//  ir
//
//  Created by Jordan Silva on 08/04/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <ctime>
#include "util/SortFile.h"

#define DIRECTORY "/home/jordan/documents/ir/irCollection"
#define MAPFILE "index.txt"
#define OUTPUT_DIRECTORY "./output/"

using namespace std;
using namespace RICPNS;
using namespace htmlcxx;

const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void search(string query) {

}

void mergeSeek() {

}

int main(int argc, const char * argv[]) {

	clock_t start = clock();
	cout << currentDateTime() << endl;

	//index
	//Indexer indexer(DIRECTORY, MAPFILE, OUTPUT_DIRECTORY);

	//external sort
	//SortFile sort("file.index");
	
	//merge vocabulary
	SortFile::mergeVocabulary("file.terms", "seek.terms", OUTPUT_DIRECTORY);

	
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

