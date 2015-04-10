/*
 * Indexer.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef INDEXER_H_
#define INDEXER_H_

#include "../parser/TextParser.h"
#include "IndexDocument.h"
#include "Dictionary.h"

class Indexer {
public:
	Indexer();
	virtual ~Indexer();
	void AddDocument(IndexDocument document);

private:
	TextParser parser;
	Dictionary dictionary;
};

#endif /* INDEXER_H_ */
