/*
 * IndexDocument.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "IndexDocument.h"

IndexDocument::IndexDocument(Document doc) {
	setUrl(doc.getURL());
	ReadDocument(doc);
}

IndexDocument::~IndexDocument() {
	// TODO Auto-generated destructor stub
}

void IndexDocument::ReadDocument(Document doc) {
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(doc.getText());
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();

	bool started = false;

	for (; it != end; ++it) {
		if (it.node != 0 && dom.parent(it) != NULL) {
			//skip response header html
			if (!started && strcasecmp(it->tagName().c_str(), "html") != 0)
				continue;
			else
				started = true;

			//skip script and css
			if (IsScript(it->tagName()))
				it.skip_children();

			if ((!it->isTag()) && (!it->isComment())) {
				this->text += " " + it->text();
			} else
				ReadTags(it, end);
		}
	}

	parser, dom, it, end = NULL;
}

bool IndexDocument::IsScript(string item) {
	boost::to_lower(item);
	if (item.find("script") != string::npos || item.find("noscript")
			!= string::npos || item.find("style") != string::npos) {
		return true;
	}

	return false;
}

void IndexDocument::ReadTags(tree<HTML::Node>::iterator & item,
		tree<HTML::Node>::iterator & end) {

	string tag = item->tagName();
	boost::to_lower(tag);

	if (tag == "title") {
		item++;
		if (item == end)
			return;

		setTitle(item->text());
	}
}