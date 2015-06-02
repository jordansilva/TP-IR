/*
 * Indexer.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: jordan
 */

#include "Indexer.h"

Indexer::Indexer(string directory, string mapfile, string output) {
	mOutputDirectory = output;
	mWriter = new WriterHelper(mOutputDirectory + INDEX_NAME, true);
    mWriterAnchor = new WriterHelper(mOutputDirectory + ANCHOR_INDEX, true);
    process(directory, mapfile);
}

Indexer::~Indexer() {
	delete mWriter;
    delete mWriterAnchor;
}

void Indexer::process(string directory, string mapfile) {
    if (mWriter->isOpen())
        execute(directory, mapfile);
    else
        cout << "File " << mOutputDirectory + INDEX_NAME << "doesn't exists!";
}

//Indexer
void Indexer::execute(string directory, string mapfile) {
	CollectionReader reader(directory, mapfile);
	ofstream mDocumentsWriter(mOutputDirectory + DOCUMENTS_NAME);
    ofstream mDocumentsMetaWriter(mOutputDirectory + DOCUMENTS_META_NAME);
    ofstream mDocumentsUrlWriter(mOutputDirectory + DOCUMENTS_URL);

	//read documents
	Document doc;
	int countNonValids = 0;
	int count = 0;

	while (reader.getNextDocument(doc)) {
		if (isValidDocument(doc.getURL())) {
			count++;

            //writing index terms
			IndexDocument indexDocument(doc);
			int sizeTerms = writeIndexTerms(indexDocument, count);
            int sizeAnchor = writeAnchorTerms(indexDocument, count);
            
            //writing urls referenced
            vector<string> urls = indexDocument.getUrlsReferenced();
            vector<string>::iterator it = urls.begin();
            vector<string>::iterator end = urls.end();
            for (; it != end; ++it)
                mDocumentsUrlWriter << count << " " << *it << endl;
            
            //writing id-docs
			mDocumentsWriter << count << " " << doc.getURL() << " " << sizeTerms << endl;
            
            //cout << count << " " << indexDocument.getDescription() << " " << indexDocument.getTitle() << endl;
            mDocumentsMetaWriter << count << indexDocument.getTitle() << endl;

			//progress
			if (count % 10000 == 0)
            {
				cout << "Documentos indexados: " << count << " | " << " Quantidade de Termos: "
						<< mDictionary.getTerms()->size() << endl;
            }
		}
        else
            countNonValids++;
	}

	cout << "Docs. Inválidos Encontrados: " << countNonValids << endl;
	cout << "Docs. Válidos Encontrados: " << count << endl;
	//Dump Vocabulary
	dumpVocabulary();
    mDocumentsUrlWriter.close();
    mDocumentsMetaWriter.close();
	mDocumentsWriter.close();
}

int Indexer::writeIndexTerms(IndexDocument &document, int documentId) {
	//Parser and get Terms from document
	mParser.Process(document.getText());
	unordered_map<string, vector<int> > terms = mParser.GetTerms();
	unordered_map<string, vector<int> >::iterator it = terms.begin();
	unordered_map<string, vector<int> >::iterator end = terms.end();

    //writing terms
	unsigned int termId = 0;
	for (; it != end; ++it) {
		termId = mDictionary.AddTerm(it->first, it->second.size());
		IndexTerm indexTerm(termId, documentId, it->second.size(), it->second);
		mWriter->Write(indexTerm);
	}
    
	terms.clear();
    return mParser.GetTerms().size();
}

int Indexer::writeAnchorTerms(IndexDocument &document, int documentId) {
    //Parser and get Terms from document
    mParser.Process(document.getAnchors());
    unordered_map<string, vector<int> > terms = mParser.GetTerms();
    unordered_map<string, vector<int> >::iterator it = terms.begin();
    unordered_map<string, vector<int> >::iterator end = terms.end();
    
    //writing terms
    unsigned int termId = 0;
    for (; it != end; ++it) {
        termId = mDictionaryAnchor.AddTerm(it->first, it->second.size());
        IndexTerm indexTerm(termId, documentId, it->second.size(), it->second);
        mWriterAnchor->Write(indexTerm);
    }
    
    terms.clear();
    return mParser.GetTerms().size();
}

void Indexer::dumpVocabulary() {
    //dump index vocabulary
	ofstream mVocabularyWriter(mOutputDirectory + VOCABULARY_NAME);
	unordered_map<string, Term>* terms = mDictionary.getTerms();
	unordered_map<string, Term>::iterator it = terms->begin();
	unordered_map<string, Term>::iterator end = terms->end();

	for (; it != end; ++it)
        mVocabularyWriter << it->second.id << " " << it->first << " " << it->second.frequency << endl;
    
	mVocabularyWriter.close();
    
    //dump anchor vocabulary
    ofstream mAnchorVocabularyWriter(mOutputDirectory + ANCHOR_TERMS);
    terms = mDictionaryAnchor.getTerms();
    it = terms->begin();
    end = terms->end();
    
    for (; it != end; ++it)
        mAnchorVocabularyWriter << it->second.id << " " << it->first << " " << it->second.frequency << endl;
    
    mAnchorVocabularyWriter.close();
}

bool Indexer::isValidDocument(string url) {
	if (url.find(".pdf") != string::npos || url.find(".doc") != string::npos || url.find(".xls")
			!= string::npos || url.find(".swf") != string::npos)
		return false;
	else
		return true;
}
