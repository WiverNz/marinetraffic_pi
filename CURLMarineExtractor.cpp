#include "CURLMarineExtractor.h"
#include <memory>
#include <boost/format.hpp>

CURLMarineExtractor::CURLMarineExtractor()
    : m_curl(curl_easy_init()), m_httpCode(0)
{

}

CURLMarineExtractor::~CURLMarineExtractor()
{
    if (m_curl)
    {
        curl_easy_cleanup(m_curl);
    }
}

void CURLMarineExtractor::init(const std::string &proxyAddr, int proxyPort)
{
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
    if (!proxyAddr.empty())
    {
        std::string proxy;
        proxy.append(proxyAddr);
        proxy.append(std::string(":"));
        proxy.append(std::to_string(proxyPort));
        curl_easy_setopt(m_curl, CURLOPT_PROXY, proxy.c_str());
    }
    struct curl_slist *headerlist = NULL;
    headerlist = curl_slist_append(headerlist, "Accept: application/json, text/javascript, */*; q=0.01");

    headerlist = curl_slist_append(headerlist, "X-Requested-With: XMLHttpRequest");
    headerlist = curl_slist_append(headerlist, "User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36");
    headerlist = curl_slist_append(headerlist, "DNT: 1");
    headerlist = curl_slist_append(headerlist, "Accept-Language: en-US,en;q=0.8");
    headerlist = curl_slist_append(headerlist, "Referer: http://www.marinetraffic.com/");
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "Accept-Encoding: gzip, deflate, sdch");
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, "");
}

std::string CURLMarineExtractor::get(const std::string &url) throw(std::runtime_error)
{
    CURLcode res;
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    m_strStream.str("");
    m_httpCode = 0;
    res = curl_easy_perform(m_curl);
    if (res != CURLE_OK)
    {
        throw std::runtime_error(curl_easy_strerror(res));
    }
    curl_easy_getinfo(m_curl, CURLINFO_RESPONSE_CODE, &m_httpCode);

    return m_strStream.str();
}

std::string CURLMarineExtractor::getByArea(double sw_x, double sw_y, double ne_x, double ne_y, int zoom, int station, double centerx, double centery)
{
    std::string url = "http://marinetraffic.herokuapp.com?";
    std::string format = "sw_x=%1$.1f&sw_y=%2$.1f&ne_x=%3$.1f&ne_y=%4$.1f&zoom=%5%&station=%6%";
    url.append((boost::format(format) % sw_x % sw_y % ne_x % ne_y
                                     % zoom % station).str());

    return get(url);
}

long CURLMarineExtractor::getHttpCode()
{
    return m_httpCode;
}

size_t CURLMarineExtractor::write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    return static_cast<CURLMarineExtractor*>(userp)->write(buffer, size, nmemb);
}

size_t CURLMarineExtractor::write(void *buffer, size_t size, size_t nmemb)
{
    m_strStream.write((const char*)buffer,size*nmemb);

    return size*nmemb;
}
