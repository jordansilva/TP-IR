/*
 * TextParser.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "TextParser.h"

TextParser::TextParser() {
	// TODO Auto-generated constructor stub

}

TextParser::~TextParser() {
	terms.clear();
	// TODO Auto-generated destructor stub
}

void TextParser::Process(string text) {
	terms.clear();
	string token;
	int pos = 0;
	char_separator<char> sep(", ");
	tokenizer<char_separator<char> > tokens(text, sep);

	for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it
			!= tokens.end(); ++it) {
		token = it.current_token();
		trim(token);

		if (!token.empty()) {
			pos++;
			AddTerm(token, pos);
		}
	}
}

void TextParser::AddTerm(string& token, int pos) {
	unordered_map<string, vector<int> >::iterator it = terms.find(token);
	vector<int>* positions;
	if (it == terms.end())
		positions = &terms[token];
	else
		positions = &it->second;

	positions->push_back(pos);
}
