/*
 * Dictionary.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

class Dictionary {
public:
	Dictionary();
	Dictionary(string file);
	virtual ~Dictionary();
	int AddTerm(string term);
	unordered_map<string, unsigned int>* getTerms();
private:
	unordered_map<string, unsigned int>* terms;
};

inline unordered_map<string, unsigned int>* Dictionary::getTerms() {
	return terms;
}

#endif /* DICTIONARY_H_ */
