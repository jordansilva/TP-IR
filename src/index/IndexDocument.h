/*
 * IndexDocument.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef INDEXDOCUMENT_H_
#define INDEXDOCUMENT_H_

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "../libs/reader/CollectionReader.h"
#include "../libs/htmlcxx/html/ParserDom.h"
#include "../libs/htmlcxx/html/utils.h"
#include "../libs/htmlcxx/html/Node.h"

using namespace htmlcxx;
using namespace RICPNS;
using namespace std;

class IndexDocument {
public:
	IndexDocument(Document document);
	virtual ~IndexDocument();

	//properties
	string getUrl();
	void setUrl(string url);

	string getTitle();
	void setTitle(string title);

	string getText();

private:
	bool IsScript(string item);
	void ReadDocument(Document document);
	void ReadTags(tree<HTML::Node>::iterator & item,
			tree<HTML::Node>::iterator & end);
	string url;
	string title;
	string text;
};

inline string IndexDocument::getUrl() {
	return this->url;
}

inline void IndexDocument::setUrl(string _url) {
	this->url = _url;
}

inline string IndexDocument::getTitle() {
	return this->title;
}

inline void IndexDocument::setTitle(string _title) {
	this->title = _title;
}

inline string IndexDocument::getText() {
	return this->text;
}

#endif /* INDEXDOCUMENT_H_ */
