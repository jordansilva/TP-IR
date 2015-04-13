/*
 * TextParser.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef TEXTPARSER_H_
#define TEXTPARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

class TextParser {
public:
	TextParser();
	virtual ~TextParser();

	void Process(string text);
	unordered_map<string, vector<int> > GetTerms();
private:
	void AddTerm(string& token, int pos);
	unordered_map<string, vector<int> > terms;
};

inline unordered_map<string, vector<int> > TextParser::GetTerms() {
	return terms;
}
#endif /* TEXTPARSER_H_ */
