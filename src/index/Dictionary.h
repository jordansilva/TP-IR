/*
 * Dictionary.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <fstream>
#include <boost/unordered_map.hpp>
#include "Term.h"

using namespace std;
using namespace boost;

class Dictionary {
public:
	Dictionary();
	Dictionary(string file);
	virtual ~Dictionary();
	unsigned int AddTerm(string term);
	unsigned int AddTerm(string term, unsigned int seek);
	unsigned int AddTerm(unsigned int termId, string term, unsigned int seek);
	unordered_map<string, Term>* getTerms();
	Term* find(string term);
	bool loadDictionary(string filename);
private:
	unordered_map<string, Term>* terms;

};

inline unordered_map<string, Term>* Dictionary::getTerms() {
	return terms;
}

inline Term* Dictionary::find(string query) {
	unordered_map<string, Term>::iterator it = terms->find(query);

	if (it == terms->end())
		return NULL;
	else
		return &it->second;
}

#endif /* DICTIONARY_H_ */
