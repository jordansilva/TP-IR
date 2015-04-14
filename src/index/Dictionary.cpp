/*
 * Dictionary.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	cout << "Construct dictionary" << endl;
	terms = new unordered_map<string, int>();
}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

int Dictionary::AddTerm(string term) {
	unordered_map<string, int>::iterator it = terms->find(term);

	if (it == terms->end()) {
		int id = terms->size()+1;
		terms->insert(make_pair(term, id));
		return id;
	} else
		return it->second;
}
