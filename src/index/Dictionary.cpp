/*
 * Dictionary.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	cout << "Construct dictionary" << endl;
	terms = new unordered_map<string, Term>();
}

Dictionary::~Dictionary() {
	delete terms;
}

unsigned int Dictionary::AddTerm(string term) {
	unordered_map<string, Term>::iterator it = terms->find(term);

	if (it == terms->end()) {
		unsigned int id = terms->size()+1;
		terms->insert(make_pair(term, Term(id)));
		//cout << term << " " << id << endl;
		return id;
	} else
		return it->second.id;
}

unsigned int Dictionary::AddTerm(string term, unsigned int seek) {
	unordered_map<string, Term>::iterator it = terms->find(term);

	if (it == terms->end()) {
		unsigned int id = terms->size()+1;
		terms->insert(make_pair(term, Term(id, seek)));
		return id;
	} else
		return it->second.id;
}
