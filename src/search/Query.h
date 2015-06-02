/*
 * Searcher.h
 *
 *  Created on: June 01, 2015
 *      Author: jordan
 */

#ifndef QUERY_H_
#define QUERY_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/unordered_map.hpp>
#include "../parser/TextParser.h"
#include "../index/Term.h"
#include "../index/IndexDocument.h"

using namespace std;
using namespace boost;


class Query {
private:
    void construct();
public:
    struct QueryTerm {        
        string text;
        Term term;
        double weightQuery;

        QueryTerm() {}
    };
    
    struct QueryDocs {
        IndexDocument* document;
        unsigned int docId;
        unsigned int size;
        double similarity;
        unordered_map<unsigned int, double> termWeight;
        
    };
    

    string mQuery;
    unordered_map<unsigned int, QueryTerm*> mTerms;
    unordered_map<unsigned int, QueryDocs*> mDocs;
    unordered_multimap<double, IndexDocument*> mIndexDocuments;

	Query(string query);
	virtual ~Query();
};

#endif /* QUERY_H_ */
