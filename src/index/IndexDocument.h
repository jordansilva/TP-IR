/*
 * IndexDocument.h
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#ifndef INDEXDOCUMENT_H_
#define INDEXDOCUMENT_H_

#include <iostream>
#include <vector>
#include <string>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
 #include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../libs/reader/CollectionReader.h"
#include "../util/StringHelper.h"
#include <htmlcxx/html/ParserDom.h>
#include <htmlcxx/html/utils.h>
#include <htmlcxx/html/Uri.h>
#include <htmlcxx/html/Node.h>

using namespace htmlcxx;
using namespace RICPNS;
using namespace std;
using namespace boost;
using namespace boost::property_tree;

class IndexDocument {
public:
    IndexDocument();
	IndexDocument(Document document);
	virtual ~IndexDocument();

	//properties
    unsigned int getId();
    void setId(unsigned int value);
    
	string getUrl();
	void setUrl(string url);
    
	string getTitle();
	void setTitle(string title);

    double getPageRank();
    void setPageRank(double value);

    double getTermWeight();
    void setTermWeight(double value);
    
    unsigned int getSizeDocument();
    void setSizeDocument(unsigned int value);
    
    string getDescription();
    vector<string> getKeywords();
    string getKeywordsAsString();
    string getAuthor();
	string getText();
    string getAnchors();
    
    void addUrlsReferenced(string url);
    vector<string> getUrlsReferenced();
    void parserAnchorText(tree<HTML::Node> &dom, tree<HTML::Node>::iterator &it, std::string &anchorText);
    string toJson();

private:
	bool IsScript(string item);
	void ReadDocument(Document document);
	bool RemoveHeader(string& html);
    unsigned int id;
    unsigned int sizeDocument;
	string url;
	string title;
	string text;
    string anchors;
    string description;
    vector<string> keywords;
    string author;
    vector<string> urlsReferenced;
    double pageRank;
    double termWeight;
};

inline unsigned int IndexDocument::getId() {
    return this->id;
}

inline void IndexDocument::setId(unsigned int value) {
    this->id = value;
}

inline unsigned int IndexDocument::getSizeDocument() {
    return this->sizeDocument;
}

inline void IndexDocument::setSizeDocument(unsigned int sizeDocument) {
    this->sizeDocument = sizeDocument;
}

inline string IndexDocument::getUrl() {
	return this->url;
}

inline void IndexDocument::setUrl(string _url) {
	this->url = _url;
}

inline double IndexDocument::getPageRank() {
    return this->pageRank;
}

inline void IndexDocument::setPageRank(double value) {
    this->pageRank = value;
}

inline double IndexDocument::getTermWeight() {
    return this->termWeight;
}

inline void IndexDocument::setTermWeight(double value) {
    this->termWeight = value;
}


inline string IndexDocument::getDescription() {
    return this->description;
}

inline string IndexDocument::getTitle() {
	return this->title;
}

inline vector<string> IndexDocument::getKeywords() {
    return this->keywords;
}

inline string IndexDocument::getKeywordsAsString() {
    string sKeywords = "";
    vector<string>::iterator it = keywords.begin();
    vector<string>::iterator end = keywords.end();
    for (; it != end; ++it)
        sKeywords += *it + ",";
    
    return sKeywords;
}


inline string IndexDocument::getAuthor() {
    return this->author;
}

inline void IndexDocument::addUrlsReferenced(string url) {
    this->urlsReferenced.push_back(url);
}

inline vector<string> IndexDocument::getUrlsReferenced() {
    return this->urlsReferenced;
}

inline void IndexDocument::setTitle(string _title) {
	this->title = _title;
}

inline string IndexDocument::getText() {
	return text;
}

inline string IndexDocument::getAnchors() {
    return anchors;
}

inline string IndexDocument::toJson() {
    ptree out;
    out.put("id", getId());
    out.put("url", getUrl());
    out.put("title", getTitle());
    out.put("description", getDescription());
    out.put("keywords", getKeywordsAsString());
    out.put("author", getAuthor());
    out.put("pageRank", getPageRank());

    std::ostringstream oss;
    boost::property_tree::write_json(oss, out);
    return oss.str();
}

#endif /* INDEXDOCUMENT_H_ */
