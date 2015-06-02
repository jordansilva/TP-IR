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
#include <boost/unordered_map.hpp>
#include "../libs/reader/CollectionReader.h"
#include "../parser/TextParser.h"
#include "../util/WriterHelper.h"
//#include "../search/PageRank.h" 
#include "IndexDocument.h"
#include "IndexTerm.h"
#include "Dictionary.h"

#define INDEX_NAME "file.index"
#define ANCHOR_INDEX "anchor.index"
#define VOCABULARY_NAME "file.terms"
#define ANCHOR_TERMS "anchor.terms"
#define DOCUMENTS_NAME "file.documents"
#define DOCUMENTS_URL "url.documents"
#define DOCUMENTS_META_NAME "meta.documents"

using namespace RICPNS;
using namespace htmlcxx;
using namespace boost;

class Indexer {

	string mOutputDirectory;
	WriterHelper* mWriter;
    WriterHelper* mWriterAnchor;
	TextParser mParser;
	Dictionary mDictionary;
    Dictionary mDictionaryAnchor;
	
private:
    void process(string directory, string mapfile);
	void execute(string directory, string mapfile);
	int writeIndexTerms(IndexDocument &document, int documentId);
    int writeAnchorTerms(IndexDocument &document, int documentId);
    void writeUrlsReferenced(IndexDocument &document, int documentId);
	void dumpVocabulary();	
	bool isValidDocument(string url);

public:
	Indexer(string directory, string mapfile, string output);
	virtual ~Indexer();
	Dictionary getDictionary();
};

inline Dictionary Indexer::getDictionary() {
	return mDictionary;
}

#endif /* INDEXER_H_ */
