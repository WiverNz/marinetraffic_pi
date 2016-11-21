#ifndef _CURLMARINEEXTRACTOR_H_
#define _CURLMARINEEXTRACTOR_H_
#include "curl/curl.h"
#include <sstream>

class CURLMarineExtractor
{
private:
    CURL* m_curl;
    std::stringstream m_strStream;
    long m_httpCode;
public:
    CURLMarineExtractor();
    ~CURLMarineExtractor();
    void init(const std::string &proxyAddr = std::string(), int proxyPort = 80);
    std::string get(const std::string& url) throw(std::runtime_error);
    std::string getByArea(double sw_x, double sw_y, double ne_x, double ne_y, int zoom, int station,
                          double centerx, double centery);
    long getHttpCode();
private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
    size_t write(void *buffer, size_t size, size_t nmemb);
};

#endif // _CURLMARINEEXTRACTOR_H_
