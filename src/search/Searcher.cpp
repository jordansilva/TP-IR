/*
 * Searcher.cpp
 *
 *  Created on: May 4, 2015
 *      Author: jordan
 */

#include "Searcher.h"

Searcher::Searcher(string directory, string index, string vocabulary, string documents) {
	//open index file
	mIndex = new WriterHelper(directory + "/" + index, false);
	cout << "Loading index..." << endl;

    //open vocabulary
	mDictionary = new Dictionary(directory + "/" + vocabulary);
	cout << "Loading vocabulary..." << endl;

	loadDocuments(directory + "/" + documents);
}

Searcher::~Searcher() {
	delete mIndex;
	delete mDictionary;
}

bool Searcher::loadDocuments(string filename) {
	mDocuments.clear();
	ifstream writer(filename);
	if (writer.good()) {
		string line;
		unsigned int id = 0;
        double pr = 0;
		string url;

		while (getline(writer, line)) {
			istringstream ss(line);
			ss >> id >> url >> pr;
            IndexDocument* indexDocument = new IndexDocument();
            indexDocument->setId(id);
            indexDocument->setUrl(url);
            indexDocument->setPageRank(pr);
            mDocuments.insert(pair<unsigned int, IndexDocument*> (id, indexDocument));
		}

		return true;
	} else
		return false;
}

vector<IndexDocument*> Searcher::search(string query) {

	vector<unsigned int> documents;
	int boolCondition = 0;

	string token;
	char_separator<char> sep(" ");
	tokenizer<char_separator<char> > tokens(query, sep);
	for (tokenizer<char_separator<char> >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		token = it.current_token();
		boost::trim(token);

		if (!token.empty()) {
			if (token == "AND") {
				boolCondition = 1;
			} else if (token == "OR") {
				boolCondition = 2;
			} else {
				boost::to_lower(token);
				Term* term = mDictionary->find(token);

				if (term) {
					vector<unsigned int> recoveryItems = recoverIndexTerms(*term);
					if (boolCondition == 1)
						documents = intersectionVec(documents, recoveryItems);
					else
						documents = unionVec(documents, recoveryItems);
				}
				boolCondition = 0;
			}
		}
	}

	vector<IndexDocument*> documentsNames;
	for (unsigned int i = 0; i < documents.size(); i++) {
		map<unsigned int, IndexDocument*>::iterator it = mDocuments.find(documents[i]);

		if (it != mDocuments.end())
			documentsNames.push_back(it->second);
	}

	return documentsNames;
}

vector<unsigned int> Searcher::recoverIndexTerms(Term term) {
	vector<unsigned int> docs;
	mIndex->SetPosition(term.indexSeek);
	while (mIndex->HasNext()) {
		IndexTerm indexTerm = mIndex->ReadIndex();
		if (indexTerm.termId == term.id)
			docs.push_back(indexTerm.documentId);
		else
			break;
	}

	return docs;
}

vector<unsigned int> Searcher::intersectionVec(vector<unsigned int> &v1, vector<unsigned int> &v2) {

	vector<unsigned int> v3;

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}

vector<unsigned int> Searcher::unionVec(vector<unsigned int> &v1, vector<unsigned int> &v2) {

	vector<unsigned int> v3;

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

	return v3;
}
