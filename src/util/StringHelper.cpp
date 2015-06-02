/*
 * SortFile.cpp
 *
 *  Created on: May 27, 2015
 *      Author: jordan
 */

#include "StringHelper.h"

 const string StringHelper::rep[92] = { "&agrave;", "&aacute;", "&acirc;", "&atilde;",
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

const string StringHelper::sub[92] = { "a", "a", "a", "a", "a", "a", "ae", "c", "e", "e",
    "e", "e", "i", "i", "i", "i", "", "n", "o", "o", "o", "o", "o",
    "÷", "ø", "u", "u", "u", "u", "y", "", "y", "", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", " ", "", "", "", "", "",
    "", "", "", "", "", "", "", "", "", "", "a", "a", "a", "a", "a",
    "a", "ae", "c", "e", "e", "e", "e", "i", "i", "i", "i", "n", "o",
    "o", "o", "o", "o", "u", "u", "u", "u", "y", "y", };

StringHelper::StringHelper() {
}

StringHelper::~StringHelper() {	
}

bool nonAlphaNumeric(char c) {
	return !(isalpha(c) || isspace(c) || isdigit(c)); //isdigit(c)
}

void StringHelper::removeNonAlphanumerics(std::string &str) {
	str.erase(std::remove_if(str.begin(), str.end(), nonAlphaNumeric), str.end());
    if (isNumber(str))
        str = "";
}

bool StringHelper::isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void StringHelper::removeAccents(string &str) {
	for (unsigned int i = 0; i < 92; i++)
		boost::replace_all(str, rep[i], sub[i]);
}
