#ifndef _FULLSHIPINFO_H_
#define _FULLSHIPINFO_H_
#include <string>
#include <map>
#include "boost/variant.hpp"
class PlugIn_ViewPort;

enum FieldType
{
    INT_TYPE,
    DOUBLE_TYPE,
    LONG_TYPE,
    STRING_TYPE
};

using pInfoVariant = boost::variant<int *, double *, long *, std::string *>;
using PairVariant = std::pair<FieldType, pInfoVariant>;

struct FullShipInfo
{
    double lat = -1;
    double lon = -1;
    int speed = -1;
    int course = -1;
    int heading = -1;
    int elapsed = -1;
    std::string destination;
    std::string flag;
    int length = -1;
    int rot = -1;
    std::string ship_name;
    int ship_type = -1;
    long ship_id = -1;
    int width = -1;
    int l_fore = -1;
    int w_left = -1;
    int dwt = -1;
    int gt_shiptype = -1;
    int pix_x = -1;
    int pix_y = -1;
    std::string legend;
    FullShipInfo();
    void setPixPoint(PlugIn_ViewPort *vp);
    void setValue(std::string key, std::string value);
private:
    std::map<std::string, PairVariant> m_valueMap;
};

#endif // _FULLSHIPINFO_H_
