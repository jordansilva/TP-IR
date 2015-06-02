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

IndexDocument::IndexDocument() {    
}

IndexDocument::~IndexDocument() {
	// TODO Auto-generated destructor stub
}

void IndexDocument::ReadDocument(Document doc) {
	HTML::ParserDom parser;
	string docText = doc.getText();
	RemoveHeader(docText);
	tree<HTML::Node> dom = parser.parseTree(docText);
	tree<HTML::Node>::iterator it = dom.begin();
	tree<HTML::Node>::iterator end = dom.end();

	int sizeDescription = 80;

	for (; it != end; ++it) {
		if (it.node != 0 && dom.parent(it) != NULL) {
			//skip response header html
			// if (!started && strcasecmp(it->tagName().c_str(), "html") != 0 && strcasecmp(it->tagName().c_str(), "body") != 0)
			// 	continue;
			// else
			// 	started = true;

			//skip script and css
			if (IsScript(it->tagName()))
				it.skip_children();

			if ((!it->isTag()) && (!it->isComment())) {
				this->text += " " + it->text();
			} else {
				//ReadTags(it, end);
				string tag = it->tagName();
				boost::to_lower(tag);

				if (tag == "title") {
					it++;
					if (it == end)
						return;

                    string text = it->text();
                    boost::trim(text);
					setTitle(text);
				}
                if (tag == "a")
                {
                    //getting url references
                    it->parseAttributes();
                    pair<bool, string> href = it->attribute("href");
                    string link;
                    
                    if (href.first)
                    {
                        boost::trim(href.second);
                        boost::to_lower(href.second);
                        
                        link = HTML::convert_link(href.second, getUrl());
                        if (link != this->url)
                            urlsReferenced.push_back(link);
                    }
                    
                    //getting anchor text
                    string anchorText = "";
                    parserAnchorText(dom, it, anchorText);
                    this->anchors += " " + anchorText;
                }
                if (tag == "meta")
                {
                    it->parseAttributes();
                    
                    //check description
                    pair<bool, string> meta = it->attribute("name");
                    pair<bool, string> content = it->attribute("content");
                    if (meta.first && content.first && !content.second.empty())
                    {
                        boost::trim(content.second);
                        
                        //get meta description
                        if (meta.second == "description")
                        {
                            if (content.second.length() < 80)
                                sizeDescription = content.second.length();

                            this->description = content.second.substr(0, sizeDescription);
                        }
                        
                        //get meta keywords
                        if (meta.second == "keywords")
                        {
                            boost::to_lower(content.second);

                            char_separator<char> sep(",.\t\r\n\b\v\f\\");
                            tokenizer<char_separator<char> > tokens(content.second, sep);
                            string token;
                            for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                                token = it.current_token();
                                boost::trim(token);
                                
                                if (!token.empty())
                                    this->keywords.push_back(token);
                            }
                        }
                        
                        //get meta author
                        if (meta.second == "author")
                            this->author = content.second;
                    }
                }
			}
		}
	}
    
    // get description if not exists in metadata
//    if (this->description.empty())
//    {
//        if (this->text.length() < 80)
//            sizeDescription = this->text.length();
//        this->description = this->text.substr(0, sizeDescription);
//        cout << this->description << endl;
//    }
}

void IndexDocument::parserAnchorText(tree<HTML::Node> &dom, tree<HTML::Node>::iterator &it, std::string &anchorText) {
    for(unsigned int i=0; i<dom.number_of_children(it); i++){
        tree<HTML::Node>::iterator it2 = dom.child(it, i);
        if((!it2->isTag()) && (!it2->isComment())){
            anchorText += " " + it2->tagName();
        }
        parserAnchorText(dom, it2, anchorText);
    }
}

bool IndexDocument::RemoveHeader(string& str) {
    size_t pos = str.find("<!DOC");
    if (!pos || pos == string::npos) {
        return false;
    }
    str.erase(0, pos - 1);
    return true;
}

bool IndexDocument::IsScript(string item) {
	boost::to_lower(item);
	if (item.find("script") != string::npos || item.find("noscript")
			!= string::npos || item.find("style") != string::npos) {
		return true;
	}

	return false;
}
