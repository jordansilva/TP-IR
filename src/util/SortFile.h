/*
 * SortFile.h
 *
 *  Created on: Apr 27, 2015
 *      Author: jordan
 */

#ifndef SORTFILE_H_
#define SORTFILE_H_

#include "../index/IndexTerm.h"
#include "WriterHelper.h"
#include <queue>
#include <algorithm>

using namespace std;

#define HEAP_SIZE 10000000
#define FILE_SIZE 10000000
#define RUN_SIZE 50
#define OUTPUT_DIRECTORY "./output/"

class SortFile {

	string mIndex;

    WriterHelper* mWriter;
    ofstream mVocabularyWriter;

    priority_queue<IndexTerm, vector<IndexTerm>, greater<IndexTerm> >* mQueue;
    vector<string> mQueueFiles;
    unsigned int mLastTermIdSeek;
    unsigned int mQueueSize;

public:
    SortFile(string index);
    virtual ~SortFile();
    void sort();

private:
    void createNewIndexFile(string filename);

    void split();
    void dumpVector(vector<IndexTerm>* vectorTerms);

    void merge();
    int write(bool isLastMerge);
    void checkFileSize();

    void openVocabulary();
    void closeVocabulary();
    void writeVocabulary(unsigned int id, unsigned int seek);
};

#endif /* SORTFILE_H_ */
