/*
 * Indexer.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include <string>
#include <sstream>
#include "../parser/TextParser.h"
#include "../util/WriterHelper.h"
#include "IndexDocument.h"
#include "Dictionary.h"
#include "IndexTerm.h"

class Indexer {

	WriterHelper* writer;
	TextParser parser;
	Dictionary dictionary;
	string directory;
	int countDocuments;

private:
	void CheckSize();

public:
	Indexer(string directory);
	virtual ~Indexer();
	void AddDocument(IndexDocument &document);
	void SaveVocabulary();
	Dictionary getDictionary();
	unsigned long getDocumentsIndexedSize();
};

inline Dictionary Indexer::getDictionary() {
	return dictionary;
}

inline unsigned long Indexer::getDocumentsIndexedSize() {
	return countDocuments;
}

#endif /* INDEXER_H_ */
