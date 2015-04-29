/*
 * SortFile.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: jordan
 */

#include "SortFile.h"

SortFile::SortFile() {
	queue = new priority_queue<IndexTerm, vector<IndexTerm> , greater<IndexTerm> > ();
}

SortFile::~SortFile() {
	delete writer;
	delete queue;
}

void SortFile::sort(string filename) {
	split(filename);
	merge();
}

void SortFile::split(string filename) {
	//start writer
	int size = 0;
	vector<IndexTerm> terms;
	WriterHelper wHelper(filename, false);
	while (wHelper.HasNext()) {
		IndexTerm indexTerm = wHelper.ReadIndex();
		terms.push_back(indexTerm);
		size += indexTerm.size();

		if (size >= FILE_SIZE) {
			countDocs++;
			string output = "fileOutput" + std::to_string(fileNames.size()) + ".index";
			writer = new WriterHelper("./output/" + output, true);

			std::sort(terms.begin(), terms.end());
			for (int i = 0; i < terms.size(); i++)
				writer->Write(terms[i]);

			writer->Close();
			fileNames.push_back(output);
			terms.clear();
			size = 0;
		}
	}

	if (!terms.empty()) {
		countDocs++;
		string output = "fileOutput" + std::to_string(fileNames.size()) + ".index";
		writer = new WriterHelper("./output/" + output, true);

		std::sort(terms.begin(), terms.end());
		for (int i = 0; i < terms.size(); i++)
			writer->Write(terms[i]);

		writer->Close();
		fileNames.push_back(output);
		terms.clear();
		size = 0;
	}

	writer = 0;
	cout << "countDocs: " << countDocs << endl;
}

void SortFile::merge() {

	//starting runs
	vector<WriterHelper*> runs;
	while (runs.size() <= RUN_SIZE && runs.size() < fileNames.size()) {
		runs.push_back(new WriterHelper("./output/" + fileNames[runs.size()], false));
	}

	int currentRun = 0;
	int count = runs.size();
	//if exists runs to merge
	if (count > 1) {
		countDocs++;
		string filename = "_merged" + std::to_string(countDocs) + ".index";
		writer = new WriterHelper("./output/" + filename, true);
		fileNames.push_back(filename);
		cout << "File created: " << filename << endl;

		WriterHelper* writerMerge;

		int popRun = -1;

		//run until has no runs
		while (count > 0) {
			//check if is valid queue (pop from queue if is full and/or create new file if is full)
			if (queueSize >= HEAP_SIZE) {
				popRun = write();
				if (popRun != -1)
					currentRun = popRun;
			}

			writerMerge = runs[currentRun];
			//insert to queue
			if (writerMerge->isOpen() && writerMerge->HasNext()) {
				IndexTerm i = writerMerge->ReadIndex();
				i.run = currentRun;
				queue->push(i);
				queueSize += i.size();
			} else if (writerMerge->isOpen()) {
				writerMerge->Remove();
				cout << "File " << currentRun << " was closed!" << endl;
				count--;
			}

			if (currentRun >= runs.size() - 1)
				currentRun = 0;
			else
				currentRun++;
		}

		while (!queue->empty())
			write();

		cout << "Merged!" << endl;
		writer->Close();
	}

	//remove from file list
	if (fileNames.size() > runs.size()) {
		vector<string> (fileNames.begin() + runs.size(), fileNames.end()).swap(fileNames);
		cout << "Merge new files " << fileNames.size() << endl;
		merge();
	} else
		fileNames.clear();

	writer = 0;
}

void SortFile::checkFileSize() {
	writer->Close();
	string filename = "fileOutput" + std::to_string(fileNames.size()) + ".index";
	writer = new WriterHelper("./output/" + filename, true);
	fileNames.push_back(filename);
	countDocs++;
}

int SortFile::write() {
	int run = -1;
	if (!queue->empty()) {
		IndexTerm top = queue->top();
		run = top.run;
		writer->Write(top);
		queueSize -= top.size();
		queue->pop();
	}

	return run;
}

