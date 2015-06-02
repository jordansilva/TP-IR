/*
 * StringHelper.h
 *
 *  Created on: May 26, 2015
 *      Author: jordan
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

class StringHelper {
public:
	static void removeNonAlphanumerics(string& token);	
    static void removeAccents(string& token);
    static bool isNumber(const std::string& s);
private:
    StringHelper();
    virtual ~StringHelper();
	static const string rep[92];
    static const string sub[92];
};

#endif /* STRINGHELPER_H_ */
