#include<iostream>
#include<string>
#include<algorithm>
#include<curl/curl.h>
#include<libxml/HTMLparser.h>
#include<libxml/xpath.h>
#include <cctype>
using namespace std;

string strtolower(string str){
  transform(str.begin(), str.end(), str.begin(),::tolower);
  return str;
}

string scrape(string markup){
    string res;
    htmlDocPtr doc = htmlReadMemory(
        markup.data(), markup.length(),
        NULL, NULL,
        HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING
    );
    if (!doc) return "HTML parse failed";

    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (!context) {
        xmlFreeDoc(doc);
        return "XPath context error";
    }

    xmlXPathObjectPtr nodes = xmlXPathEvalExpression(
        (xmlChar*)"//span[contains(@class,'dtText')]",
        context
    );

    if (!nodes || !nodes->nodesetval) {
        xmlXPathFreeContext(context);
        xmlFreeDoc(doc);
        return "No definitions available";
    }

    for (int i = 0; i < nodes->nodesetval->nodeNr; ++i) {
        char* text = (char*)xmlNodeGetContent(nodes->nodesetval->nodeTab[i]);
        if (text) {
            res += text;
            res += "\n";
            xmlFree(text);
        }
    }
    xmlXPathFreeObject(nodes);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
    return res;
}


string request(string word){
    CURLcode res_code=CURLE_FAILED_INIT;
    CURL *curl=curl_easy_init();
    string result;
    string url="https://www.merriam-webster.com/dictionary/"+strtolower(word);

    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&result);
    curl_easy_setopt(curl,CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl,CURLOPT_USERAGENT,"simple scraper");

    if(curl){
        curl_easy_setopt(curl,
                        CURLOPT_WRITEFUNCTION,
                        +[](char* contents, size_t size,size_t nmemb, string* data)->size_t
                                                {
                                                    size_t new_size=size*nmemb;
                                                    if(data==NULL) return 0;
                                                    data->append(contents,new_size);
                                                    return new_size;
                                                }
                                                );

        res_code=curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res_code!=CURLE_OK){
            return curl_easy_strerror(res_code);
        }
       

    }
    return result;
}

int main(int argc, char** argv){
    if(argc!=2){
        cout<<"Please provide a valid english word"<<'\n';
        exit(EXIT_FAILURE);
    }
    curl_global_init(CURL_GLOBAL_ALL);
    string arg=argv[1];
    string res=request(arg);
    cout<<scrape(res)<<'\n';
    curl_global_cleanup();
    return 0;
}