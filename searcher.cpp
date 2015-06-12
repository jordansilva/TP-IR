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
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include "src/search/Search.h"
#include "src/search/VectorModelSpace.h"
#include "src/search/Query.h"
#include "src/search/PageRank.h"
#include "src/util/FileHelper.h"
#include "src/index/IndexDocument.h"

using namespace std;
using namespace boost;

#define DOCUMENTS_NAME "file.documents"
#define OUTPUT_DIRECTORY "./output/"
#define GROUDTRUTH_DIRECTORY "./results/"
#define INVERTED_INDEX "inverted.index"
#define INVERTED_VOCABULARY "vocabulary.terms"
#define ANCHOR_INDEX "ianchor.index"
#define ANCHOR_VOCABULARY "anchor_vocabulary.terms"
#define ALPHA 0.48 //VMS
#define BETA 0.26 //ANCHOR TEXT
#define GAMA 0.26 //PAGE RANK

unordered_map<unsigned int, IndexDocument*>* mDocuments;
map<int, string> *mQueries;
Search *searchIndex;
Search *searchAnchor;

void init() {
	mDocuments = FileHelper::loadDocuments(string(OUTPUT_DIRECTORY) + "/" + string(DOCUMENTS_NAME));
	searchIndex = new Search(OUTPUT_DIRECTORY, INVERTED_INDEX, INVERTED_VOCABULARY, mDocuments);
	searchAnchor = new Search(OUTPUT_DIRECTORY, ANCHOR_INDEX, ANCHOR_VOCABULARY, mDocuments);

	mQueries = new map<int, string>();	
}

void loadQueries(string filename) {
	ifstream writer(filename);
    if (writer.good()) {
        string line;
        int i = 0;
        
        while (getline(writer, line)) {
            istringstream ss(line);
            mQueries->insert(pair<int, string> (i, line));
            i++;
        }
    }    
}

void destroy() {
	delete mDocuments;
	delete searchIndex;
	delete searchAnchor;
}

multimap<double, IndexDocument*, std::greater<double> > merge(unordered_map<unsigned int, double> index, unordered_map<unsigned int, double> anchor, bool pageRank, bool anchorText, double _alpha = ALPHA, double _beta = BETA, double _gama = GAMA) {
	
	index = Search::normalize(index);	
	
	if (anchorText)
		anchor = Search::normalize(anchor);

	multimap<double, IndexDocument*, std::greater<double> > result;
	
	//values
	double vectorValue = 0;
	double anchorValue = 0;
	double pageRankValue = 0;
	double total = 0;

	//weights
	double alpha = _alpha; 	
	double gama = _gama;
	double beta = _beta;

	for (auto it = index.begin(); it != index.end(); ++it) {
		
		vectorValue = it->second;
		anchorValue = 0;
		pageRankValue = 0;

		unordered_map<unsigned int, IndexDocument*>::iterator d = mDocuments->find(it->first);
		if (pageRank)
			pageRankValue = d->second->getPageRank();

		if (anchorText) {
			unordered_map<unsigned int, double>::iterator find = anchor.find(it->first);
			if (find != anchor.end())
			{
				anchorValue = find->second;
				anchor.erase(it->first);
			}
		}

		total = (alpha * vectorValue) + (gama * pageRankValue) + (beta * anchorValue);
		result.insert(make_pair(total, d->second));
	}

	if (anchorText) {
		for (auto it = anchor.begin(); it != anchor.end(); ++it)
		{
			anchorValue = 0;
			pageRankValue = 0;

			unordered_map<unsigned int, IndexDocument*>::iterator d = mDocuments->find(it->first);
			if (pageRank)
				pageRankValue = d->second->getPageRank();

			total = (gama * pageRankValue) + (beta * anchorValue);
			result.insert(make_pair(total, d->second));
		}
	}

	return result;	
}

void vectorModel(Query *q) {
	clock_t start = clock();

	searchIndex->search(q);
	VectorModelSpace::order(q);

	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "Time elapsed to search: " << elapsed_secs << endl;
}

void pageRank(Query *q) {
	clock_t start = clock();
	
	searchIndex->search(q);
	PageRank::order(q);
	
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "Time elapsed to search: " << elapsed_secs << endl;
}

void anchorText(Query *q) {
	clock_t start = clock();
	
	searchAnchor->search(q);	
	VectorModelSpace::order(q);
	
	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
	cout << "Time elapsed to search: " << elapsed_secs << endl;
}

void search(string query, bool vsm, bool pr, bool at) {

	Query::Query *q = new Query(query);	

	multimap<double, IndexDocument*, std::greater<double> > docs;

	if (vsm && !pr && !at) //vsm
	{
		vectorModel(q);
		docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
	}
	else if (!vsm && pr && !at) //pr
	{
		pageRank(q);
		docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
	}
	else if (!vsm && !pr && at) //anchor text
	{
		anchorText(q);
		docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
	}
	else if (vsm) //vsm + pr
	{
		vectorModel(q);
		
		Query::Query *q2 = new Query(query);
		if (at)
			anchorText(q2);

		docs = merge(q->mDocumentsWeight, q2->mDocumentsWeight, pr, at);
	}
	
	multimap<double, IndexDocument*, std::greater<double> >::iterator it = docs.begin();
	int i = 0;
	cout << docs.size() << " Results found." << endl;
	for (; it != docs.end(); ++it)
	{
		cout << i+1 << " - " << it->first << " | " << it->second->getUrl() << endl;		
		i++;
		if (i > 10)
			break;
	}
}

