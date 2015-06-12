/*
 * Search.h
 *
 *  Created on: May 4, 2015
 *      Author: jordan
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <functional>
#include <math.h>
#include <boost/unordered_map.hpp>
#include "Query.h"
#include "../index/Dictionary.h"
#include "../index/IndexDocument.h"
#include "../util/WriterHelper.h"

using namespace std;
using namespace boost;

class Search {
private:
    unsigned int mCollectionSize;
    WriterHelper* mIndex;
    Dictionary* mDictionary;
    unordered_map<unsigned int, IndexDocument*> *mDocuments;
    void recoverIndexTerms(Term term, Query::Query* query);
public:
	Search(string directory, string index, string vocabulary, unordered_map<unsigned int, IndexDocument*> *documents);
    virtual ~Search();
    void search(Query::Query *query);
    static unordered_map<unsigned int, double> normalize(unordered_map<unsigned int, double> data);
	
};
#endif /* SEARCH_H_ */
