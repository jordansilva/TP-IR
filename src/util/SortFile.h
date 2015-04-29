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

class SortFile {

	string mOutputDirectory;

    WriterHelper* mWriter;
    ofstream mVocabularyWriter;

    priority_queue<IndexTerm, vector<IndexTerm>, greater<IndexTerm> >* mQueue;
    vector<string> mQueueFiles;
    unsigned int mLastTermIdSeek;
    unsigned int mQueueSize;

public:
    SortFile(string index);
    virtual ~SortFile();    

private:
    void createNewIndexFile(string filename);
    void checkFileSize();

    void execute(string index);
    void split(string filename);
    void merge();

    int write(bool isLastMerge);
    void dumpVector(vector<IndexTerm>* vectorTerms);

    void openVocabulary();
    void closeVocabulary();
    void writeVocabulary(unsigned int id, unsigned int seek);
    static void mergeVocabulary(string file, string fileSeek, string outputDirectory);
};

#endif /* SORTFILE_H_ */
