/*
 * Searcher.h
 *
 *  Created on: June 01, 2015
 *      Author: jordan
 */

#ifndef VECTORMODELSPACE_H_
#define VECTORMODELSPACE_H_

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
#include "../parser/TextParser.h"

using namespace std;
using namespace boost;

class VectorModelSpace {
private:
    unsigned int mCollectionSize;
    WriterHelper* mIndex;
    Dictionary* mDictionary;
    unordered_map<unsigned int, IndexDocument*> *mDocuments;
    void recoverIndexTerms(Term term, Query::Query* query);
    void similarity(Query* query);
public:
	VectorModelSpace(string directory, string index, string vocabulary, unordered_map<unsigned int, IndexDocument*> *documents);
    multimap<double, IndexDocument*, std::greater<double> > search(Query::Query query);
	virtual ~VectorModelSpace();
};

#endif /* VECTORMODELSPACE_H_ */
