/*
 * Dictionary.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	cout << "Construct dictionary" << endl;
	terms = new unordered_map<string, unsigned int>();
}

Dictionary::~Dictionary() {
	delete terms;
}

int Dictionary::AddTerm(string term) {
	unordered_map<string, unsigned int>::iterator it = terms->find(term);

	if (it == terms->end()) {
		int id = terms->size()+1;
		terms->insert(make_pair(term, id));
		//cout << term << " " << id << endl;
		return id;
	} else
		return it->second;
}
