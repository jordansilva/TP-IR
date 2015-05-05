/*
 * TextParser.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "TextParser.h"

TextParser::TextParser() {

}

TextParser::~TextParser() {
	terms.clear();
	// TODO Auto-generated destructor stub
}

void TextParser::Process(string text) {
	terms.clear();
	string token;
	int pos = 0;

	boost::to_lower(text);
	removeAccents(text);

	char_separator<char> sep(",.\t\r\n\b\v\f \\");
	tokenizer<char_separator<char> > tokens(text, sep);

	for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		token = it.current_token();
		boost::trim(token);

		if (!token.empty()) {
			pos++;
			AddTerm(token, pos);
		}
	}
}

bool nonAlphaNumeric(char c) {
	return !(isalpha(c) || isspace(c)); //isdigit(c)
}

void TextParser::removeNonAlphanumerics(std::string &str) {
	str.erase(std::remove_if(str.begin(), str.end(), nonAlphaNumeric), str.end());
}

void TextParser::removeAccents(string &str) {
	for (unsigned int i = 0; i < 92; i++)
		boost::replace_all(str, rep[i], sub[i]);
}

void TextParser::AddTerm(string& token, int pos) {
	//removeAccents(token); //memory problem
	removeNonAlphanumerics(token);
	if (token.length() > 1) {
		unordered_map<string, vector<int> >::iterator it = terms.find(token);
		vector<int>* positions;
		if (it == terms.end())
			positions = &terms[token];
		else
			positions = &it->second;

		positions->push_back(pos);
	}
}
