/*
 * Indexer.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Indexer.h"

Indexer::Indexer(string directoryName) {
	directory = directoryName;
	writer = new WriterHelper(directory + "/file.index", true);
	countDocuments = 0;
}

Indexer::~Indexer() {
	delete writer;
}

const std::string currentDateTime2() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void Indexer::AddDocument(IndexDocument &document) {
	parser.Process(document.getText());
	unordered_map<string, vector<int> > terms = parser.GetTerms();
	unordered_map<string, vector<int> >::iterator it = terms.begin();
	unordered_map<string, vector<int> >::iterator end = terms.end();

	countDocuments++;
	int termid = 0;
	for (; it != end; ++it) {
		termid = dictionary.AddTerm(it->first);
		//cout << "term_id: " << termid << " | term: " << it->first << " | document_id: " << countDocuments << " | " << it->second.size() << endl;
		IndexTerm term(termid, countDocuments, it->second.size(), it->second);
		writer->Write(term);
	}

	if (countDocuments % 10000 == 0)
		cout << currentDateTime2() << " Documentos indexados: " << countDocuments << endl;

	terms.clear();
}

void Indexer::SaveVocabulary() {
	ofstream writer;
	writer.open(directory + "/file.terms");

	unordered_map<string, unsigned int>* terms = dictionary.getTerms();
	unordered_map<string, unsigned int>::iterator it = terms->begin();
	unordered_map<string, unsigned int>::iterator end = terms->end();

	for (; it != end; ++it)
		writer << it->first << " " << it->second << endl;

	writer.close();
}
