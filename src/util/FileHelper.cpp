/*
 * FileHelper.cpp
 *
 *  Created on: June 01, 2015
 *      Author: jordan
 */

#include "FileHelper.h"

FileHelper::FileHelper() {
}

FileHelper::~FileHelper() {
}

unordered_map<unsigned int, IndexDocument*>* FileHelper::loadDocuments(string filename) {
    unordered_map<unsigned int, IndexDocument*> *mDocuments = new unordered_map<unsigned int, IndexDocument*>();
    ifstream writer(filename);
    if (writer.good()) {
        string line;
        unsigned int id = 0;
        double pr = 0;
        unsigned int size = 0;
        string url;
        
        while (getline(writer, line)) {
            istringstream ss(line);
            ss >> id >> url >> size >> pr;
            IndexDocument* indexDocument = new IndexDocument();
            indexDocument->setId(id);
            indexDocument->setUrl(url);
            indexDocument->setSizeDocument(size);
            indexDocument->setPageRank(pr);
            mDocuments->insert(pair<unsigned int, IndexDocument*> (id, indexDocument));
        }
    }
    return mDocuments;
}
