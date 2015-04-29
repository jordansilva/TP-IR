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
#include "libs/reader/CollectionReader.h"
#include "index/IndexDocument.h"
#include "index/Indexer.h"
#include "util/SortFile.h"

#define DIRECTORY "/home/jordan/documents/ir/irCollection"
#define MAPFILE "index.txt"

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

bool isValid(string url) {
	if (url.find(".pdf") != string::npos || url.find(".doc") != string::npos || url.find(".xls")
			!= string::npos || url.find(".swf") != string::npos)
		return false;
	else
		return true;
}

void index() {
	//Indexer
	CollectionReader reader(DIRECTORY, MAPFILE);
	Document doc;
	Indexer* indexer = new Indexer("./output/");

	while (reader.getNextDocument(doc)) {
		if (isValid(doc.getURL())) {
			IndexDocument document(doc);
			indexer->AddDocument(document);
		}
	}

	//Save vocabulary
	indexer->SaveVocabulary();

	delete indexer;
}

void order() {
	///home/jordan/documents/ir/ir/file.index
	SortFile sortFile("file.index");
	sortFile.sort();
}

void mergeSeek() {
}

void search(string query) {

}

int main(int argc, const char * argv[]) {

	clock_t start = clock();
	cout << currentDateTime() << endl;

	//index();
	order();
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