struct Queries {
	unsigned int id;
	string query;
	Query* queryDocs;
	Query* queryAnchor;
	Query* queryPageRank;
};

void test(string filename) {
	
	init();
	loadQueries(filename);

	ofstream outWriterALL;
	
	Query::Query *q;
	Query::Query *q2;
	Query::Query *q3;

	map<unsigned int, Queries> queriesDocsAnchor;	
	int i = 1;
 	for (auto it = mQueries->begin(); it != mQueries->end(); ++it) {
    	
    	//query
    	q = new Query(it->second);
		searchIndex->search(q);
		VectorModelSpace::order(q);
		
		q2 = new Query(it->second);
		searchAnchor->search(q2);		
		VectorModelSpace::order(q2);

		q3 = new Query(it->second);
		searchAnchor->search(q3);		
		PageRank::order(q3);

		Queries queries;
		queries.id = i;
		queries.query = it->second;
		queries.queryDocs = q;
		queries.queryAnchor = q2;
		queries.queryPageRank = q3;
		queriesDocsAnchor.insert(make_pair(i,queries));

		i++;
	}
	
	int j = 1;
	int count = 1;
	string tag;
	
	//Anchor Text
	tag = "N-AT";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	unordered_map<unsigned int, double> NUL;
    	//it->second.queryDocs->mDocumentsWeight
		//anchor
		multimap<double, IndexDocument*, std::greater<double> > docs(it->second.queryAnchor->mIndexDocuments.begin(), it->second.queryAnchor->mIndexDocuments.end());
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }
	outWriterALL.close();
    
    //VSM
    tag = "N-VSM";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	unordered_map<unsigned int, double> NUL;
    	//it->second.queryDocs->mDocumentsWeight
		//anchor
		multimap<double, IndexDocument*, std::greater<double> > docs(it->second.queryDocs->mIndexDocuments.begin(), it->second.queryDocs->mIndexDocuments.end());
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }
    outWriterALL.close();

 	//PageRank
    tag = "N-PageRank";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	unordered_map<unsigned int, double> NUL;
    	//it->second.queryDocs->mDocumentsWeight
		//anchor
		multimap<double, IndexDocument*, std::greater<double> > docs(it->second.queryPageRank->mIndexDocuments.begin(), it->second.queryPageRank->mIndexDocuments.end());
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }
    outWriterALL.close();

    //VSM+AT
    tag = "N-VSM+AT";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	//unordered_map<unsigned int, double> NUL;
    	multimap<double, IndexDocument*, std::greater<double> > docs = merge(it->second.queryDocs->mDocumentsWeight, it->second.queryAnchor->mDocumentsWeight, false, true);
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }

    outWriterALL.close();

    //VSM+PR
    tag = "N-VSM+PR";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	//unordered_map<unsigned int, double> NUL;
    	multimap<double, IndexDocument*, std::greater<double> > docs = merge(it->second.queryDocs->mDocumentsWeight, it->second.queryAnchor->mDocumentsWeight, true, false);
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }

    outWriterALL.close();

    //VSM+PR+AT
    tag = "N-VSM+PR+AT";
	outWriterALL.open(string(GROUDTRUTH_DIRECTORY) + "/" + tag);
    for (auto it = queriesDocsAnchor.begin(); it != queriesDocsAnchor.end(); ++it)
    {
    	cout << count << " | Doing query: " << it->second.query << " #" << tag << endl;

    	//unordered_map<unsigned int, double> NUL;
    	multimap<double, IndexDocument*, std::greater<double> > docs = merge(it->second.queryDocs->mDocumentsWeight, it->second.queryAnchor->mDocumentsWeight, true, true);
		
		j = 1;    	
    	for (auto it2 = docs.begin(); it2 != docs.end(); ++it2)
    	{
    		outWriterALL << "Q" << it->second.id << " 0 " << it2->second->getId() << " " << j << " " << it2->first << " " << tag << endl;
    		j++;
    	}

    	count++;
    	docs.clear();
    }

    outWriterALL.close();
}

int main(int argc, const char * argv[]) {	

	string query;
	string filename;
	bool testMode = false;
	bool vectorModel = false;	
	bool pageRank = false;
	bool anchorText = false;
	double vectorWeight = ALPHA;
	double pageRankWeight = GAMA;	
	double anchorWeight = BETA;

    for (int i = 1; i < argc; ++i)
    	if (string(argv[i]) == "-vsm")
    	{
    		vectorModel = true;
    		vectorWeight = boost::lexical_cast<double>(argv[i+1]);
    		i++;
    	}
    	else if (string(argv[i]) == "-pr")
    	{
    		pageRank = true;
    		pageRankWeight = boost::lexical_cast<double>(argv[i+1]);
    		i++;
    	}
    	else if (string(argv[i]) == "-at")
    	{
    		anchorText = true;
    		anchorWeight = boost::lexical_cast<double>(argv[i+1]);
    		i++;
    	}
    	else if (string(argv[i]) == "-test")
    	{
    		testMode = true;
    		filename = argv[i+1];
    		i++;
    	}
    	else
    	{
    		query += " " + string(argv[i]);
    	}
    
    boost::trim(query);
    
    if (testMode)
    	test(filename);
	else
	{
	    if (query.empty() || query.size() < 2)
	    	cout << "Found no queries. Please, type something to search." << endl;
	    else
	    	search(query, vectorModel, pageRank, anchorText);
	}
	return 0;
}

