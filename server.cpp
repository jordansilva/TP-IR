//
//  jsearch.cpp
//  ir
//
//  Created by Jordan Silva on 01/06/15.
//  Copyright (c) 2015 MEIKG IT. All rights reserved.
//

//using namespace boost::property_tree;

#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "src/search/Search.h"
#include "src/search/VectorModelSpace.h"
#include "src/search/Query.h"
#include "src/search/PageRank.h"
#include "src/util/FileHelper.h"
#include "src/index/IndexDocument.h"
#include "src/webserver/server_http.hpp"
#include "src/webserver/client_http.hpp"

//Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
//Added for the json-example:
using namespace boost::property_tree;

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Client<SimpleWeb::HTTP> HttpClient;

#define DOCUMENTS_NAME "file.documents"
#define OUTPUT_DIRECTORY "./output/"
#define GROUDTRUTH_DIRECTORY "./results/"
#define INVERTED_INDEX "inverted.index"
#define INVERTED_VOCABULARY "vocabulary.terms"
#define ANCHOR_INDEX "ianchor.index"
#define ANCHOR_VOCABULARY "anchor_vocabulary.terms"
#define ALPHA 0.48 //VMS
#define BETA 0.26 //ANCHOR TEXT
#define GAMA 0.26 //PAGE RANK

boost::unordered_map<unsigned int, IndexDocument*>* mDocuments;
map<int, string> *mQueries;
Search *searchIndex;
Search *searchAnchor;

namespace boost { 
  template<class T> const T* get_pointer(const std::shared_ptr<T>& ptr) 
  {
    return ptr.get();
  }

  template<class T> T* get_pointer(std::shared_ptr<T>& ptr)
  {
    return ptr.get();
  }
}

void init() {
    mDocuments = FileHelper::loadDocuments(string(OUTPUT_DIRECTORY) + "/" + string(DOCUMENTS_NAME));
    searchIndex = new Search(OUTPUT_DIRECTORY, INVERTED_INDEX, INVERTED_VOCABULARY, mDocuments);
    searchAnchor = new Search(OUTPUT_DIRECTORY, ANCHOR_INDEX, ANCHOR_VOCABULARY, mDocuments);

    mQueries = new map<int, string>();  
}

void destroy() {
    delete mDocuments;
    delete searchIndex;
    delete searchAnchor;
}

multimap<double, IndexDocument*, std::greater<double> > merge(boost::unordered_map<unsigned int, double> index, boost::unordered_map<unsigned int, double> anchor, bool pageRank, bool anchorText, double _alpha = ALPHA, double _beta = BETA, double _gama = GAMA) {
    
    index = Search::normalize(index);   
    
    if (anchorText)
        anchor = Search::normalize(anchor);

    multimap<double, IndexDocument*, std::greater<double> > result;
    
    //values
    double vectorValue = 0;
    double anchorValue = 0;
    double pageRankValue = 0;
    double total = 0;

    //weights
    double alpha = _alpha;  
    double gama = _gama;
    double beta = _beta;

    for (auto it = index.begin(); it != index.end(); ++it) {
        
        vectorValue = it->second;
        anchorValue = 0;
        pageRankValue = 0;

        boost::unordered_map<unsigned int, IndexDocument*>::iterator d = mDocuments->find(it->first);
        if (pageRank)
            pageRankValue = d->second->getPageRank();

        if (anchorText) {
            boost::unordered_map<unsigned int, double>::iterator find = anchor.find(it->first);
            if (find != anchor.end())
            {
                anchorValue = find->second;
                anchor.erase(it->first);
            }
        }

        total = (alpha * vectorValue) + (gama * pageRankValue) + (beta * anchorValue);
        result.insert(make_pair(total, d->second));
    }

    if (anchorText) {
        for (auto it = anchor.begin(); it != anchor.end(); ++it)
        {
            anchorValue = 0;
            pageRankValue = 0;

            boost::unordered_map<unsigned int, IndexDocument*>::iterator d = mDocuments->find(it->first);
            if (pageRank)
                pageRankValue = d->second->getPageRank();

            total = (gama * pageRankValue) + (beta * anchorValue);
            result.insert(make_pair(total, d->second));
        }
    }

    return result;  
}

void vectorModel(Query *q) {
    clock_t start = clock();

    searchIndex->search(q);
    VectorModelSpace::order(q);

    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed to search: " << elapsed_secs << endl;
}

void pageRank(Query *q) {
    clock_t start = clock();
    
    searchIndex->search(q);
    PageRank::order(q);
    
    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed to search: " << elapsed_secs << endl;
}

void anchorText(Query *q) {
    clock_t start = clock();
    
    searchAnchor->search(q);    
    VectorModelSpace::order(q);
    
    clock_t end = clock();
    double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed to search: " << elapsed_secs << endl;
}

