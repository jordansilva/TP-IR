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
#include "../libs/reader/CollectionReader.h"
#include "../parser/TextParser.h"
#include "../util/WriterHelper.h"
#include "IndexDocument.h"
#include "IndexTerm.h"
#include "Dictionary.h"

#define INDEX_NAME "file.index"
#define VOCABULARY_NAME "file.terms"

class Indexer {

	string mOutputDirectory;
	WriterHelper* mWriter;
	TextParser mParser;
	Dictionary mDictionary;
	
private:
	void add(IndexDocument &document);
	void dumpVocabulary();	
	bool isValidDocument(string url)

public:
	Indexer(string directory, string mapfile, string output);
	virtual ~Indexer();
	Dictionary getDictionary();
};

inline Dictionary Indexer::getDictionary() {
	return mDictionary;
}

#endif /* INDEXER_H_ */
