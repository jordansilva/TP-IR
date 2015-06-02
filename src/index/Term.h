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
    unsigned int frequency;
	string term;

	Term() {}

	Term(unsigned int _id, unsigned int _frequency) {
		id = _id;
        frequency = _frequency;
	}

	Term(unsigned int _id, unsigned int _frequency, unsigned int _indexSeek) {
		id = _id;
        frequency = _frequency;
		indexSeek = _indexSeek;
	}

	Term(unsigned int _id, unsigned int _frequency, string _term) {
		id = _id;
        frequency = _frequency;
		term = _term;
	}

	Term(unsigned int _id, unsigned int _frequency, string _term, unsigned int _indexSeek) {
		id = _id;
        frequency = _frequency;
		term = _term;
		indexSeek = _indexSeek;
	}

	virtual ~Term() {

	}
};

#endif /* TERM_H_ */
