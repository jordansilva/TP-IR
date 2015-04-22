/*
 * IndexTerm.h
 *
 *  Created on: Apr 13, 2015
 *      Author: jordan
 */

#ifndef INDEXTERM_H_
#define INDEXTERM_H_

#include <vector>

using namespace std;

class IndexTerm {
public:
	int termId;
	int documentId;
	int frequency;
	vector<int> positions;

	IndexTerm(int termId_, int documentId_, int termFrequency_,
			vector<int> positions_) {
		termId = termId_;
		documentId = documentId_;
		frequency = termFrequency_;
		positions = positions_;
	}

	void print() {
		cout << "termId: " << termId;
		cout << " | docId: " << documentId;
		cout << " | frequency: " << frequency;

		cout << " | position: ";
		for (std::vector<int>::const_iterator i = positions.begin(); i != positions.end(); ++i)
			std::cout << *i << ' ';

		cout << endl;
	}

};

#endif /* INDEXTERM_H_ */
