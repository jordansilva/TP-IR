//
//  main.cpp
//  ir
//
//  Created by Jordan Silva on 08/04/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "libs/reader/CollectionReader.h"
#include "index/IndexDocument.h"
#include "index/Indexer.h"

#define DIRECTORY "/home/jordan/documents/ir/irCollection"
#define MAPFILE "index.txt"

using namespace std;
using namespace RICPNS;
using namespace htmlcxx;

void readDocument(Document doc);

const std::string currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

bool isValid(string url) {
	if (url.find(".pdf") != string::npos || url.find(".doc") != string::npos
			|| url.find(".xls") != string::npos || url.find(".swf")
			!= string::npos)
		return false;
	else
		return true;
}

int main(int argc, const char * argv[]) {
	clock_t start = clock();
	cout << currentDateTime() << endl;

	CollectionReader reader(DIRECTORY, MAPFILE);
	Document doc;
	doc.clear();
	Indexer indexer(".");

	while (reader.getNextDocument(doc)) {
		if (isValid(doc.getURL())) {
			IndexDocument *document = new IndexDocument(doc);
			indexer.AddDocument(document);
		}
	}

	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "All files was indexed. Time elapsed: " << elapsed_secs << endl;
	cout << currentDateTime() << endl;
	cout << "All files was indexed" << endl;
	cin.get();
	return 0;
}

