//
//  jsearch.cpp
//  ir
//
//  Created by Jordan Silva on 01/06/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <string>
#include <boost/algorithm/string.hpp>
#include "src/search/VectorModelSpace.h"
#include "src/search/Query.h"
#include "src/util/FileHelper.h"
#include "src/index/IndexDocument.h"


using namespace std;
using namespace boost;

#define DOCUMENTS_NAME "file.documents"
#define OUTPUT_DIRECTORY "./output/"
#define INVERTED_INDEX "inverted.index"
#define INVERTED_VOCABULARY "vocabulary.terms"
#define ANCHOR_INDEX "ianchor.index"
#define ANCHOR_VOCABULARY "anchor_vocabulary.terms"

unordered_map<unsigned int, IndexDocument*>* mDocuments;

void search(string query) {

	clock_t start = clock();
	clock_t end;

	cout << "Loading Documents... " << endl;
	mDocuments = FileHelper::loadDocuments(string(OUTPUT_DIRECTORY) + "/" + string(DOCUMENTS_NAME));

	Query::Query q(query);
	
	VectorModelSpace vectorModel(OUTPUT_DIRECTORY, INVERTED_INDEX, INVERTED_VOCABULARY, mDocuments);
	multimap<double, IndexDocument*, std::greater<double> > result = vectorModel.search(q);

	multimap<double, IndexDocument*, std::greater<double> >::iterator it = result.begin();
	int i = 0;
	cout << result.size() << " Results found." << endl;
	for (; it != result.end(); ++it)
	{
		cout << i+1 << " - " << it->first << " | " << it->second->getUrl() << endl;
		// cout << it->second->getUrl() << endl;
		// cout << endl;
		i++;
	}
}

int main(int argc, const char * argv[]) {	
	
	string query;
    for (int i = 1; i < argc; ++i)
    	query += " " + string(argv[i]);
    
    boost::trim(query);
    if (query.empty() || query.size() < 2)
    	cout << "Found no queries. Please, type something to search." << endl;
    else
    	search(query);
	
	return 0;
}

