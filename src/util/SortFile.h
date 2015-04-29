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

    WriterHelper* writer;
    priority_queue<IndexTerm, vector<IndexTerm>, greater<IndexTerm> >* queue;
    unsigned int queueSize;
    vector<string> fileNames;
    unsigned int countDocs;


public:
    SortFile();
    virtual ~SortFile();
    void sort(string filename);

private:
    void split(string filename);
    void merge();
    int write();
    void checkFileSize();
};

#endif /* SORTFILE_H_ */
