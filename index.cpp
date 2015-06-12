//
//  index.cpp
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
#include "src/search/PageRank.h"

#define DIRECTORY "/Users/jordansilva/Documents/Jordan/Mestrado/Disciplinas/irCollection"
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
	cout << "index <directory> <index> \t -initializes the index" << endl;
	cout << "search [directory] [inverted-index] [vocabulary] [documents] \t -initializes the search program" << endl;
	cout << "EXIT \t -to exit program" << endl << endl << endl;
}

void pageRank() {
	
	string documents = string(OUTPUT_DIRECTORY) + string(DOCUMENTS_NAME);
    string references = string(OUTPUT_DIRECTORY) + string(DOCUMENTS_URL);       
	clock_t start = clock();
	
	cout << "Calculating PageRank..." << endl;    
	PageRank pr;
    pr.execute(documents, references);    
    
    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "PageRank was calculated. Time elapsed: " << elapsed_secs << endl;    
}

void sortInvertedIndex() {
	clock_t start = clock();
	clock_t end = clock();
	double elapsed_secs = 0;

	//external sort
	cout << "Starting External Sort - Index..." << endl;
	SortFile sort(OUTPUT_DIRECTORY, "file.index", "inverted");
	
	end = clock();
	elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "Finish External Sort - Index. Time elapsed: " << elapsed_secs << endl;
    
    //merge vocabulary
    start = clock();

    cout << "Starting Merge Sort - Index..." << endl;    
    SortFile::mergeVocabulary("file.terms", "seek.terms", OUTPUT_DIRECTORY, "vocabulary.terms");
    
    end = clock();
    elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finish Merge Sort - Index. Time elapsed: " << elapsed_secs << endl;  
}

void sortAnchorIndex() {
	clock_t start = clock();
	clock_t end = clock();
	double elapsed_secs = 0;
	
	//external sort
    cout << "Starting External Sort - Anchor..." << endl;    
    SortFile sortAnchor(OUTPUT_DIRECTORY, "anchor.index", "ianchor");
    
    end = clock();
    elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finish External Sort - Anchor. Time elapsed: " << elapsed_secs << endl;
	
    //merge vocabulary
    start = clock();
    cout << "Starting Merge Sort - Anchor..." << endl;    
    SortFile::mergeVocabulary("anchor.terms", "seek.terms", OUTPUT_DIRECTORY, "anchor_vocabulary.terms");
    
    end = clock();
    elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Finish Merge Sort - Anchor. Time elapsed: " << elapsed_secs << endl;    
}

void index(string dirIndex, string fileIndex) {
	if (dirIndex.empty())
	{
		cout << "Diretório para indexação não informado" << endl;
	}
	else
	{
		if (fileIndex.empty())
			fileIndex = MAPFILE;

		//indexer
		clock_t start = clock();
	    clock_t general = clock();
	    clock_t end = clock();
	    double elapsed_secs = 0;

	    //TODO: Remove this line
	    dirIndex = DIRECTORY;
	    
	    
	    //index
	    cout << "Indexing..." << endl;
		Indexer indexer(dirIndex, fileIndex, OUTPUT_DIRECTORY);
		end = clock();
		elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
		cout << "Indexer finish. Time elapsed: " << elapsed_secs << endl;
	    
	    pageRank();
		sortInvertedIndex();
		sortAnchorIndex();
		
		end = clock();
		elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	    cout << "Total time elapsed: " << elapsed_secs << endl;
	}
}

int main(int argc, const char * argv[]) {

	string dirIndex;
	string fileIndex;
	if (argc > 1)
	{
		dirIndex = argv[0];
		if (argc > 2)
			fileIndex = argv[1];
	}

	index(dirIndex, fileIndex);	
	return 0;
}

