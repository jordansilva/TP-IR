/*
 * Indexer.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Indexer.h"

Indexer::Indexer(string directory, string mapfile, string output) {
	mOutputDirectory = output;
	mWriter = new WriterHelper(mOutputDirectory + INDEX_NAME, true);
	countDocuments = 0;

	execute(directory, mapfile);
}

Indexer::~Indexer() {
	delete mWriter;
}

//Indexer
void Indexer::execute(string directory, string mapfile) {
	CollectionReader reader(directory, mapfile);
	
	//read documents
	Document doc;
	int count = 0;

	while (reader.getNextDocument(doc)) {
		if (isValidDocument(doc.getURL())) {
			count++;

			IndexDocument indexDocument(doc);
			add(indexDocument, count);

			//progress
			if (count % 10000 == 0)
				cout << "Documentos indexados: " << count << endl;
		}
	}

	//Dump Vocabulary
	dumpVocabulary();
}

void Indexer::add(IndexDocument &document, int documentId) {
	//Parser and get Terms from document
	mParser.Process(document.getText());
	unordered_map<string, vector<int> > terms = mParser.GetTerms();
	unordered_map<string, vector<int> >::iterator it = terms.begin();
	unordered_map<string, vector<int> >::iterator end = terms.end();
	
	unsigned int termid = 0;
	for (; it != end; ++it) {
		termId = mDictionary.AddTerm(it->first);
		IndexTerm indexTerm(termId, documentId, it->second.size(), it->second);
		mWriter->Write(indexTerm);
	}

	terms.clear();
}

void Indexer::dumpVocabulary() {
	ofstream mVocabularyWriter;
	mVocabularyWriter.open(mOutputDirectory + VOCABULARY_NAME);

	unordered_map<string, Term>* terms = mDictionary.getTerms();
	unordered_map<string, Term>::iterator it = terms->begin();
	unordered_map<string, Term>::iterator end = terms->end();

	for (; it != end; ++it)
		mVocabularyWriter << it->first << " " << it->second.id << endl;

	mVocabularyWriter.close();
}

bool Indexer::isValidDocument(string url) {
	if (url.find(".pdf") != string::npos || url.find(".doc") != string::npos || url.find(".xls")
			!= string::npos || url.find(".swf") != string::npos)
		return false;
	else
		return true;
}

