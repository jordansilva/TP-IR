/*
 * VectorModelSpace.cpp
 *
 *  Created on: June 01, 2015
 *      Author: jordan
 */

#include "VectorModelSpace.h"

VectorModelSpace::VectorModelSpace(string directory, string index, string vocabulary, unordered_map<unsigned int, IndexDocument*> *documents) {
    //open index file
    cout << "Loading index..." << endl;
    mIndex = new WriterHelper(directory + "/" + index, false);
    
    //open vocabulary
    cout << "Loading vocabulary..." << endl;
    mDictionary = new Dictionary(directory + "/" + vocabulary);
    
    //set documents
    mDocuments = documents;
    mCollectionSize = documents->size();
}

VectorModelSpace::~VectorModelSpace() {
    delete mIndex;
    delete mDictionary;
}

struct gtdouble
{
  bool operator()(const double& s1, const double& s2) const
  {
    return s1 > s2;
  }
};


multimap<double, IndexDocument*, std::greater<double> > VectorModelSpace::search(Query query) {
    multimap<double, IndexDocument*, std::greater<double> >  results;
    if (mDocuments && mIndex && mDictionary)
    {
        unordered_map<unsigned int, Query::QueryTerm*> terms = query.mTerms;
        unordered_map<unsigned int, Query::QueryTerm*>::iterator it = terms.begin();
        unordered_map<unsigned int, Query::QueryTerm*>::iterator end = terms.end();
        
        //writing terms
        for (; it != end; ++it) {
            Term* term = mDictionary->find(it->second->text);
            //calculate weight
            if (term) {
                //f(t)
                it->second->term = *term;
                
                //w(t)
                it->second->weightQuery = 1*log2(mCollectionSize/term->frequency);
                
                //for each (d, f(d,t))
                recoverIndexTerms(*term, &query);
            }
            else
                it->second->weightQuery = 0;
        }
        
        //Cosine
        similarity(&query);
        
        multimap<double, IndexDocument*, std::greater<double> > ordered(query.mIndexDocuments.begin(), query.mIndexDocuments.end());
        results = ordered;
    }
    else
        cout << "initSearch before use search method!" << endl;
    
    return results;
}

void VectorModelSpace::recoverIndexTerms(Term term, Query::Query* query) {
    mIndex->SetPosition(term.indexSeek);
    while (mIndex->HasNext()) {
        IndexTerm indexTerm = mIndex->ReadIndex();
        if (indexTerm.termId == term.id)
        {            
            double weight = (1 + log2(indexTerm.frequency)) * log2(mCollectionSize/term.frequency);
            unordered_map<unsigned int, Query::QueryDocs*>::iterator it = query->mDocs.find(indexTerm.documentId);
            //if not exists
            if (it == query->mDocs.end())
            {
                IndexDocument* i = mDocuments->find(indexTerm.documentId)->second;                
                Query::QueryDocs *q = new Query::QueryDocs();
                q->docId = indexTerm.documentId;
                q->termWeight.insert(make_pair(term.id, weight));
                q->document = i;
                q->size = i->getSizeDocument();
                query->mDocs.insert(make_pair(indexTerm.documentId, q));
            }
            else
            {
                unordered_map<unsigned int, double>::iterator it2 = it->second->termWeight.find(term.id);
                if (it2 == it->second->termWeight.end())
                    it->second->termWeight.insert(make_pair(term.id, weight));
                else
                    it2->second = it2->second*2;
            }
        }
        else
            break;
    }
}

void VectorModelSpace::similarity(Query* query) {
    
    //given query weights
    unordered_map<unsigned int, double> queryWeight;
    unordered_map<unsigned int, Query::QueryTerm*>::iterator itTerms = query->mTerms.begin();
    unordered_map<unsigned int, Query::QueryTerm*>::iterator itTermsEnd = query->mTerms.end();
    for (; itTerms != itTermsEnd; ++itTerms)
    {
        unsigned int termId = itTerms->second->term.id;
        unordered_map<unsigned int, double>::iterator itQueryWeight = queryWeight.find(termId);
        if (itQueryWeight == queryWeight.end())
            queryWeight.insert(make_pair(termId, itTerms->second->weightQuery));
        else
            itQueryWeight->second = itQueryWeight->second * 2;
    }
    
    //calculating cosine for each document
    unordered_map<unsigned int, Query::QueryDocs*>::iterator it = query->mDocs.begin();
    unordered_map<unsigned int, Query::QueryDocs*>::iterator end = query->mDocs.end();

    double product = 0;
    for (; it != end; ++it) {
        product = 0;
        
        unordered_map<unsigned int, double>::iterator dTerms = it->second->termWeight.begin();
        unordered_map<unsigned int, double>::iterator dTermsEnd = it->second->termWeight.end();
        
        for (; dTerms != dTermsEnd; ++dTerms) {
            product += queryWeight.find(dTerms->first)->second * dTerms->second;
        }
        
        //product/sqrt(it->second->size * 1.0);
        it->second->similarity = product;        
        
        query->mIndexDocuments.insert(make_pair(it->second->similarity, it->second->document));
    }
}
