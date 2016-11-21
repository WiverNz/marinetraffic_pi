#ifndef _CDATAREADER_H_
#define _CDATAREADER_H_
#include <string>
#include <vector>
struct FullShipInfo;
class PlugIn_ViewPort;
class wxDC;
class wxPoint;

class CDataReader
{
public:
    CDataReader();
    ~CDataReader();
    void readData(double sw_x, double sw_y, double ne_x, double ne_y, int zoom, int station,
                  double centerx, double centery);
    void updatePixPositions(PlugIn_ViewPort &vp);
    void draw(wxDC &dc, PlugIn_ViewPort *vp);
    void drawShip(FullShipInfo *shipInfo, wxDC &dcIn);
    void useProxy(const bool &useProxy, const std::__cxx11::string &site = std::__cxx11::string(""), const int &port = -1);
protected:
    std::vector<FullShipInfo *> m_ships;
    void clearData();
    bool m_useProxy;
    std::string m_proxySite;
    int m_proxyPort;
};

#endif // _CDATAREADER_H_
