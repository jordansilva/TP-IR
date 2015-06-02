/*
 * Dictionary.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	terms = new unordered_map<string, Term> ();
}

Dictionary::Dictionary(string filename) {
	terms = new unordered_map<string, Term> ();
	terms->clear();
	if (!loadDictionary(filename))
	{
        //cout << "Vocabulário não encontrado. Nome do arquivo: " << filename << endl;
		throw;
	}
}

Dictionary::~Dictionary() {
	delete terms;
}

unsigned int Dictionary::AddTerm(string term, unsigned int frequency) {
	unordered_map<string, Term>::iterator it = terms->find(term);

	if (it == terms->end()) {
		unsigned int id = terms->size() + 1;
		terms->insert(make_pair(term, Term(id, 1)));
		return id;
	} else
    {
        Term *t = &it->second;
        t->frequency += 1;
		return it->second.id;
    }
}

unsigned int Dictionary::AddTerm(string term, unsigned int frequency, unsigned int seek) {
	unordered_map<string, Term>::iterator it = terms->find(term);

	if (it == terms->end()) {
		unsigned int id = terms->size() + 1;
		terms->insert(make_pair(term, Term(id, frequency, seek)));
		return id;
	} else
    {
        Term *t = &it->second;
        t->frequency += frequency;
		return it->second.id;
    }
}

unsigned int Dictionary::AddTerm(unsigned int termId, string term, unsigned int frequency, unsigned int seek) {
	terms->insert(make_pair(term, Term(termId, frequency, seek)));
	return termId;
}

bool Dictionary::loadDictionary(string filename) {
	ifstream writer(filename);
	if (writer.good()) {
		string line;
		string term;
		unsigned int id = 0;
		unsigned int seek = 0;
        unsigned int frequency = 0;

		while (getline(writer, line)) {
			istringstream ss(line);
			ss >> id >> term >> frequency >> seek;
			AddTerm(id, term, frequency, seek);
		}

		return true;
	} else
		return false;
}
