/*
 * VectorModelSpace.cpp
 *
 *  Created on: June 01, 2015
 *      Author: jordan
 */

#include "Query.h"


Query::Query(string query) {
    mQuery = query;
    construct();
}

Query::~Query() {
}

void Query::construct() {
    TextParser parser;
    parser.Process(mQuery);
    
    unordered_map<string, vector<int> > terms = parser.GetTerms();
    unordered_map<string, vector<int> >::iterator it = terms.begin();
    unordered_map<string, vector<int> >::iterator end = terms.end();
    
    //writing terms
    int i = 0;
    for (; it != end; ++it) {
        QueryTerm* queryTerm = new QueryTerm();
        queryTerm->text = it->first;
        mTerms.insert(make_pair(i, queryTerm));
        i++;
    }
    
    
}
