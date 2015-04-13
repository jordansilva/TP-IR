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
#include "../index/IndexTerm.h"

using namespace std;

class WriterHelper {
	FILE* file;
	string filename;

public:
	WriterHelper(string name) {
		this->filename = name;
		Open();
	}

	virtual ~WriterHelper() {
		Close();
	};

	void Write(IndexTerm& obj) {
		CheckFile();
		fwrite((char *) &obj, sizeof(obj), 1, file);
	}

private:

	void Open() {
		//if (trunc) {
		file = fopen(filename.c_str(), "w+b");
		//size = 0;
		//} else {
		//		file = fopen(name.c_str(), "a+b");
		//		fseek(file, 0, SEEK_END);
		//		int fileSize = ftell(file);
		//		size = fileSize / sizeof(T);
		//		rewind();
		//	}
	}

	void Close() {
		CheckFile();
		fclose(file);
	}

	void CheckFile() {
		if (file == NULL)
			throw;
	}
};

#endif /* WRITERHELPER_H_ */