string search(string query, bool vsm, bool pr, bool at, int page) {

    Query::Query *q = new Query(query); 

    multimap<double, IndexDocument*, std::greater<double> > docs;

    if (vsm && !pr && !at) //vsm
    {
        vectorModel(q);
        docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
    }
    else if (!vsm && pr && !at) //pr
    {
        pageRank(q);
        docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
    }
    else if (!vsm && !pr && at) //anchor text
    {
        anchorText(q);
        docs.insert(q->mIndexDocuments.begin(), q->mIndexDocuments.end());
    }
    else if (vsm) //vsm + pr
    {
        vectorModel(q);
        
        Query::Query *q2 = new Query(query);
        if (at)
            anchorText(q2);

        docs = merge(q->mDocumentsWeight, q2->mDocumentsWeight, pr, at);
    }
    

    multimap<double, IndexDocument*, std::greater<double> >::iterator it = docs.begin();
    int totalPages = ceil(docs.size()/10);
    string json = "[";
    
    int i = 0;
    for (; it != docs.end(); ++it)
    {
        if (floor(i/10.0) == page)
            json = json + it->second->toJson() + ",";

        if (floor(i/10.0) > page)
            break; 

        i++;
    }
    if (json.size()>1)
        json = json.substr(0, json.size()-1);
    
    json += "]";
    json = "{\"page\":" + std::to_string(page) + ", \"totalPages\":" + std::to_string(totalPages) + ",\"result\":" + json + "}";
    return json;
}

std::string minify(std::string json)
{
    std::string ret;
    bool insignificant = true;
    for (unsigned int i = 0; i < json.length(); ++i) {
        if ('"' == json[i]) insignificant = !insignificant;
        if (!(insignificant && isspace(json[i]))) ret += json[i];
    }
    return ret;
}

int main() {
    cout << "Inicializando servidor..." << endl;
    
    init();

    //HTTP-server at port 8080 using 4 threads
    HttpServer server(8080, 4);
    
    //Add resources using path-regex and method-string, and an anonymous function
    //POST-example for the path /string, responds the posted string
    server.resource["^/search$"]["POST"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        try {
            //Retrieve string from istream (request->content)
            ptree pt;
            read_json(request->content, pt);

            bool vectorModel = pt.get<bool>("vms");
            bool anchorText = pt.get<bool>("at");
            bool pageRank = pt.get<bool>("pr");
            int page = pt.get<int>("page");
            string query = pt.get<string>("query");

            string result = search(query, vectorModel, pageRank, anchorText, page);
            result = minify(result);
            
            response << "HTTP/1.1 200 OK\r\nContent-Length: " << result.length() << "\r\nAccess-Control-Allow-Origin: *" << "\r\nContent-Type: \"application/json\"" << "\r\n\r\n" << result;
        }
        catch(std::exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };
    
    //Add resources using path-regex and method-string, and an anonymous function
    //POST-example for the path /string, responds the posted string
    server.resource["^/search/(.+)/page/([0-9]+)$"]["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {    
        try {            
            string query=request->path_match[1];
            unsigned int page = boost::lexical_cast<unsigned int>(request->path_match[2]);
            
            string result = search(query, true, true, true, page);
            result = minify(result);

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << query.length() << "\r\nAccess-Control-Allow-Origin: *" << "\r\nContent-Type: \"application/json\"" << "\r\n\r\n" << result;
        }
        catch(std::exception& e) {
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };
    
    //Default GET-example. If no other matches, this anonymous function will be called. 
    //Will respond with content in the web/-directory, and its subdirectories.
    //Default file: index.html
    //Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
    server.default_resource["GET"]=[](HttpServer::Response& response, std::shared_ptr<HttpServer::Request> request) {
        string filename="./www";
        
        string path=request->path;
        
        //Replace all ".." with "." (so we can't leave the web-directory)
        size_t pos;
        while((pos=path.find(".."))!=string::npos) {
            path.erase(pos, 1);
        }
        
        filename+=path;
        ifstream ifs;
        //A simple platform-independent file-or-directory check do not exist, but this works in most of the cases:
        if(filename.find('.')==string::npos) {
            if(filename[filename.length()-1]!='/')
                filename+='/';
            filename+="index.html";
        }
        
        ifs.open(filename, ifstream::in);
        
        if(ifs) {
            ifs.seekg(0, ios::end);
            size_t length=ifs.tellg();
            
            ifs.seekg(0, ios::beg);

            response << "HTTP/1.1 200 OK\r\nContent-Length: " << length << "\r\n\r\n";
            
            //read and send 128 KB at a time if file-size>buffer_size
            size_t buffer_size=131072;
            if(length>buffer_size) {
                vector<char> buffer(buffer_size);
                size_t read_length;
                while((read_length=ifs.read(&buffer[0], buffer_size).gcount())>0) {
                    response.stream.write(&buffer[0], read_length);
                    response << HttpServer::flush;
                }
            }
            else
                response << ifs.rdbuf();

            ifs.close();
        }
        else {
            string content="Could not open file "+filename;
            response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << content.length() << "\r\n\r\n" << content;
        }
    };
    
    cout << "Servidor inicializado!" << endl;

    thread server_thread([&server](){
        //Start server
        server.start();
    });
    
    // //Wait for server to start so that the client can connect
    // this_thread::sleep_for(chrono::seconds(1));
    
    // //Client examples
    // HttpClient client("localhost:8080");
    // // auto r1=client.request("GET", "/match/123");
    // // cout << r1->content.rdbuf() << endl;

    // string json="{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";
    // stringstream ss(json);    
    // // auto r2=client.request("POST", "/string", ss);
    // // cout << r2->content.rdbuf() << endl;
    
    // ss.str(json);
    // auto r3=client.request("POST", "/json", ss);
    // cout << r3->content.rdbuf() << endl;
        
    server_thread.join();    
    
    return 0;
}