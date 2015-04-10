/*
 * Indexer.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Indexer.h"

Indexer::Indexer() {
	// TODO Auto-generated constructor stub

}

Indexer::~Indexer() {
	// TODO Auto-generated destructor stub
}

void Indexer::AddDocument(IndexDocument document) {
	parser.Process(document.getText());
	parser.
}
