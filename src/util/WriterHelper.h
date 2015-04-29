/*
 * WriterHelper.h
 *
 *  Created on: Apr 13, 2015
 *      Author: jordan
 */

#ifndef WRITERHELPER_H_
#define WRITERHELPER_H_

#include <fstream>
#include <cstdio>
#include <string>
#include <stdio.h>
#include "../index/IndexTerm.h"

using namespace std;

class WriterHelper {
	FILE* file;
	string filename;
	unsigned int fileSize;

public:
	WriterHelper(string name, bool writeFile) {
		this->filename = name;
		Open(writeFile);
	}

	virtual ~WriterHelper() {
		Close();
	}

	IndexTerm ReadIndex() {
		CheckFile();

		int termId, documentId, termFrequency;

		fread((char*) &termId, sizeof(int), 1, file);
		fread((char*) &documentId, sizeof(int), 1, file);
		fread((char*) &termFrequency, sizeof(int), 1, file);

		vector<int> positions(termFrequency);
		fread((char*) &positions[0], sizeof(int)*termFrequency, 1, file);

		return IndexTerm(termId, documentId, termFrequency, positions);
	}

	template <class T>
	void Read(T* obj) {
		CheckFile();
		fread((char*) obj, sizeof(T), 1, file);
	}

	void Write(IndexTerm& obj) {
		CheckFile();
		fwrite((char *) &obj.termId, sizeof(obj.termId), 1, file);
		fwrite((char *) &obj.documentId, sizeof(obj.documentId), 1, file);
		fwrite((char *) &obj.frequency, sizeof(obj.frequency), 1, file);
		fwrite((char *) &obj.positions[0], obj.positions.size(), sizeof(int), file);
	}

	void WriteText(string text) {
		CheckFile();
		fwrite((char *) &text, sizeof(text), 1, file);
	}

	bool HasNext() {
		CheckFile();
		return (CurrentPosition() < fileSize);
	}

	unsigned int CurrentPosition() {
		return ftell(file);
	}

	void SetPosition(int position) {
		CheckFile();
		fseek(file, position, SEEK_SET);
	}

	unsigned int getSize() {
		unsigned int currPosition = ftell(file);
		fseek(file, 0L, SEEK_END);
		unsigned int size = ftell(file);
		fseek(file, 0L, currPosition);
		return size;
	}

	void Close() {
		CheckFile();
		fclose(file);
		file = NULL;
	}

	bool Remove()
	{
		Close();
		return (remove(filename.c_str()) == 0);
	}

	string getFilename() {
		return filename;
	}

	bool isOpen() {
		return (file != NULL);
	}

private:

	void Open(bool writeFile) {
		if (writeFile)
			file = fopen(filename.c_str(), "w+b");
		else {
			file = fopen(filename.c_str(), "a+b");
			fseek(file, 0, SEEK_END);
			fileSize = ftell(file);
			rewind(file);
			fseek(file, 0, SEEK_SET);
		}
	}

	void CheckFile() {
		if (file == NULL)
			throw;
	}
};

#endif /* WRITERHELPER_H_ */
