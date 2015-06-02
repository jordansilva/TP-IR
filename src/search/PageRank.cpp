/*
 * PageRank.cpp
 *
 *  Created on: May 30, 2015
 *      Author: jordan
 */

#include "PageRank.h"

PageRank::PageRank() {
}

PageRank::~PageRank() {
}

void PageRank::execute(string documents, string references) {
    fDocuments = documents;
    fReferences = references;
    cout << "Calculating PageRank..." << endl;
    constructTable();
    calculate();
    dump();
}

void PageRank::constructTable() {
    ifstream streamDocuments(fDocuments);
    ifstream streamReferences(fReferences);
    
    string line;
    unsigned int id = 0;
    string url;
    unsigned int size = 0;
    unsigned int totalExternalLinks = 0;
    unsigned int externalLinksMatches = 0;
    
    //reading urls
    cout << "Reading urls" << endl;
    mDocuments = new map<unsigned int, IndexDocument*> ();
    unordered_map<string, unsigned int> *urldocuments = new unordered_map<string, unsigned int> ();
    while (getline(streamDocuments, line)) {
        istringstream ss(line);
        ss >> id >> url >> size;
        IndexDocument* indexDocument = new IndexDocument();
        indexDocument->setId(id);
        indexDocument->setUrl(url);
        indexDocument->setSizeDocument(size);
        mDocuments->insert(make_pair(id, indexDocument));
        urldocuments->insert(make_pair(url, id));
    }
    
    id = 0;
    url = "";
    
    //reading references
    cout << "Reading references" << endl;
    mReferences = new unordered_map<unsigned int, vector<unsigned int>*>();
    
    ofstream tmpReferences;
    tmpReferences.open(fReferences + ".tmp");

    while (getline(streamReferences, line)) {
        istringstream ss(line);
        ss >> id >> url;
        totalExternalLinks++;
        
        //check external link exists in collection
        unordered_map<string, unsigned int>::iterator itUrls = urldocuments->find(url);
        if (itUrls != urldocuments->end())
        {
            tmpReferences << id << " " << url << endl;
            //check if map exists for external url
            //create input references for external url
            //ex: external url, ids from documents references this url
            unordered_map<unsigned int, vector<unsigned int>*>::iterator it = mReferences->find(itUrls->second);
            if (it == mReferences->end())
            {
                externalLinksMatches++;
                vector<unsigned int> *v = new vector<unsigned int>();
                v->push_back(id);
                mReferences->insert(make_pair(itUrls->second, v));
            }
            else
            {
                externalLinksMatches++;
                vector<unsigned int> *v = it->second;
                if (std::find(v->begin(), v->end(), id) == v->end())
                    v->push_back(id);
            }
            
            map<unsigned int, IndexDocument*>::iterator itIndexDocument = mDocuments->find(id);
            itIndexDocument->second->addUrlsReferenced(url);
        }
    }
    
    cout << "Total External Links: " << totalExternalLinks << endl;
    cout << "Matches External Links: " << externalLinksMatches << endl;
    
    streamDocuments.close();
    streamReferences.close();
    tmpReferences.close();
    remove(fReferences.c_str());
    rename((fReferences + ".tmp").c_str(), fReferences.c_str());
}

void PageRank::calculate() {
    cout << "Calculating..." << endl;
    double diff = 1;
    double currDiff = 0;
    unsigned int numIterations = 0;
    
    double sumPR; // sum of current pagerank vector elements
    double sizeCollection = mDocuments->size() * 1.0;

    // nodes
    while (diff > DEFAULT_CONVERGENCE && numIterations < DEFAULT_MAX_ITERATIONS) {
        diff = 0;
        map<unsigned int, IndexDocument*>::iterator it = mDocuments->begin();
        for (; it != mDocuments->end(); ++it) {
            sumPR = 0;
            
            //inputs links
            unordered_map<unsigned int, vector<unsigned int>*>::iterator itReferences = mReferences->find(it->first);
            if (itReferences != mReferences->end()) {
                vector<unsigned int> *v = itReferences->second;
                vector<unsigned int>::iterator vit = v->begin();
                for (; vit != v->end(); ++vit) {
                    map<unsigned int, IndexDocument*>::iterator doc = mDocuments->find(*vit);
                    if (doc != mDocuments->end())
                    {
                        if (numIterations == 0)
                            doc->second->setPageRank(1.0/sizeCollection);
                    
                        if (doc->second->getUrlsReferenced().size() > 0)
                        {
                            sumPR += doc->second->getPageRank() / (doc->second->getUrlsReferenced().size() * 1.0);
                        }
                        else
                        {
                            cout << doc->first << " dangling" << endl;
                        }
                    }
                    else
                        cout << "ERROR!!!" << endl;
                }
            }
            
            sumPR = (1-DEFAULT_ALPHA) + (DEFAULT_ALPHA * sumPR);
            //sumPR = (1-DEFAULT_ALPHA/sizeCollection) + (DEFAULT_ALPHA * sumPR);
            currDiff = abs(sumPR - it->second->getPageRank());
            if (currDiff > diff)
                diff = currDiff;

            //cout << "dangling: " << danglingPR << endl;
            it->second->setPageRank(sumPR);
            //cout << it->first << ": " << it->second->getPageRank() << endl;
        }
        
        cout.precision(15);
        cout << "Iteration " << numIterations << ": " << diff << endl;
        numIterations++;
    }
}

void PageRank::dump() {

    ofstream urlWriter;
    urlWriter.open(fDocuments);

    for(auto it = mDocuments->begin(); it != mDocuments->end(); ++it)
        urlWriter << it->first << " " << it->second->getUrl() << " " << it->second->getSizeDocument() << " " << it->second->getPageRank() << endl;

    urlWriter.close();
}