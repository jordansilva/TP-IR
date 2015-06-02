/*
 * FileHelper.h
 *
 *  Created on: June 1, 2015
 *      Author: jordan
 */

#ifndef FILEHELPER_H_
#define FILEHELPER_H_

#include <string>
#include "../util/WriterHelper.h"
#include "../index/Dictionary.h"
#include "../index/Term.h"
#include "../index/IndexDocument.h"
#include <boost/tokenizer.hpp>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

class FileHelper {
public:
    static unordered_map<unsigned int, IndexDocument*>* loadDocuments(string filename);
private:
    FileHelper();
    virtual ~FileHelper();
};

#endif /* FILEHELPER_H_ */
