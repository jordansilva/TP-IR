/*
 * Indexer.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Indexer.h"

Indexer::Indexer(string directory) {
	writer = new WriterHelper(directory + "/file.index");
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
		//cout << "document_id: " << countDocuments << " | term: " << it->first << " | term_id: " << termid << " | " << it->second.size() << endl;
		//cout << termid << endl;
		IndexTerm term(termid, countDocuments, it->second.size(), it->second);
		writer->Write(term);
	}

	if (countDocuments % 10000 == 0)
		cout << currentDateTime2() << " Documentos indexados: " << countDocuments << endl;

	terms.clear();
}
