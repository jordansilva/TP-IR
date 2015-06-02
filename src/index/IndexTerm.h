/*
 * IndexTerm.h
 *
 *  Created on: Apr 13, 2015
 *      Author: jordan
 */

#ifndef INDEXTERM_H_
#define INDEXTERM_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IndexTerm {
public:
	int run;
	unsigned int termId;
	unsigned int documentId;
	int frequency;
	vector<int> positions;

	IndexTerm(unsigned int termId_, unsigned int documentId_, int termFrequency_, vector<int> positions_) {
		termId = termId_;
		documentId = documentId_;
		frequency = termFrequency_;
		positions = positions_;
	}

	string print() {
		string print = "";
		print = "termId: " + to_string(termId);
		print = print + " | docId: " + to_string(documentId);
		print = print + " | frequency: " + to_string(frequency);

		print += print + " | position: ";
		for (std::vector<int>::const_iterator i = positions.begin(); i != positions.end(); ++i)
			print = print + to_string(*i) + " ";

		return print;
	}

	unsigned int size() {
		return sizeof(termId) + sizeof(documentId) + sizeof(frequency) + (sizeof(int) * frequency);
	}

	friend bool operator<(const IndexTerm &x, const IndexTerm &y) {
		if (x.termId < y.termId) {
			return true;
		} else if (x.termId == y.termId) {
			if (x.documentId < y.documentId) {
				return true;
			} else if (x.documentId == y.documentId) {
				if (x.frequency < y.frequency) {
					return true;
				}
			}
		}
		return false;
	}

	friend bool operator>(const IndexTerm &x, const IndexTerm &y) {
		if (x.termId > y.termId) {
			return true;
		} else if (x.termId == y.termId) {
			if (x.documentId > y.documentId) {
				return true;
			} else if (x.documentId == y.documentId) {
				if (x.frequency > y.frequency) {
					return true;
				}
			}
		}
		return false;
	}

};

#endif /* INDEXTERM_H_ */
