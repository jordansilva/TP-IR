/*
 * Dictionary.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	// TODO Auto-generated constructor stub

}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

int Dictionary::addTerm(string term) {
	unordered_map<string, int>::iterator it = terms.find(term);
	if (it == terms.end()) {
		int& id = terms[term];
		id = terms.size();
		return id;
	} else
		return it->second;
}
