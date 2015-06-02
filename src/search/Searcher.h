/*
 * Searcher.h
 *
 *  Created on: May 4, 2015
 *      Author: jordan
 */

#ifndef SEARCHER_H_
#define SEARCHER_H_

#include <string>
#include "../util/WriterHelper.h"
#include "../index/Dictionary.h"
#include "../index/Term.h"
#include "../index/IndexDocument.h"
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

class Searcher {
private:
	WriterHelper* mIndex;
	Dictionary* mDictionary;
	map<unsigned int, IndexDocument*> mDocuments;
	vector<Term*> getTermsFromVocabulary(string query);
	vector<unsigned int> recoverIndexTerms(Term term);
	bool loadDocuments(string filename);
	vector<unsigned int> intersectionVec(vector<unsigned int> &v1, vector<unsigned int> &v2);
	vector<unsigned int> unionVec(vector<unsigned int> &v1, vector<unsigned int> &v2);

public:
	Searcher(string directory, string index, string vocabulary, string documents);
	vector<IndexDocument*> search(string query);
	virtual ~Searcher();
};

#endif /* SEARCHER_H_ */
