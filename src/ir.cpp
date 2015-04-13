//
//  main.cpp
//  ir
//
//  Created by Jordan Silva on 08/04/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

#include <iostream>
#include "libs/reader/CollectionReader.h"
#include "index/IndexDocument.h"
#include "index/Indexer.h"

#define DIRECTORY "/home/jordan/documents/ir/irCollection"
#define MAPFILE "index.txt"

using namespace std;
using namespace RICPNS;
using namespace htmlcxx;

void readDocument(Document doc);

int main(int argc, const char * argv[]) {
	CollectionReader reader(DIRECTORY, MAPFILE);
	Document doc;
	doc.clear();

	Indexer indexer(".");
	while (reader.getNextDocument(doc)) {

		IndexDocument *document = new IndexDocument(doc);
		indexer.AddDocument(document);
		//cout << parser.process(index.getText()) << endl;
	}

	cin.get();
	return 0;
}

