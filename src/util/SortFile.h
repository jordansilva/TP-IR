/*
 * SortFile.h
 *
 *  Created on: Apr 27, 2015
 *      Author: jordan
 */

#ifndef SORTFILE_H_
#define SORTFILE_H_

#include "../index/IndexTerm.h"
#include "../index/Term.h"
#include "WriterHelper.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

#define HEAP_SIZE 10000000
#define FILE_SIZE 10000000
#define RUN_SIZE 50

class SortFile {

	string mOutputDirectory;

	WriterHelper* mWriter;
	ofstream mVocabularyWriter;

	priority_queue<IndexTerm, vector<IndexTerm> , greater<IndexTerm> >* mQueue;
	vector<string> mQueueFiles;
	unsigned int mLastTermIdSeek;
	unsigned int mQueueSize;

public:
	SortFile(string directory, string index, string filenameOutput);
	virtual ~SortFile();
	static void mergeVocabulary(string file, string fileSeek, string outputDirectory, string outputFile);

private:
	void createNewIndexFile(string filename);
	void checkFileSize();

	void execute(string directory, string filename, string filenameOutput);
	void split(string directory, string filename, string filenameOutput);
	void merge(string filenameOutput);

	int write(bool isLastMerge);
	void dumpVector(vector<IndexTerm>* vectorTerms);

	void openVocabulary();
	void closeVocabulary();
	void writeVocabulary(unsigned int id, unsigned int seek);
};

#endif /* SORTFILE_H_ */
