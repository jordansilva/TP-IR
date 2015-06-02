/*
 * Searcher.h
 *
 *  Created on: May 30, 2015
 *      Author: jordan
 */

#ifndef PAGERANK_H_
#define PAGERANK_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/unordered_map.hpp>
#include "../index/Dictionary.h"
#include "../index/IndexDocument.h"
#include "../util/WriterHelper.h"


const double DEFAULT_ALPHA = 0.85;
const double DEFAULT_DELTA = 0.15;
const double DEFAULT_CONVERGENCE = 0.00001;
const unsigned long DEFAULT_MAX_ITERATIONS = 100;

using namespace std;
using namespace boost;

class PageRank {
private:
    string fDocuments;
    string fReferences;
    map<unsigned int, IndexDocument*> *mDocuments;
    unordered_map<unsigned int, vector<unsigned int>*> *mReferences;

    void constructTable();
    void calculate();
    void dump();
public:
	PageRank();
    void execute(string documents, string references);
	virtual ~PageRank();
};

#endif /* PAGERANK_H_ */
