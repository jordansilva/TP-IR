/*
 * Term.h
 *
 *  Created on: Apr 29, 2015
 *      Author: jordan
 */

#ifndef TERM_H_
#define TERM_H_

#include <string>

using namespace std;

class Term {
public:

	unsigned int id;
	unsigned int indexSeek;
	string term;

	Term(unsigned int _id) {
		id = _id;
	}

	Term(unsigned int _id, unsigned int _indexSeek) {
		id = _id;
		indexSeek = _indexSeek;
	}

	Term(unsigned int _id, string _term) {
		id = _id;
		term = _term;
	}

	Term(unsigned int _id, string _term, unsigned int _indexSeek) {
		id = _id;
		term = _term;
		indexSeek = _indexSeek;
	}

	virtual ~Term() {

	}
};

#endif /* TERM_H_ */
