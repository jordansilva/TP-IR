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
	virtual ~Dictionary();
	int AddTerm(string term);
private:
	unordered_map<string, int>* terms;
};

#endif /* DICTIONARY_H_ */
