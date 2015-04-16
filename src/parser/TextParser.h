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
#include <boost/regex.hpp>
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
	void removeNonAlphanumerics(string& token);
	void removeAccents(string& token);
	unordered_map<string, vector<int> > terms;
	const string rep[92] = { "&agrave;", "&aacute;", "&acirc;", "&atilde;",
			"&auml;", "&aring;", "&aelig;", "&ccedil;", "&egrave;", "&eacute;",
			"&ecirc;", "&euml;", "&igrave;", "&iacute;", "&icirc;", "&iuml;",
			"&eth;", "&ntilde;", "&ograve;", "&oacute;", "&ocirc;", "&otilde;",
			"&ouml;", "&divide;", "&oslash;", "&ugrave;", "&uacute;",
			"&ucirc;", "&uuml;", "&yacute;", "&thorn;", "&yuml;", "&deg;",
			"&plusmn;", "&sup2;", "&sup3;", "&acute;", "&micro;", "&para;",
			"&middot;", "&cedil;", "&sup1;", "&ordm;", "&raquo;", "&frac14;",
			"&frac12;", "&frac34;", "&iquest;", "&nbsp;", "&iexcl;", "&cent;",
			"&pound;", "&curren;", "&yen;", "&brvbar;", "&sect;", "&uml;",
			"&copy;", "&ordf;", "&laquo;", "&not;", "&shy;", "&reg;", "&macr;",
			"à", "á", "â", "ã", "ä", "å", "æ", "ç", "è", "é", "ê", "ë", "ì",
			"í", "î", "ï", "ñ", "ò", "ó", "ô", "õ", "ö", "ù", "ú", "û", "ü",
			"ý", "ÿ" };
	const string sub[92] = { "a", "a", "a", "a", "a", "a", "ae", "c", "e", "e",
			"e", "e", "i", "i", "i", "i", "", "n", "o", "o", "o", "o", "o",
			"÷", "ø", "u", "u", "u", "u", "y", "", "y", "", "", "", "", "", "",
			"", "", "", "", "", "", "", "", "", "", " ", "", "", "", "", "",
			"", "", "", "", "", "", "", "", "", "", "a", "a", "a", "a", "a",
			"a", "ae", "c", "e", "e", "e", "e", "i", "i", "i", "i", "n", "o",
			"o", "o", "o", "o", "u", "u", "u", "u", "y", "y", };
};

inline unordered_map<string, vector<int> > TextParser::GetTerms() {
	return terms;
}
#endif /* TEXTPARSER_H_ */
