/*
 * SortFile.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: jordan
 */

#include "SortFile.h"

SortFile::SortFile(string directory, string filename) {
	mLastTermIdSeek = 0;
	mWriter = NULL;
	mOutputDirectory = directory;
	mQueue = new priority_queue<IndexTerm, vector<IndexTerm> , greater<IndexTerm> > ();

	execute(directory + "/" + filename);
}

SortFile::~SortFile() {
	delete mWriter;
	delete mQueue;
}

void SortFile::execute(string index) {
	split(index);
	merge();
	remove(index.c_str());
}

void SortFile::split(string filename) {
	//Start Writer
	vector<IndexTerm> vectorTerms;
	vectorTerms.reserve(FILE_SIZE / 16);
	int vectorSize = 0;

	WriterHelper indexFile(filename, false);
	while (indexFile.HasNext()) {
		//add term to vector
		IndexTerm term = indexFile.ReadIndex();
		vectorSize += term.size();
		vectorTerms.push_back(term);

		if (vectorSize >= FILE_SIZE) {
			//create new file to split
			createNewIndexFile("split" + to_string(mQueueFiles.size()) + ".index");

			//dump vector to file
			dumpVector(&vectorTerms);
			vectorSize = 0;

			//close file
			mWriter->Close();
		}
	}

	//check if terms vector is empty, if not, write vector in a new file
	if (!vectorTerms.empty()) {
		createNewIndexFile("split" + to_string(mQueueFiles.size()) + ".index");

		//dump vector to file
		dumpVector(&vectorTerms);

		//close file
		mWriter->Close();
	}

	mWriter = 0;
	vectorTerms.shrink_to_fit();
}

void SortFile::merge() {

	//create runs
	vector<WriterHelper*> runs;
	while (runs.size() <= RUN_SIZE && runs.size() < mQueueFiles.size()) {
		runs.push_back(new WriterHelper(mOutputDirectory + mQueueFiles[runs.size()], false));
	}

	//if exists runs to merge
	if (runs.size() > 1) {
		//create merge file and assign to writer
		createNewIndexFile("merged" + to_string(mQueueFiles.size()) + ".index");

		WriterHelper* run;

		unsigned int runsLeft = runs.size();
		unsigned int currRun = 0;
		bool isLastMerge = runs.size() < RUN_SIZE;
		if (isLastMerge)
			openVocabulary();

		//run until has no runs
		while (runsLeft > 0) {

			//check if is valid queue (pop from queue if is full and/or create new file if is full)
			if (mQueueSize >= HEAP_SIZE) {
				currRun = write(isLastMerge);
			}

			//get run
			run = runs[currRun];

			//insert to queue
			if (run->isOpen() && run->HasNext()) {
				IndexTerm i = run->ReadIndex();
				i.run = currRun;
				mQueueSize += i.size();
				mQueue->push(i);
			} else if (run->isOpen()) {
				run->Remove();
				cout << "File " << run->getFilename() << " was removed!" << endl;
				runsLeft--;
			}

			//if runs get in the end, start again
			if (currRun >= runs.size() - 1)
				currRun = 0;
			else
				currRun++;
		}

		//dump
		while (!mQueue->empty())
			write(isLastMerge);

		cout << "Merged!" << endl;
		mWriter->Close();

		if (isLastMerge) {
			closeVocabulary();
			rename(mWriter->getFilename().c_str(), (mOutputDirectory + "inverted.index").c_str());
			remove(mWriter->getFilename().c_str());
		}
	}

	//remove from file list
	if (mQueueFiles.size() > runs.size()) {
		vector<string> (mQueueFiles.begin() + runs.size(), mQueueFiles.end()).swap(mQueueFiles);
		cout << mQueueFiles.size() << " remaining files." << endl;
		merge();
	} else
		mQueueFiles.clear();

	mWriter = 0;

}

//Create new file and associate to writer
void SortFile::createNewIndexFile(string filename) {
	if (mWriter && mWriter->isOpen())
		mWriter->Close();

	mWriter = new WriterHelper(mOutputDirectory + filename, true);
	mQueueFiles.push_back(filename);
	//std::cout << "File created: " << filename << endl;
}

void SortFile::dumpVector(vector<IndexTerm>* vectorTerms) {
	//sort terms
	std::sort(vectorTerms->begin(), vectorTerms->end());
	for (unsigned int i = 0; i < vectorTerms->size(); i++)
		mWriter->Write(vectorTerms->at(i));

	//clear terms vector and vector size control variable
	vectorTerms->clear();
}

int SortFile::write(bool isLastMerge) {
	//check if queue is empty
	if (!mQueue->empty()) {
		//get top from queue and write in file
		IndexTerm top = mQueue->top();

		if (isLastMerge && top.termId != mLastTermIdSeek) {
			mLastTermIdSeek = top.termId;
			writeVocabulary(top.termId, mWriter->CurrentPosition());
		}

		mWriter->Write(top);

		//remove top from queue and reduce computed size
		mQueueSize -= top.size();
		mQueue->pop();

		//return current run from file
		return top.run;
	}

	return -1;
}

void SortFile::openVocabulary() {
	//open file with terms and their seeks
	mVocabularyWriter.open(mOutputDirectory + "seek.terms");
}

void SortFile::closeVocabulary() {
	//close vocabulary
	mVocabularyWriter.close();
}

void SortFile::writeVocabulary(unsigned int id, unsigned int seek) {
	//writes term id and seek;
	mVocabularyWriter << id << " " << seek << endl;
}

//This method reads the vocabulary with description of term and id, and merges with term-id 
//and seek position in inverted index
void SortFile::mergeVocabulary(string file, string fileSeek, string outputDirectory) {
	ifstream writer(outputDirectory + "/" + file);
	ifstream writerSeek(outputDirectory + "/" + fileSeek);

	string line;
	string term;
	unsigned int id = 0;
	unsigned int seek = 0;

	unordered_map<int, Term*> *terms = new unordered_map<int, Term*> ();
	while (getline(writer, line)) {
		istringstream ss(line);
		ss >> term >> id;
		terms->insert(make_pair(id, new Term(id, term)));
	}

	id = 0;
	seek = 0;
	line = "";

	ofstream vocabularyWriter;
	vocabularyWriter.open(outputDirectory + "/vocabulary.terms");

	while (getline(writerSeek, line)) {
		istringstream ss(line);
		ss >> id >> seek;

		unordered_map<int, Term*>::iterator it = terms->find(id);
		if (it != terms->end())
			vocabularyWriter << it->second->term << " " << it->second->id << " " << seek << endl;
		else {
			cout << id << endl;
		}
	}

	writer.close();
	remove((outputDirectory + "/" + file).c_str());
	writerSeek.close();
	remove((outputDirectory + "/" + fileSeek).c_str());

	vocabularyWriter.close();
}
