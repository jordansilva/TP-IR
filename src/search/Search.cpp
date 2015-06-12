/*
 * Search.cpp
 *
 *  Created on: May 4, 2015
 *      Author: jordan
 */

#include "Search.h"

Search::Search(string directory, string index, string vocabulary, unordered_map<unsigned int, IndexDocument*> *documents) {
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

Search::~Search() {
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


void Search::search(Query *query) {    

    if (mDocuments && mIndex && mDictionary)
    {
        unordered_map<unsigned int, Query::QueryTerm*> terms = query->mTerms;
        unordered_map<unsigned int, Query::QueryTerm*>::iterator it = terms.begin();
        unordered_map<unsigned int, Query::QueryTerm*>::iterator end = terms.end();
        
        //writing terms
        for (; it != end; ++it) {
            Term *term = mDictionary->find(it->second->text);
            //calculate weight
            if (term) {
                //f(t)
                it->second->term = *term;
                
                //w(t)
                it->second->weightQuery = 1*log2(mCollectionSize/term->frequency);
                
                //for each (d, f(d,t))
                recoverIndexTerms(*term, query);
            }
            else
                it->second->weightQuery = 0;
        }
        
        //multimap<double, IndexDocument*, std::greater<double> > ordered(query.mIndexDocuments.begin(), query.mIndexDocuments.end());
        //results = ordered;
    }
}

void Search::recoverIndexTerms(Term term, Query::Query* query) {
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

unordered_map<unsigned int, double> Search::normalize(unordered_map<unsigned int, double> data) {
    double maxValue = 0;
    unordered_map<unsigned int, double> results;

    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (maxValue == 0)
            maxValue = it->second;

        results.insert(make_pair(it->first, it->second/maxValue));
    }

    return results;
}

// vector<unsigned int> Search::intersectionVec(vector<unsigned int> &v1, vector<unsigned int> &v2) {

// 	vector<unsigned int> v3;

// 	sort(v1.begin(), v1.end());
// 	sort(v2.begin(), v2.end());

// 	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

// 	return v3;
// }

// vector<unsigned int> Search::unionVec(vector<unsigned int> &v1, vector<unsigned int> &v2) {

// 	vector<unsigned int> v3;

// 	sort(v1.begin(), v1.end());
// 	sort(v2.begin(), v2.end());

// 	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

// 	return v3;
// }
