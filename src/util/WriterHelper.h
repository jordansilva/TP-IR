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
	}

	void Write(IndexTerm& obj) {
		CheckFile();
		fwrite((char *) &obj.termId, sizeof(obj.termId), 1, file);
		fwrite((char *) &obj.documentId, sizeof(obj.documentId), 1, file);
		fwrite((char *) &obj.frequency, sizeof(obj.frequency), 1, file);
		fwrite((char *) &obj.positions[0],
				sizeof(obj.positions) * obj.positions.size(), 1, file);
	}

	void Close() {
		CheckFile();
		fclose(file);
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

	void CheckFile() {
		if (file == NULL)
			throw;
	}
};

#endif /* WRITERHELPER_H_ */
